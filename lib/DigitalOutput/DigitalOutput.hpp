#pragma once
#ifndef DIGITAL_OUTPUT_HEADER
#define DIGITAL_OUTPUT_HEADER

#include "Pin.hpp"

/// @brief Pin de salida digital
class DigitalOutput : public Pin {
public:

    /// @brief Constructor base
    /// @param pin Número GPIO del pin a usar
    explicit DigitalOutput(uint8_t pin);

    /// @brief Escribe el valor deseado en el pin
    /// @param value Valor a escribir
    void write(bool value);
};

#endif // !DIGITAL_OUTPUT_HEADER
