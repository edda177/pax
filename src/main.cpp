#include "measurement_state.h"
#include "networking_base.h"
#include <Arduino.h>

int ledPin = 3;
MeasurementState roomState(2, 5000);

WiFiClient wifi;
EthernetClient ether;
NetworkingBase network (&wifi, &ether) ;


void setup() {
  roomState.init();
  network.begin();
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(500);
  Serial.println(network.wifi_on());

  // if ( wifi )
  // {
  //     wifi.begin(SECRET_SSID, SECRET_PASS);
  // }
  
  // else 
  // {
  //     ethernet_in->begin();
  // }

}

void loop() {
  roomState.update();

  if (roomState.roomHasActivity()) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
