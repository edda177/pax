#include <Arduino.h>

int pirPin = 2;
int ledPin = 3;
int currentPinReading {0};
long unsigned int roomActivateTime;
long unsigned int duration = 5 * 1 * 1000;

void setup() {
  pinMode(pirPin, INPUT);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  currentPinReading = digitalRead(pirPin);
  if (currentPinReading) {
    roomActivateTime = millis();
    Serial.print(" Reset: ");
    Serial.println(roomActivateTime);
  }

  if (millis() - roomActivateTime <= duration) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
