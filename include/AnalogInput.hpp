#pragma once
#ifndef ANALOG_INPUT_HEADER
#define ANALOG_INPUT_HEADER

#include <Arduino.h>
#include "Pin.hpp"

class AnalogInput : public Pin {
public:
    explicit AnalogInput(uint8_t pin);

    [[nodiscard]]
    uint16_t read() const noexcept;
};

#endif // !ANALOG_INPUT_HEADER