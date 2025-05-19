#include "measurement_state.h"


MeasurementState::MeasurementState(uint8_t pirPin, unsigned long holdDuration)
    : m_pirPin { pirPin }, m_holdDuration { holdDuration } {}

unsigned long MeasurementState::getCurrentTime(){
    return millis();
}

void MeasurementState::init(){
    pinMode(m_pirPin, INPUT);

    if(! m_sgp.begin()) {
        Serial.println("SGP30 sensor not initialized");
    };
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

void MeasurementState::readAirQuality()
{
    m_sgp.setHumidity(0);
    // try to read new data from Air Quality Sensor
    if (!m_sgp.IAQmeasure()) {
        Serial.println("Air Quality Sensor reading failed");
    }
    // if successful update cached Air Quality value
    else {
        m_air_quality = m_sgp.eCO2;
    }
}

 String MeasurementState::getAirQuality()
 {
    return String(m_air_quality);
 }
    
 String MeasurementState::getTemperature()
 {
    return String(m_temperature);
 }