#include "networking_base.h"
#include "arduino_secrets.h"

NetworkingBase::NetworkingBase( Stream * wifi_in, Stream * ethernet_in ) {
    wifi_pin_set = digitalRead(NETWORK_CONFIG_PIN);

    wifi_ptr = wifi_in;
    ethernet_ptr = ethernet_in;
}

const Stream * NetworkingBase::network() const {

    if ( wifi_pin_set )
    {
        return wifi_ptr;
    }

    else
    {
        return ethernet_ptr;
    }
}