#include "measurement_state.h"


MeasurementState::MeasurementState(uint8_t pirPin, unsigned long holdDuration, uint8_t temp_sensor_pin)
    : m_pirPin { pirPin }, m_holdDuration { holdDuration }, m_temp_sensor { temp_sensor_pin }
    {
        if (temp_sensor_pin == 0) 
        {
            m_temp_sensor_initialized = false;
        } else 
        {
            m_temp_sensor.begin();
            m_temp_sensor_initialized = true;
        }
    }

unsigned long MeasurementState::getCurrentTime(){
    return millis();
}

void MeasurementState::begin(){
    pinMode(m_pirPin, INPUT);

    if(! m_sgp.begin()) {
        Serial.println(F("SGP30 sensor not initialized"));
    }
    else {
        Serial.println(F("SGP30 sensor initialized"));
        if (m_sgp.getIAQBaseline(&m_iaq_baseline_eco2, &m_iaq_baseline_tvoc)) {
            Serial.println(F("SGP30 sensor baseline values set"));
            m_sgp_initialized = true;
        }
        else {
            Serial.println(F("SGP30 sensor baseline values not set"));
        }
    }
}

void MeasurementState::update_pir()
{
    // update room status
    PinStatus currentPinReading = digitalRead(m_pirPin);
    if (currentPinReading) {
        m_lastActivationTime = getCurrentTime();
      }
}
void MeasurementState::update_all(){
    // Read PIR Sensor
    update_pir();
    // read Air Quality Sensor
    if (m_sgp_initialized) {
    readAirQuality();
    }
    // Read Temperature Sensor
    if (m_temp_sensor_initialized) {
        m_temperature = m_temp_sensor.get_temperature();
    }
}



bool MeasurementState::roomHasActivity(){
    if (getCurrentTime() - m_lastActivationTime <= m_holdDuration) {
        return true;
      } else {
        return false;
      }    
}

String MeasurementState::roomIsAvailable()
{
    return String(!roomHasActivity());
}

void MeasurementState::readAirQuality()
{
    m_sgp.setHumidity(0);
    // try to read new data from Air Quality Sensor
    if (!m_sgp.IAQmeasure()) {
        Serial.println(F("Air Quality Sensor reading failed"));
    }
    // if successful update cached Air Quality value
    else {
        m_air_quality = m_sgp.eCO2;
    }
}

 String MeasurementState::getAirQuality()
 {
    if (!m_sgp_initialized) {
        return F("Sensor error");
    }
    return String(m_air_quality);
 }
    
 String MeasurementState::getTemperature()
 {
    if (!m_temp_sensor_initialized) {
        return F("Sensor error");
    }
    return String(m_temperature);
 }