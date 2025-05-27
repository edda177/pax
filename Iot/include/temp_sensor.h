#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H
#include <Arduino.h>

/**
 * @class Class for temperature and humidity sensor DHT11
 * @details
 * Values read will be formatted into json string and sent via Ether/WiFi.
 */
class TempSensor
{
public:
    //! Constructor for temp sensor.
    TempSensor(uint8_t pin);

    /**
     * @brief Initialize sensor
     */
    void begin();

    /**
     * @brief Get the Temperature object
     * @return float value of temperature (%)
     */
    float get_temperature();

    /**
     * @details We have not talked about using humidity values yet
     * @return float value of humidity (%)
     */
    float get_humidity();

    /**
     * @brief A method for getting the current time passed (ms)
     * @return millis()
     */
    unsigned long current_time();

private:
    /**
     * @brief Populate byte array
     */
    void store_sensor();

    /**
     * @brief Method will store data in byte array
     * @return Arduino define byte array
     */
    byte read_sensor();

    //! Store last polled time with millis()
    unsigned long last_polled;
    //! Array to store data and read from
    byte data[5];
    //! Pin number of DHT 11 sensor.
    uint8_t pin;
};

/*
Example Usage:
#include "temp_sensor.h"
    TempSensor DHT11(PIN_NUMBER);

    void setup()
    {
        DHT11.begin();
    }
    void loop(
    {
        DHT11.get_temperature();
    }
*/

#endif // TEMP_SENSOR