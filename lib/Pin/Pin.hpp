#pragma once
#ifndef PIN_HEADER
#define PIN_HEADER

#include <Arduino.h>
#include <cstdint>

/// @brief Representación de pin
class Pin {
public:

    /// @brief Constructor base
    /// @param pin Número GPIO del pin a usar
    /// @param pinMode Modo en el que se inicializa el pin
    Pin(uint8_t pin, uint8_t pinMode);

    /// @brief Función para inicializar el pin
    void begin();

protected:

    /// @brief Obtiene el pin seleccionado
    /// @return El pin seleccionado
    [[nodiscard]]
    uint8_t getPin() const noexcept;

private:

    uint8_t pin_m;
    uint8_t pinMode_m;
};


#endif // !PIN_HEADER