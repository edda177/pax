#ifndef NETWORKING_BASE_H
#define NETWORKING_BASE_H

#include "arduino_secrets.h"
#include <Arduino.h>
#include <WiFiS3.h>
#include <Ethernet.h>
#include <SPI.h>
#include <cstdint>  // For fixed-size types
#include "Device.h"

// Configuration pin as constexpr instead of #define
constexpr uint8_t NETWORK_CONFIG_PIN = 7;

// Arduino Ethernet Shield specific pins
constexpr uint8_t ETHERNET_CS_PIN = 10;   // Arduino Ethernet Shield uses pin 10 for CS (Chip Select)

//! Network handling class
//! @brief This class manages the network state and routes to the configured Client
//!
//! Checks whether or not the configuration pin for wifi or ethernet is set.
//! Passes on the appropriate network object, either Stream (for ArduinoHttpServer)
//! or Client (if you want to use the higher level abstractions for WiFi or Ethernet).
class NetworkingBase 
{
private:
    //! @brief Pointer to the Wifi client created in main.cpp
    //! Explicitly constructed as nullptr.
    WiFiClient* wifi_ptr {nullptr};
    
    //! @brief Pointer to the Ethernet client created in main.cpp
    //! Explicitly constructed as nullptr.
    EthernetClient* ethernet_ptr {nullptr};
    
    //! @brief wifi_pin_set
    //! For storing the pin configuration detected at startup.
    //! Cached here to not have to read the pin state every time.
    bool wifi_pin_set;
    
    //! @brief configured
    //! Set to true if we managed to pass the begin function successfully.
    bool configured = false;
    
    //! @brief m_local_ip
    //! Logs the IP address we connected as.
    IPAddress m_local_ip;
    
    // Networking constants
    static constexpr uint32_t wifi_connect_timeout_ms = 10000;  // 10 seconds
    static constexpr uint32_t reconnect_interval_ms = 5000;     // 5 seconds between reconnection attempts
    static constexpr uint8_t dhcp_retry_attempts = 3;           // Number of DHCP retry attempts
    
    // State tracking variables
    uint32_t last_reconnect_attempt_ms = 0;  // Last time we attempted reconnection
    bool last_configured_state = false;      // Previous connection state for change detection
    bool last_link_status = false;           // Previous Ethernet link status for cable detection
    
    //! @brief Initializes the Ethernet Shield
    //! @return true if initialization successful, false otherwise
    bool initialize_ethernet();
    
    //! @brief Validates if an IP address is valid (non-zero)
    //! @param ip The IP address to validate
    //! @return true if IP is valid, false otherwise
    bool is_valid_ip(const IPAddress& ip) const;
    
    //! @brief Attempts to connect to WiFi network
    //! @return true if connection successful, false otherwise
    bool connect_wifi();

    //! @brief Attempts to establish Ethernet connection
    //! @return true if connection successful, false otherwise
    bool connect_ethernet();
    
    //! @brief Handles Ethernet DHCP maintenance and logs events
    //! @param maintain_result The result code from Ethernet.maintain()
    void handle_dhcp_maintenance(uint8_t maintain_result);
    
public:
    // NetworkingBase(); shouldn't use default constructor, we need the pointers in
   
    //! @brief Intended constructor.
    //! @param wifi_in
    //! Pointer to the WiFiClient object
    //! @param ethernet_in
    //! Pointer to the EtherNetClient object
    NetworkingBase(WiFiClient* wifi_in, EthernetClient* ethernet_in);
   
    //! @brief Returns a pointer to the Stream of the configured connection
    //! For ArduinoHttpServer
    Stream* out_stream() const;
    
    //! @brief Returns a pointer to the Client of the configured connection
    //! For PostMan to send Json.
    Client* current_client() const;
    
    //! @brief Returns what the configuration pin is set to.
    //! Returns the member variable (cached) and not the pin value
    bool wifi_on() const;
    
    //! @brief Returns the current status of the configured connection.
    //! Will return false if configured is false.
    bool ready_for_traffic() const;
    
    //! @brief Attempts to connect to WiFi server
    //! @return true if connection successful, false otherwise
    bool connect_wifi_to_server();

    //! @brief Returns the logged IP address
    //! Do not trust this if configured is not true.
    IPAddress local_ip() const;
    
    //! @brief Startup function
    //! Starting the selected network connection.
    //! Sets configured if the connection is established.
    void begin();
    
    //! @brief Upkeep function operator()
    //! For the main loop, run every time.
    void operator()();
    
    // ~NetworkingBase(); default destructor used
};

#endif