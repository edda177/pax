/**
 * @file networking_base.cpp
 * @brief Handles connections to backend server over WiFi and Ethernet 
 * 
 */
#include "networking_base.h"
#include <SPI.h>

NetworkingBase::NetworkingBase( WiFiClient* wifi_in, EthernetClient* ethernet_in ) : 
    wifi_ptr {wifi_in},
    ethernet_ptr {ethernet_in}
{

}

bool NetworkingBase::initialize_ethernet()
{
    Serial.println(F("Network: Initializing Arduino Ethernet Shield..."));
    
    // Step 1: Configure CS pin
    pinMode(ETHERNET_CS_PIN, OUTPUT);
    digitalWrite(ETHERNET_CS_PIN, HIGH);
    
    // Step 2: Initialize SPI
    SPI.begin();
    
    // Step 3: Initialize Ethernet library with CS pin
    Ethernet.init(ETHERNET_CS_PIN);
    
    // Step 4: Verification delay (let the chip fully initialize)
    delay(1000);
    
    // Check if we can detect the Ethernet hardware
    Serial.println(F("Network: Checking Ethernet hardware status..."));
    
    // Use Ethernet library's hardware status check
    EthernetHardwareStatus hw_status = Ethernet.hardwareStatus();
    
    if (hw_status == EthernetHardwareStatus::EthernetW5100)
    {
        Serial.println(F("Network: W5100 controller detected successfully"));
        return true;
    }
    else if (hw_status == EthernetHardwareStatus::EthernetW5500)
    {
        Serial.println(F("Network: WARNING - W5500 detected instead of expected W5100"));
        // Continue anyway as the library can handle either
        return true;
    }
    else if (hw_status == EthernetHardwareStatus::EthernetNoHardware)
    {
        Serial.println(F("Network: ERROR - No Ethernet hardware detected"));
        return false;
    }
    else
    {
        Serial.println(F("Network: Unknown Ethernet controller"));
        // Try to continue anyway
        return true;
    }
}

bool NetworkingBase::is_valid_ip(const IPAddress& ip) const
{
    // Check if the IP address is all zeros (0.0.0.0)
    if (ip[0] == 0 && ip[1] == 0 && ip[2] == 0 && ip[3] == 0)
    {
        Serial.println(F("Network: ERROR - Invalid IP address (0.0.0.0)"));
        return false;
    }
    
    // Check for APIPA/link-local address (169.254.x.x) which often indicates 
    // DHCP failure but self-assigned address
    if (ip[0] == 169 && ip[1] == 254)
    {
        Serial.print(F("Network: Warning - Link-local address detected: "));
        Serial.println(ip);
        // We don't consider this an error, but log it as a warning
        // Still return true as this is technically a valid IP
        return true;
    }
    
    // Log valid IP address
    Serial.print(F("Network: Valid IP address: "));
    Serial.println(ip);
    return true;
}

bool NetworkingBase::connect_wifi()
{
    Serial.print(F("Network: Using WiFi, connecting to SSID: "));
    Serial.println(SECRET_SSID);
    
    WiFi.begin(SECRET_SSID, SECRET_PASS);
    
    uint32_t start_time_ms = millis();
    uint8_t connection_attempts = 0;
    
    // Wait for connection with timeout
    while (WiFi.status() != WL_CONNECTED)
    {
        if (millis() - start_time_ms > wifi_connect_timeout_ms)
        {
            Serial.println(F("Network: WiFi connection timeout"));
            Serial.print(F("Network: Last WiFi status: "));
            Serial.println(WiFi.status());
            return false;
        }
        delay(100);
        if (++connection_attempts % 10 == 0)
        {
            Serial.print(F("Network: WiFi status: "));
            Serial.print(WiFi.status());
            Serial.print(F(" ("));
            switch(WiFi.status()) {
                case WL_IDLE_STATUS: Serial.print(F("IDLE")); break;
                case WL_NO_SSID_AVAIL: Serial.print(F("NO SSID AVAIL")); break;
                case WL_CONNECT_FAILED: Serial.print(F("CONNECT FAILED")); break;
                case WL_CONNECTION_LOST: Serial.print(F("CONNECTION LOST")); break;
                case WL_DISCONNECTED: Serial.print(F("DISCONNECTED")); break;
                default: Serial.print(F("UNKNOWN")); break;
            }
            Serial.println(F(")"));
            Serial.print(F("."));  // Progress indicator every second
        }
    }
    Serial.println(); // End progress indicator line
    
    // Add delay to ensure connection is fully established
    delay(2000);  // Wait 2 seconds for DHCP and network setup
    
    // Get and store IP address
    m_local_ip = WiFi.localIP();
    
    // Print connection details
    Serial.println(F("Network: WiFi connection established"));
    Serial.print(F("Network: IP Address: "));
    Serial.println(m_local_ip);
    Serial.print(F("Network: Subnet Mask: "));
    Serial.println(WiFi.subnetMask());
    Serial.print(F("Network: Gateway IP: "));
    Serial.println(WiFi.gatewayIP());
    Serial.print(F("Network: DNS Server: "));
    Serial.println(WiFi.dnsIP());
    Serial.print(F("Network: Signal Strength (RSSI): "));
    Serial.print(WiFi.RSSI());
    Serial.println(F(" dBm"));
    
    // Validate IP address
    if (!is_valid_ip(m_local_ip))
    {
        return false;
    }
    return true;    
}

