#include "measurement_state.h"
#include "networking_base.h"
#include "PostMan.h"
#include <Arduino.h>

#ifndef SERVER
//! This is what your ardjuino secrets should look like
#define SECRET_SSID "your_ssid"
#define SECRET_PASS "your_password"

#define SERVER "google.com"
#define PORT 8080
#define ENDPOINT "/api/v1/room-state"

#endif


int ledPin = 3;
MeasurementState roomState(2, 60*1000); // pass temperature pin as 3rd argument


//! If your server URL is an IP address, define SERVER_IS_IP in arduino_secrets.h
#ifdef SERVER_IS_IP
IPAddress server_ip(SERVER);
static String server_ip_str = server_ip.toString();
#define SERVER server_ip_str.c_str()
#else
static String server_ip_str = SERVER;
#endif


WiFiClient wifi;
EthernetClient ether;
NetworkingBase network (&wifi, &ether) ;

PostMan postman(SERVER, ENDPOINT, PORT, &network);
time_t postman_wait_time = 30 * 1000;
time_t last_postman_update = 0;

void setup()
{
    constexpr uint32_t serial_baud_rate = 115200;
    Serial.begin( serial_baud_rate );
    Wire.begin();
    
    // Let Serial start
    delay( 50 );
    

    Serial.println( F("System: Initializing room state") );
    roomState.init();
    

    Serial.println( F("System: Initializing network") );
    network.begin();
    

    Serial.println( F("System: Configuring I/O pins") );
    pinMode( ledPin, OUTPUT );
    digitalWrite( ledPin, LOW );
    

    delay( 100 );
    
    Serial.println( F("System: Initialization complete") );
    
    // Sending initial message to server
    postman.sendPost("22", String(!roomState.roomHasActivity()), "50");
    last_postman_update = millis();
}

void loop()
{
    // read sensor data
    roomState.update_all();

    // send data to server
    if (millis()-last_postman_update > postman_wait_time) {
        
        Serial.println("Sending data...");
        network();
        delay(10);
        last_postman_update = millis();
        postman.sendPost(roomState.getTemperature(), String(!roomState.roomHasActivity()), roomState.getAirQuality());
    }

    if (millis() > 1000000) {
        network();
    }
    

}