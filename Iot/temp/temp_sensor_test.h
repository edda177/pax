#ifndef TEMP_SENSOR_TEST
#define TEMP_SENSOR_TEST

#include <Arduino.h>
#include "../include/temp_sensor.h"

// File for testing the TempSensor class

// Object of temp_sensor class (we are using DHT11) 
// I/O pin set to example digital pin 2

TempSensor DHT11(2);

void temp_sensor_example_setup()
{
    // Invoke store_sensor 
    DHT11.begin();

    // Use correct baud rate
    Serial.begin(115200);
}
 
void temp_sensor_example_loop()
{
    Serial.print("Humidity: ");
    Serial.println(DHT11.get_humidity());
    Serial.print("Temperature: ");
    Serial.println(DHT11.get_temperature());
}

#endif