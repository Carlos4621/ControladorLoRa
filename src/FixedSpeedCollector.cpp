#include "FixedSpeedCollector.hpp"

FixedSpeedCollector::FixedSpeedCollector(uint8_t fixedSpeedPin) 
    : fixedSpeed_m{ fixedSpeedPin }
{
}

void FixedSpeedCollector::beginPins() {
    fixedSpeed_m.begin();
}

int32_t FixedSpeedCollector::getData() {
    return map(fixedSpeed_m.read(), MIN_ANALOG_VALUE, MAX_ANALOG_VALUE, MIN_FIXED_VALUE, MAX_FIXED_VALUE);
}
