#include "measurement_state.h"
#include "networking_base.h"
#include "PostMan.h"
#include <Arduino.h>

#ifndef SERVER
//! This is what your ardjuino secrets should look like
#define SECRET_SSID "your_ssid"
#define SECRET_PASS "your_password"

#define SERVER "google.com"
#define SERVER_PORT 8080
#define ENDPOINT "/pax-api/rooms/"
#define ROOM_ID "0"

#endif

//! If your server URL is an IP address, define SERVER_IS_IP in arduino_secrets.h
#ifdef SERVER_IS_IP
IPAddress server_ip(SERVER);
static String server_ip_str = server_ip.toString();
#define SERVER server_ip_str.c_str()
#else
static String server_ip_str = SERVER;
#endif

int pir_pin = 2;
int led_pin = 3;
int temp_pin = 6; 
MeasurementState room_state(pir_pin, 60*1000, temp_pin); // pass temperature pin as 3rd argument to use sensor
WiFiClient wifi;
EthernetClient ether;
NetworkingBase network (&wifi, &ether) ;
PostMan postman(SERVER, ENDPOINT, SERVER_PORT, &network);
time_t postman_wait_time = 30 * 1000;
time_t last_postman_update = 0;
constexpr uint32_t serial_baud_rate = 115200;

void setup()
{
    Serial.begin( serial_baud_rate );
    while (!Serial) {
        delay( 50 );
    }

    delay(500); // extra delay to give Serial connection time
    Wire.begin();
    
    Serial.println( F("System: Initializing room state") );
    room_state.begin();
    

    Serial.println( F("System: Initializing network") );
    network.begin();
    
    Serial.println( F("System: Configuring I/O pins") );
    pinMode( led_pin, OUTPUT );
    digitalWrite( led_pin, LOW );
    

    delay( 100 );
    
    Serial.println( F("System: Initialization complete") );
    
    // Update room state and send initial message to server
    room_state.update_all();
    postman.sendPost(room_state.get_temperature(), room_state.room_has_activity(), room_state.get_air_quality());
    last_postman_update = millis();
}

void loop()
{
    // read sensor data
    room_state.update_all();

    // send data to server
    if (millis()-last_postman_update > postman_wait_time) {
        
        Serial.println("Sending data...");
        network();
        delay(10);
        last_postman_update = millis();
        postman.sendPost(room_state.get_temperature(), room_state.room_has_activity(), room_state.get_air_quality());
    }

    if (millis() > 1000000) {
        network();
    }
    

}