bool NetworkingBase::connect_wifi_to_server() 
{
    Serial.println(F("Network: Connecting WiFi client to server..."));
    Serial.print(F("Network: Server: "));
    Serial.print(SERVER);
    Serial.print(F(":"));
    Serial.println(SERVER_PORT);
    
    if (wifi_ptr->connect(SERVER, SERVER_PORT)) 
    {
        Serial.println(F("Network: WiFi client connected to server."));
        Serial.print(F("Network: Local IP: "));
        Serial.println(m_local_ip);
        Serial.print(F("Network: Remote Port: "));
        Serial.println(SERVER_PORT);
        return true;
    }
    else
    {
        Serial.println(F("Network: Failed to connect WiFi client to server."));
        Serial.print(F("Network: WiFi Status: "));
        Serial.println(WiFi.status());
        Serial.print(F("Network: Write Error: "));
        Serial.println(wifi_ptr->getWriteError());
        return false;
    }
}

bool NetworkingBase::connect_ethernet()
{
    Serial.println(F("Network: Using Ethernet (Arduino Ethernet Shield)"));
    
    // Initialize the Ethernet hardware
    if (!initialize_ethernet())
    {
        Serial.println(F("Network: Ethernet initialization failed"));
        return false;
    }
    
    // Check link status before DHCP
    Serial.print(F("Network: Pre-DHCP physical link status: "));
    bool physical_link = (Ethernet.linkStatus() == LinkON);
    Serial.println(physical_link ? F("CONNECTED") : F("DISCONNECTED"));
    
    if (!physical_link)
    {
        Serial.println(F("Network: Cable not detected, but will try DHCP anyway"));
        Serial.println(F("Network: Check if cable is properly connected to the shield and switch"));
    }
    
    // Try multiple times for DHCP
    int dhcp_result = 0;
    
    Serial.print(F("Network: Attempting DHCP, up to "));
    Serial.print(dhcp_retry_attempts);
    Serial.println(F(" tries..."));
    
    for (uint8_t attempt = 1; attempt <= dhcp_retry_attempts; attempt++)
    {
        Serial.print(F("Network: DHCP attempt "));
        Serial.print(attempt);
        Serial.print(F("..."));
        
        dhcp_result = Ethernet.begin(const_cast<uint8_t*>(Device::ETHERNET_MAC));
        
        if (dhcp_result != 0)
        {
            Serial.println(F("Success!"));
            Serial.print(F("Network: DHCP lease time (seconds): "));
            Serial.println(dhcp_result);
            break;
        }
        else
        {
            Serial.println(F("Failed"));
            delay(1000);  // Wait before retrying
        }
    }
    
    if (dhcp_result == 0)
    {
        // All DHCP attempts failed, try static IP
        Serial.println(F("Network: DHCP failed, using fallback IP"));
        
        // Prepare network configuration with reasonable defaults
        IPAddress fallback_ip(Device::FALLBACK_IP[0], Device::FALLBACK_IP[1],
                           Device::FALLBACK_IP[2], Device::FALLBACK_IP[3]);
        IPAddress dns(8, 8, 8, 8);  // Google DNS
        IPAddress gateway(Device::FALLBACK_IP[0], Device::FALLBACK_IP[1],
                          Device::FALLBACK_IP[2], 1);  // Default gateway (.1)
        IPAddress subnet(255, 255, 255, 0);  // Standard /24 subnet
        
        // Initialize with static configuration
        Ethernet.begin(const_cast<uint8_t*>(Device::ETHERNET_MAC), 
                       fallback_ip, 
                       dns,
                       gateway, 
                       subnet);
                       
        Serial.print(F("Network: Static IP configured: "));
        Serial.println(fallback_ip);
    }
    
    // Always get the assigned IP address
    m_local_ip = Ethernet.localIP();
    
    // Print network configuration for debugging
    Serial.println(F("Network: Configuration details:"));
    Serial.print(F("  IP Address: "));
    Serial.println(m_local_ip);
    Serial.print(F("  Subnet Mask: "));
    Serial.println(Ethernet.subnetMask());
    Serial.print(F("  Gateway IP: "));
    Serial.println(Ethernet.gatewayIP());
    Serial.print(F("  DNS Server: "));
    Serial.println(Ethernet.dnsServerIP());
    
    // Check link status after configuration
    Serial.print(F("Network: Post-DHCP physical link status: "));
    physical_link = (Ethernet.linkStatus() == LinkON);
    Serial.println(physical_link ? F("CONNECTED") : F("DISCONNECTED"));
    
    // Validate IP address
    bool valid_ip = is_valid_ip(m_local_ip);
    
    // Initialize link status tracking for operator()
    last_link_status = physical_link;
    
    // Connection is successful if we have a valid IP
    bool connection_successful = valid_ip;
    
    if (connection_successful)
    {
        Serial.print(F("Network: Successfully configured with IP: "));
        Serial.println(m_local_ip);
    }
    else
    {
        Serial.println(F("Network: Failed to establish connection"));
    }
    
    return connection_successful;
}

