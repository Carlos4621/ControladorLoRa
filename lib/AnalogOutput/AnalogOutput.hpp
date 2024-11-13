#pragma once
#ifndef ANALOG_OUTPUT_HEADER
#define ANALOG_OUTPUT_HEADER

#include "Pin.hpp"

class AnalogOutput : public Pin {
public:
    explicit AnalogOutput(uint8_t pin);

    void write(uint16_t value);
};

#endif // !ANALOG_OUTPUT_HEADER