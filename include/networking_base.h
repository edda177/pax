#ifndef NETWORKING_BASE_H
#define NETWORKING_BASE_H

#include <Arduino.h>
#include <WiFi.h>
#include <Ethernet.h>

constexpr uint8_t NETWORK_CONFIG_PIN = 7;

class NetworkingBase {
private:
    WiFiClient* wifi_ptr;
    EthernetClient* ethernet_ptr;
    bool wifi_pin_set;
public:
    NetworkingBase();
    NetworkingBase( WiFiClient* wifi_in, EthernetClient* ethernet_in );
    const Stream * network() const; // does this mean wifi and ether need to be public?
    const bool wifi_on ( ) const;
    void begin();
    void operator ()();
    // ~NetworkingBase();
};

#endif