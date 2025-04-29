#include "measurement_state.h"
#include "networking_base.h"
#include "PostMan.h"
#include <Arduino.h>

int ledPin = 3;
MeasurementState roomState(2, 5000);

WiFiClient wifi;
EthernetClient ether;
NetworkingBase network (&wifi, &ether) ;

PostMan postman(SERVER_URL, SERVER_ENDPOINT, SERVER_PORT, &network);

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
    postman.sendPost("1","101","12345000");

}

void loop()
{
    roomState.update();
    
    
    if ( roomState.roomHasActivity() )
    {
        digitalWrite( ledPin, HIGH );
    }
    else
    {
        digitalWrite( ledPin, LOW );
    }
    
    
    network();
    

    delay( 10 );
}