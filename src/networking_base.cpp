#include "networking_base.h"

NetworkingBase::NetworkingBase( WiFiClient* wifi_in, EthernetClient* ethernet_in ) : 
    wifi_ptr {wifi_in},
    ethernet_ptr {ethernet_in}
{

}

void NetworkingBase::begin()
{
    constexpr uint32_t wifi_connect_timeout_ms = 10000;

    pinMode( NETWORK_CONFIG_PIN, INPUT_PULLUP );
    wifi_pin_set = digitalRead( NETWORK_CONFIG_PIN );
    configured = false;
    
    // Exit if clients aren't properly initialized
    if (wifi_ptr == nullptr || ethernet_ptr == nullptr) 
    {
        return;  
    }
    
    
    // WiFi connection path
    if (wifi_on()) 
    {
        WiFi.begin(SECRET_SSID, SECRET_PASS);
        
        uint32_t start_time_ms = millis();
        while ( WiFi.status() != WL_CONNECTED ) 
        {
            if ( millis() - start_time_ms > wifi_connect_timeout_ms ) 
            {
                configured = false;
                return;
            }
            delay(100);
        }
        
        // Log IP
        m_local_ip = WiFi.localIP();
    }
    
    // Ethernet connection path
    else 
    {
        if (Ethernet.begin(const_cast<uint8_t*>(Device::ETHERNET_MAC)) == 0) 
        {
            // DHCP failed, try static IP
            IPAddress fallback_ip(Device::FALLBACK_IP[0], Device::FALLBACK_IP[1], 
                               Device::FALLBACK_IP[2], Device::FALLBACK_IP[3]);
            Ethernet.begin(const_cast<uint8_t*>(Device::ETHERNET_MAC), fallback_ip);
        }
        
        // Check physical link and IP validity regardless of method
        if (Ethernet.linkStatus() != LinkON) 
        {
            configured = false;
            return;
        }
        
        // Log IP
        m_local_ip = Ethernet.localIP();
    }

    // Check logged IP validity
    if (m_local_ip[0] == 0 && m_local_ip[1] == 0 && 
        m_local_ip[2] == 0 && m_local_ip[3] == 0) 
    {
        configured = false;  // Invalid IP
    } 
    else 
    {
        configured = true;   // Successfully connected
    }
}

const bool NetworkingBase::wifi_on() const 
{
    return wifi_pin_set;
}

const bool NetworkingBase::ready_for_traffic() const
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
    constexpr uint32_t reconnect_interval_ms = 5000;  // 5 seconds between reconnect attempts
    static uint32_t last_reconnect_attempt_ms = 0;
    uint32_t current_time_ms = millis();
    
    // WiFi path
    if ( wifi_pin_set )
    {
        // Check if we're disconnected
        if ( WiFi.status() != WL_CONNECTED )
        {
            // Attempt reconnection with rate limiting
            if ( current_time_ms - last_reconnect_attempt_ms > reconnect_interval_ms )
            {
                last_reconnect_attempt_ms = current_time_ms;
                WiFi.begin( SECRET_SSID, SECRET_PASS );
            }
            configured = false;
        }
        // If we're reconnected but state wasn't updated
        else if ( !configured )
        {
            m_local_ip = WiFi.localIP();
            
            // Validate IP address
            if ( m_local_ip[0] != 0 || m_local_ip[1] != 0 || 
                 m_local_ip[2] != 0 || m_local_ip[3] != 0 )
            {
                configured = true;
            }
        }
    }
    // Ethernet path
    else
    {
        // Handle DHCP lease renewal
        Ethernet.maintain();
        
        // Check link status
        if ( Ethernet.linkStatus() != LinkON )
        {
            configured = false;
        }
        // If link is back but state wasn't updated
        else if ( !configured )
        {
            m_local_ip = Ethernet.localIP();
            
            // Validate IP address
            if ( m_local_ip[0] != 0 || m_local_ip[1] != 0 || 
                 m_local_ip[2] != 0 || m_local_ip[3] != 0 )
            {
                configured = true;
            }
        }
    }
}