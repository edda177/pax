/**
 * @file MeasurementState.h
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief 
 * @version 0.1
 * @date 2025-04-07
 * 
 */
#ifndef PAX_MEASUREMENT_STATE_CLASS
#define PAX_MEASUREMENT_STATE_CLASS

#include <Arduino.h>
#include <Adafruit_SGP30.h>
#include "temp_sensor.h"

/**
 * @brief Class to handle sensor measurements over time for Arduino UNO R4
 * 
 * Sensors implemented: PIR Sensor
 */
class MeasurementState {
private:
    /**
     * @brief The Arduino Pin where the PIR Sensor is connected
     */
    uint8_t m_pirPin;
    /**
     * @brief Time in milliseconds the class will hold last positive reading
     */
    unsigned long m_holdDuration;
    /**
     * @brief The last time a positive reading was made
     */
    unsigned long m_lastActivationTime;
    /**
     * @brief A wrapper around Arduino function millis()
     * 
     * @return unsigned long 
     */
    Adafruit_SGP30 m_sgp;
    float m_temperature { 22.0f };
    float m_humidity { 50.0f };
    float m_air_quality { 50.0f };
    bool m_sgp_initialized { false };
    TempSensor m_temp_sensor;
    bool m_temp_sensor_initialized {};
    uint16_t m_iaq_baseline_eco2;
    uint16_t m_iaq_baseline_tvoc;
    unsigned long getCurrentTime();
    void readAirQuality();
public:
    /**
     * @brief Constructor
     * 
     * @param pirPin 
     * @param holdDuration in milliseconds
     * @param temp_sensor_pin if not passed getTemperature will give error message
     */
    MeasurementState(uint8_t pirPin, unsigned long holdDuration = 5 * 1 * 1000, uint8_t temp_sensor_pin = 0);
    /**
     * @brief Run in setup to set correct pinMode
     * 
     */
    void begin();
    /**
     * @brief Read PIR sensor value for room activity and update private variables
     * 
     */
    void update_pir();
    /**
     * @brief Read PIR sensor value for room activity and temperature and co2 sensors
     * and update private variables
     * 
     */
    void update_all();
    /**
     * @brief Function to check current room status
     */
    bool roomHasActivity();
    String getAirQuality();
    String getTemperature();
};



#endif