#include "networking_base.h"

NetworkingBase::NetworkingBase( WiFiClient* wifi_in, EthernetClient* ethernet_in ) : 
    wifi_ptr {wifi_in},
    ethernet_ptr {ethernet_in}
{

}

void NetworkingBase::begin ( ) 
{
    pinMode( NETWORK_CONFIG_PIN, INPUT_PULLUP );
    wifi_pin_set = digitalRead(NETWORK_CONFIG_PIN);
}

const bool NetworkingBase::wifi_on() const 
{
    return wifi_pin_set;
}

Stream * NetworkingBase::network() const 
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

void NetworkingBase::operator ()(){
    if (wifi_on()) {
        if (WiFi.status() != WL_CONNECTED) {
            WiFi.begin(SECRET_SSID, SECRET_PASS);
        }
    }
    else {
        // gör ethernetgrejs
    }


}