void NetworkingBase::handle_dhcp_maintenance(uint8_t maintain_result)
{
    // Process and log the result of Ethernet.maintain()
    switch (maintain_result)
    {
        case 1: // Renew failed
            Serial.println(F("Network: DHCP renew failed"));
            break;
            
        case 2: // Renew success
            Serial.print(F("Network: DHCP renewed IP: "));
            Serial.println(Ethernet.localIP());
            // Update stored IP in case it changed
            m_local_ip = Ethernet.localIP();
            break;
            
        case 3: // Rebind failed
            Serial.println(F("Network: DHCP rebind failed"));
            break;
            
        case 4: // Rebind success
            Serial.print(F("Network: DHCP rebind with new IP: "));
            Serial.println(Ethernet.localIP());
            // Update stored IP
            m_local_ip = Ethernet.localIP();
            break;
            
        default:
            // No change (0), do nothing
            break;
    }
}

void NetworkingBase::begin()
{
    Serial.println(F("Network: Initializing..."));
    pinMode(NETWORK_CONFIG_PIN, INPUT_PULLUP);
    wifi_pin_set = digitalRead(NETWORK_CONFIG_PIN);
    configured = false;
   
    // Exit if clients aren't properly initialized
    if (wifi_ptr == nullptr || ethernet_ptr == nullptr)
    {
        Serial.println(F("Network: ERROR - Client pointers not initialized"));
        return;  
    }
   
    bool connection_successful = false;
   
    // Choose connection method based on configuration pin
    if (wifi_on())
    {
        int attempts {0};
        connection_successful = connect_wifi();
        while ( WiFi.status() != WL_CONNECTED && attempts < 10 )
        {
            attempts++;
            delay(50);
        }
    }
    else
    {
        connection_successful = connect_ethernet();
    }
    
    // Update configuration status based on connection result
    configured = connection_successful;
    
    // Final status report
    if (configured)
    {
        Serial.print(F("Network: Successfully configured with IP: "));
        Serial.println(m_local_ip);
    }
    else
    {
        Serial.println(F("Network: Failed to establish connection"));
        Serial.println(F("Network: Check cable connections and network configuration"));
    }
}

