#include "networking_base.h"
#include "arduino_secrets.h"

NetworkingBase::NetworkingBase( Stream * wifi_in, Stream * ethernet_in ) {
//    bool wifi = digitalRead(NETWORK_CONFIG_PIN);

    wifi_ptr = wifi_in;
    ethernet_ptr = ethernet_in;

}

const Stream * NetworkingBase::network() const {
    bool wifi = digitalRead(NETWORK_CONFIG_PIN);

    if ( wifi )
    {
        return wifi_ptr;
    }

    else
    {
        return ethernet_ptr;
    }
}