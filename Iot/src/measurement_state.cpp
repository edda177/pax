#include "measurement_state.h"


MeasurementState::MeasurementState(uint8_t pirPin, unsigned long holdDuration)
    : m_pirPin { pirPin }, m_holdDuration { holdDuration } {}

unsigned long MeasurementState::getCurrentTime(){
    return millis();
}

void MeasurementState::init(){
    pinMode(m_pirPin, INPUT);

}

void MeasurementState::update(){
    PinStatus currentPinReading = digitalRead(m_pirPin);
    if (currentPinReading) {
        m_lastActivationTime = getCurrentTime();
      }
}

bool MeasurementState::roomHasActivity(){
    if (getCurrentTime() - m_lastActivationTime <= m_holdDuration) {
        return true;
      } else {
        return false;
      }    
}