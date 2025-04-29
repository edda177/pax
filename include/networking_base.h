#ifndef NETWORKING_BASE_H
#define NETWORKING_BASE_H

#include "arduino_secrets.h"
#include <Arduino.h>
#include <WiFi.h>
#include <Ethernet.h>
#include "Device.h"

constexpr uint8_t NETWORK_CONFIG_PIN = 7;

//! Network handling class
//! @brief This class manages the network state and routes to the configured Client
//!
//! Checks wether or not the configuration pin for wifi or ethernet is set.
//! Passes on the appropriate network object, either Stream (for ArduinoHttpServer)
//! or Client (if you want to use the higher level abstractions for WiFi or Ethernet).
//!
//!

class NetworkingBase {
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

public:
    // NetworkingBase(); shouldn't use default constructor, we need the pointers in
    
    //! @brief Intended constructor.
    //! @param wifi_in
    //! Pointer to the WiFiClient object
    //! @param ethernet_in
    //! Pointer to the EtherNetClient object
    
    NetworkingBase( WiFiClient* wifi_in, EthernetClient* ethernet_in );
    
    //! @brief Returns a pointer to the Stream of the configured connection
    //! For ArduinoHttpServer
    Stream * out_stream() const;

    //! @brief Returns a pointer to the Client of the configured connection
    //! For PostMan to send Json.
    Client * current_client() const;

    //! @brief Returns what the configuration pin is set to.
    //! Returns the member variable (cached) and not the 
    const bool wifi_on ( ) const;

    //! @brief Returns the current status of the configured connection.
    //! Will return false if configured is false.
    const bool ready_for_traffic ( ) const;

    //! @brief Returns the logged IP address
    //! Do not trust this if configured is not true.
    const IPAddress local_ip ( ) const;

    //! @brief Startup function
    //! Starting the selected network connection.
    //! Sets configured if the connection is established.
    void begin();

    //! @brief Upkeep function operator ()
    //! For the main loop, run every time.
    void operator ()();

    // ~NetworkingBase(); default destructor used
};

#endif