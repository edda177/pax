#ifndef PAX_MEASUREMENT_STATE_CLASS
#define PAX_MEASUREMENT_STATE_CLASS

#include <Arduino.h>


class MeasurementState {
private:
    uint8_t m_pirPin;
    unsigned long m_holdDuration;
    unsigned long m_lastActivationTime;
    unsigned long getCurrentTime();
public:
    MeasurementState(uint8_t pirPin, unsigned long holdDuration);
    void init();
    void update();
    bool roomHasActivity();
};



#endif