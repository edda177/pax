#include "MeasurementState.h"
#include <Arduino.h>

int ledPin = 3;
MeasurementState roomState(2, 5000);

void setup() {
  roomState.init();

  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  roomState.update();

  if (roomState.roomHasActivity()) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
