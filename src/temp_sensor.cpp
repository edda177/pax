#include "../include/temp_sensor.h"

TempSensor::TempSensor(uint8_t pin) : m_pin{pin} {}

unsigned long TempSensor::current_time()
{
    return millis();
}

std::byte TempSensor::read(uint8_t pin)
{
    for (int i = 0; i < 8; i++)
    {
        if (digitalRead(pin) == LOW)
        {
            while (digitalRead(pin) == LOW)
                ;                  // wait 50us;
            delayMicroseconds(30); // Duration of high level determine whether data is 0 or 1
            if (digitalRead(pin) == HIGH)
                data |= (1 << (7 - i)); // High in the former, low in the post;
            while (digitalRead(pin) == HIGH)
                ; // Data '1', waiting for next bit
        }
    }
    return data;
}

void start_test(uint8_t pin)
{
    digitalWrite(pin, LOW); // Pull down the bus to send the start signal;
    delay(30);              // The delay is greater than 18 ms so that DHT 11 can detect the start signal;
    digitalWrite(pin, HIGH);
    delayMicroseconds(40); // Wait for DHT11 to respond;
    while (digitalRead(pin) == HIGH)
        ;
    delayMicroseconds(80); // The DHT11 responds by pulling the bus low for 80us;
    if (digitalRead(pin) == LOW)
        ;
    delayMicroseconds(80);      // DHT11 pulled up after the bus 80us to start sending data;
    for (int i = 0; i < 4; i++) // Receiving data, check bits are not considered;
        data[i] = read();
    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH); // After release of bus, wait for host to start next signal
}
void setup()
{
    Serial.begin(9600);
    pinMode(DHpin, OUTPUT);
}
void loop()
{
    start_test();
    Serial.print("Current humdity = ");
    Serial.print(data[0], DEC); // Displays the integer bits of humidity;
    Serial.print('.');
    Serial.print(data[1], DEC); // Displays the decimal places of the humidity;
    Serial.println('%');
    Serial.print("Current temperature = ");
    Serial.print(data[2], DEC); // Displays the integer bits of temperature;
    Serial.print('.');
    Serial.print(data[3], DEC); // Displays the decimal places of the temperature;
    Serial.println('C');
    delay(700);
}