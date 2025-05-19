#include "measurement_state.h"
#include "networking_base.h"
#include "PostMan.h"
#include <Arduino.h>

int ledPin = 3;
MeasurementState roomState(2, 50*1000);

WiFiClient wifi;
EthernetClient ether;
NetworkingBase network (&wifi, &ether) ;

PostMan postman(SERVER_URL, SERVER_ENDPOINT, SERVER_PORT, &network);
time_t postman_wait_time = 30 * 1000;
time_t last_postman_update = 0;

void setup()
{
    constexpr uint32_t serial_baud_rate = 115200;
    Serial.begin( serial_baud_rate );
    
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
    
    // Sending test message to server
    postman.sendPost("22", String(roomState.roomHasActivity()), "50");
    postman.sendPost("1",String(true),"12345000");
    last_postman_update = millis();
}

void loop()
{
    // read sensor data
    roomState.update();

    // send data to server
    if (millis()-last_postman_update > postman_wait_time) {
        
        Serial.println("Sending data...");
        network();
        delay(10);
        last_postman_update = millis();
        postman.sendPost("22", String(roomState.roomHasActivity()), "50");
    }

    // do network maintenance routine
    

}