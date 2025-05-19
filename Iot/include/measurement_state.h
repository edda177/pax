/**
 * @file MeasurementState.h
 * @author Erik Dahl (erik@iunderlandet.se)
 * @brief 
 * @version 0.2
 * @date 2025-05-19
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
    uint8_t m_pir_pin;
    /**
     * @brief Time in milliseconds the class will hold last positive reading
     */
    unsigned long m_hold_duration;
    /**
     * @brief The last time a positive reading was made
     */
    unsigned long m_last_activation_time;
    /**
     * @brief A wrapper around Arduino function millis()
     * 
     * @return unsigned long 
     */
    unsigned long get_current_time();
    /**
     * @brief Internal SGP30 sensor object
     * 
     */
    Adafruit_SGP30 m_sgp;
    /**
     * @brief The latest cached Air Quality reading from SGP30
     * defaults to 50%
     * 
     */
    float m_air_quality { 50.0f };
    /**
     * @brief Internal variable indicating if SGP30 is properly initalized
     * 
     */
    bool m_sgp_initialized { false };
    /**
     * @brief Internal Temperature Sensor object
     * 
     */
    TempSensor m_temp_sensor;
    /**
     * @brief The latest cached Temperature reading
     * 
     */
    float m_temperature { 22.0f };
    /**
     * @brief The latest cached Humidity reading
     * 
     */
    float m_humidity { 50.0f };
    /**
     * @brief Internal variable indicating if Temperature Sensor is properly initalized
     * 
     */
    bool m_temp_sensor_initialized {};
    /**
     * @brief Calibration varible for SGP30 sensor
     * 
     */
    uint16_t m_iaq_baseline_eco2;
        /**
     * @brief Calibration varible for SGP30 sensor
     * 
     */
    uint16_t m_iaq_baseline_tvoc;
    /**
     * @brief Read SGP30 values and update internal variables
     * 
     */
    void read_air_quality();
public:
    /**
     * @brief Constructor
     * 
     * @param pir_pin 
     * @param hold_duration in milliseconds
     * @param temp_sensor_pin if not passed getTemperature will give error message
     */
    MeasurementState(uint8_t pir_pin, unsigned long hold_duration = 5 * 1 * 1000, uint8_t temp_sensor_pin = 0);
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
    bool room_has_activity();
    /**
     * @brief Function returns room availability in a printable format
     * 
     * @return String boolean, either true or false
     */
    String room_is_available();
    /**
     * @brief Function returns Air Quality in a printable format 
     * 
     * @return String Values 0-100, representing percentage 
     */
    String get_air_quality();
    /**
     * @brief Funciton returns Temperature in a printable format
     * 
     * @return String temperature in °C
     */
    String get_temperature();
};



#endif