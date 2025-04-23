#include "networking_base.h"
#include "arduino_secrets.h"

NetworkingBase::NetworkingBase( Stream * wifi_in, Stream * ethernet_in ) : 
    wifi_ptr {wifi_in},
    ethernet_ptr {ethernet_in}
{

}

NetworkingBase::begin ( ) 
{
    pinMode( NETWORK_CONFIG_PIN, INPUT_PULLUP );
    wifi_pin_set = digitalRead(NETWORK_CONFIG_PIN);
}

const bool NetworkingBase::wifi_on() const 
{
    return wifi_pin_set;
}

const Stream * NetworkingBase::network() const 
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