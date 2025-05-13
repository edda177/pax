#ifndef TEMP_SENSOR
#define TEMP_SENSOR
#include <arduino.h>

//! uint8_t defined in lib below
#include <cstdint>

// std::byte defined in lib below
#include <cstddef>

/**
 * @class Class for temperature and humidity sensor DHT11
 * @details
 * Values read will be formatted into json string and sent via Ether/WiFi.
 */
class TempSensor
{
private:
    //! Array to store data and read from
    std::byte data[5];
    //! Pin number of DHT 11 sensor.
    uint8_t m_pin;

public:
    //! Constructor for temp sensor.
    TempSensor(uint8_t pin) {}

    /**
     * @brief
     * @param pin Pin I/O to read from
     * @details Method will store data in byte array
     * @return
     */
    std::byte read(uint8_t pin);

    /**
     * @brief A method for getting the current time passed (ms)
     * @return millis()
     */
    unsigned long current_time();
};

#endif // TEMP_SENSOR