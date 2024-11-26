#pragma once
#ifndef ANALOG_OUTPUT_HEADER
#define ANALOG_OUTPUT_HEADER

#include "Pin.hpp"

/// @brief Pin de salida analógica
class AnalogOutput : public Pin {
public:

    /// @brief Constructor base
    /// @param pin Número GPIO del pin a usar
    explicit AnalogOutput(uint8_t pin);

    /// @brief Escribe el valor enviado
    /// @param value Valor a escribir en la salida
    void write(int value);
};

#endif // !ANALOG_OUTPUT_HEADER