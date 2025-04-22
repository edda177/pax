#include "networking_base.h"
#include "arduino_secrets.h"

NetworkingBase::NetworkingBase( Stream * wifi_in, Stream * ethernet_in ) {
    wifi = digitalRead(CONFIG_PIN);

    wifi_ptr = wifi_in;
    ehernet_ptr = ethernet_in;

    if ( wifi )
    {
        wifi_in->begin(SECRET_SSID, SECRET_PASS);
    }
    
    else 
    {
        ethernet_in->begin();
    }
}

const Stream * NetworkingBase::network() const {
    wifi = digitalRead(CONFIG_PIN);

    if ( wifi )
    {
        return wifi_ptr;
    }

    else
    {
        return ethernet_ptr;
    }
}