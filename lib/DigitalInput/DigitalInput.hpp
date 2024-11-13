#pragma once
#ifndef DIGITAL_INPUT_HEADER
#define DIGITAL_INPUT_HEADER

#include "Pin.hpp"

class DigitalInput : public Pin {
public:
    explicit DigitalInput(uint8_t pin);

    [[nodiscard]]
    bool read() const noexcept;
};

#endif // !DIGITAL_INPUT_HEADER
