/**
 * @file temp_sensor.cpp
 * @brief Handles DHT11 sensor readings
 * 
 */
#include "../include/temp_sensor.h"

TempSensor::TempSensor(uint8_t pin) : pin{pin} {}

unsigned long TempSensor::current_time()
{
    return millis();
}

//! To prevent zero values 
void TempSensor::begin()
{
    // Set pin to OUTPUT before entering store_sensor
    pinMode(pin, OUTPUT);
    store_sensor();
}

byte TempSensor::read_sensor()
{
    byte data;
    for (int i = 0; i < 8; i++)
    {
        if (digitalRead(pin) == LOW)
        {
            while (digitalRead(pin) == LOW)
            {
            // wait 50us; 
            }   
            delayMicroseconds(30); // Duration of high level determine whether data is 0 or 1
            if (digitalRead(pin) == HIGH)
            {
                data |= (1 << (7 - i)); // High in the former, low in the post;
            }
            while (digitalRead(pin) == HIGH)
            {
            // Data '1', waiting for next bit
            } 
        }
    }
    return data;
}

void TempSensor::store_sensor()
{
    this->last_polled = current_time();
    digitalWrite(pin, LOW); // Pull down the bus to send the start signal;
    delay(30);              // The delay is greater than 18 ms so that DHT 11 can detect the start signal;
    digitalWrite(pin, HIGH);
    delayMicroseconds(40); // Wait for DHT11 to respond;
    pinMode(pin, INPUT);
    while (digitalRead(pin) == HIGH)
    {
    }
    delayMicroseconds(80); // The DHT11 responds by pulling the bus low for 80us;
    if (digitalRead(pin) == LOW)
    {
    }
    delayMicroseconds(80);      // DHT11 pulled up after the bus 80us to start sending data;
    for (int i = 0; i < 4; i++) // Receiving data, check bits are not considered;
    {
        this->data[i] = read_sensor();
    }
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // After release of bus, wait for host to start next signal
}

//TempSensor
float TempSensor::get_temperature()
{   
    // This is to ensure we do not poll too often compared to what store_sensor() can handle
    if (current_time() >= this->last_polled + 1000) 
    {
        store_sensor();
    }
    // data[2] integer value of temp. data[3] decimal value of temp 
    return float(data[2]) + (float(data[3]) / 10); 
}

float TempSensor::get_humidity()
{   
    // This is to ensure we do not poll too often compared to what store_sensor() can handle
    if (current_time() >= this->last_polled + 1000)
    {
        store_sensor();
    }
    // data[0] integer value of temp. data[1] decimal value of temp 
    return float(data[0]) + (float(data[1]) / 10); 
}