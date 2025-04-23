#ifndef NETWORKING_BASE_H
#define NETWORKING_BASE_H

#include <Arduino.h>
#include <WiFi.h>
#include <Ethernet.h>

constexpr uint8_t NETWORK_CONFIG_PIN = 7;

class NetworkingBase {
private:
    Stream * wifi_ptr;
    Stream * ethernet_ptr;
    bool wifi_pin_set;
public:
    NetworkingBase();
    NetworkingBase( Stream * wifi_in, Stream * ethernet_in );
    const Stream * network() const; // does this mean wifi and ether need to be public?
    bool wifi_on ( ) const;
    // ~NetworkingBase();
};

#endif