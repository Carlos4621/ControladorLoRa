#pragma once
#ifndef ANALOG_INPUT_HEADER
#define ANALOG_INPUT_HEADER

#include <Arduino.h>
#include "Pin.hpp"

/// @brief Pin de entrada analógico
class AnalogInput : public Pin {
public:

    /// @brief Constructor base
    /// @param pin Número GPIO del pin a usar 
    explicit AnalogInput(uint8_t pin);

    /// @brief Lee el valor actual del pin
    /// @return Valor actual el pin en base a la resolución actual (default: 12 bits)
    [[nodiscard]]
    uint16_t read() const noexcept;
};

#endif // !ANALOG_INPUT_HEADER