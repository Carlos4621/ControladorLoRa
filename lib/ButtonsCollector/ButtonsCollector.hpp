#pragma once
#ifndef BUTTONS_COLLERCTOR_HEADER
#define BUTTONS_COLLERCTOR_HEADER

#include <pb.h>
#include "Collector.hpp"
#include "Buttons.pb.h"
#include "DigitalInput.hpp"

/// @brief Struct con los pines a usar por el collector
struct ButtonsPins {
    uint8_t buttonAPin;
    uint8_t buttonBPin;
    uint8_t buttonXPin;
    uint8_t buttonYPin;
};

/// @brief Clase que lee y recolecta el estado de los botones seleccionados
class ButtonsCollector : public Collector<Buttons> {
public:

    /// @brief Constructor base
    /// @param buttonAPin Número GPIO del pin del botón A
    /// @param buttonBPin Número GPIO del pin del botón B
    /// @param buttonXPin Número GPIO del pin del botón X
    /// @param buttonYPin Número GPIO del pin del botón Y
    ButtonsCollector(uint8_t buttonAPin, uint8_t buttonBPin, uint8_t buttonXPin, uint8_t buttonYPin);

    /// @brief Constructor con struct
    /// @param pins Pines a usar
    explicit ButtonsCollector(const ButtonsPins& pins);

    /// @brief Inicializa los pines a usar
    void beginPins() override;

    /// @brief Obtiene el estado actual de los botones
    /// @return El estado actual de los botones
    [[nodiscard]]
    Buttons getData() override;

private:
    DigitalInput buttonA_m;
    DigitalInput buttonB_m;
    DigitalInput buttonX_m;
    DigitalInput buttonY_m;

};

#endif // !BUTTONS_COLLERCTOR_HEADER