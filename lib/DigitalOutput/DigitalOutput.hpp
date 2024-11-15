#pragma once
#ifndef DIGITAL_OUTPUT_HEADER
#define DIGITAL_OUTPUT_HEADER

#include "Pin.hpp"

class DigitalOutput : public Pin {
public:
    explicit DigitalOutput(uint8_t pin);

    void write(bool value);
};

#endif // !DIGITAL_OUTPUT_HEADER
