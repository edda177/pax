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
    if ( wifi_ptr && ethernet_ptr )
    {
        configured = true;
    }

    if (wifi_on()) {
        if ( WiFi.begin(SECRET_SSID, SECRET_PASS) == 0 ) {
            configured = false;
        }
    }
    else {
        if (Ethernet.begin(Device::ETHERNET_MAC) == 0 )
        {
            if ( Ethernet.begin( Device::ETHERNET_MAC, 
                (Device::FALLBACK_IP[0], Device::FALLBACK_IP[1], Device::FALLBACK_IP[2], Device::FALLBACK_IP[3]))
                 == 0 )
             {
                configured == false;
             }
        }
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

void NetworkingBase::operator ()(){
    if ( wifi_pin_set && configured )
    {
        if ( WiFi.status() != WL_CONNECTED )
        {
            if ( WiFi.begin(SECRET_SSID, SECRET_PASS) == 0 )
            {
                configured = false;
            }
        }
    }
    else if ( configured )
    {
        Ethernet.maintain();
    }
}