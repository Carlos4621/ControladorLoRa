#pragma once
#ifndef DIGITAL_INPUT_HEADER
#define DIGITAL_INPUT_HEADER

#include "Pin.hpp"

/// @brief Pin de entrada digital
class DigitalInput : public Pin {
public:

    /// @brief Constructor base
    /// @param pin Número GPIO del pin a usar
    explicit DigitalInput(uint8_t pin);

    /// @brief Lee el estado actual del pin
    /// @return El estado actual del pin
    [[nodiscard]]
    bool read() const noexcept;
};

#endif // !DIGITAL_INPUT_HEADER