bool NetworkingBase::wifi_on() const 
{
    return wifi_pin_set;
}

bool NetworkingBase::ready_for_traffic() const
{
    if ( configured && wifi_pin_set && WiFi.status() == WL_CONNECTED )
    {
        return true;
    }
    else if ( configured && !wifi_pin_set && Ethernet.linkStatus() == LinkON )
    {
        return true;
    }
    else
    {
        return false;
    }
}

Client * NetworkingBase::current_client() const
{
    if ( wifi_pin_set )
    {
        return wifi_ptr;
    }
    else
    {
        return ethernet_ptr;
    }
}

Stream * NetworkingBase::out_stream() const 
{
    return current_client();
}

void NetworkingBase::operator()()
{
    uint32_t current_time_ms = millis();
    bool state_changed = false;
    
    // WiFi path
    if (wifi_pin_set)
    {
        // Check if we're disconnected
        if (WiFi.status() != WL_CONNECTED)
        {
            if (configured)
            {
                // Just disconnected
                Serial.println(F("Network: WiFi connection lost"));
                configured = false;
                state_changed = true;
            }
            
            // Attempt reconnection with rate limiting
            if (current_time_ms - last_reconnect_attempt_ms > reconnect_interval_ms)
            {
                last_reconnect_attempt_ms = current_time_ms;
                Serial.println(F("Network: Attempting WiFi reconnection..."));
                WiFi.begin(SECRET_SSID, SECRET_PASS);
            }
        }
        // If we're reconnected but state wasn't updated
        else if (!configured)
        {
            m_local_ip = WiFi.localIP();
            
            // Validate IP address
            if (is_valid_ip(m_local_ip))
            {
                configured = true;
                state_changed = true;
            }
        }
    }
    // Ethernet path
    else
    {
        // Get current Ethernet link status
        bool current_link_status = (Ethernet.linkStatus() == LinkON);
        
        // Check if link status changed (cable plugged/unplugged)
        if (current_link_status != last_link_status)
        {
            if (current_link_status)
            {
                Serial.println(F("Network: Ethernet cable connected"));
                
                // Cable just plugged in - reinitialize Ethernet
                Serial.println(F("Network: Restarting Ethernet connection"));
                
                // Try DHCP first
                if (Ethernet.begin(const_cast<uint8_t*>(Device::ETHERNET_MAC)) == 0)
                {
                    // DHCP failed, try static IP
                    Serial.println(F("Network: DHCP failed, using fallback IP"));
                    IPAddress fallback_ip(Device::FALLBACK_IP[0], Device::FALLBACK_IP[1],
                                       Device::FALLBACK_IP[2], Device::FALLBACK_IP[3]);
                    Ethernet.begin(const_cast<uint8_t*>(Device::ETHERNET_MAC), fallback_ip);
                }
                
                // Get and validate IP address
                m_local_ip = Ethernet.localIP();
                configured = is_valid_ip(m_local_ip);
                state_changed = true;
            }
            else
            {
                // Cable just unplugged
                Serial.println(F("Network: Ethernet cable disconnected"));
                configured = false;
                state_changed = true;
            }
            
            // Update the stored link status
            last_link_status = current_link_status;
        }
        
        // Normal Ethernet maintenance
        if (current_link_status)
        {
            // Handle DHCP lease renewal
            uint8_t maintain_result = Ethernet.maintain();
            
            // Process maintenance results if any
            if (maintain_result != 0)
            {
                handle_dhcp_maintenance(maintain_result);
            }
            
            // Periodically check if we have a valid IP (for static configurations)
            if (!configured && (current_time_ms - last_reconnect_attempt_ms > reconnect_interval_ms))
            {
                last_reconnect_attempt_ms = current_time_ms;
                
                m_local_ip = Ethernet.localIP();
                if (is_valid_ip(m_local_ip))
                {
                    Serial.println(F("Network: Ethernet connection restored"));
                    configured = true;
                    state_changed = true;
                }
            }
        }
    }
    
    // Log overall state change if it occurred
    if (last_configured_state != configured)
    {
        Serial.print(F("Network: Status changed to "));
        Serial.println(configured ? F("CONNECTED") : F("DISCONNECTED"));
        last_configured_state = configured;
    }
}