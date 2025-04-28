#include "measurement_state.h"
#include "networking_base.h"
#include "PostMan.h"
#include <Arduino.h>

int ledPin = 3;
MeasurementState roomState(2, 5000);

WiFiClient wifi;
EthernetClient ether;
NetworkingBase network (&wifi, &ether) ;

PostMan postman(SERVER_URL, SERVER_ENDPOINT, SERVER_PORT, network.network());

void setup() {
  roomState.init();
  network.begin();
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  delay(200);
  Serial.println(network.wifi_on());
  network();
  while(WiFi.status() != WL_CONNECTED) {}
  Serial.println(WiFi.localIP());
  delay(200);
  postman.sendPost("50°C", "1", "42");
}

void loop() {
  roomState.update();

  if (roomState.roomHasActivity()) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
