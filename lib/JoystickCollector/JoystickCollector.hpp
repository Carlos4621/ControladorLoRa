#pragma once
#ifndef JOYSTIC_COLLECTOR_HEADER
#define JOYSTIC_COLLECTOR_HEADER

#include <pb.h>
#include "Collector.hpp"
#include "AnalogInput.hpp"
#include "DigitalInput.hpp"
#include "Joystick.pb.h"

/// @brief Struct con los pines del joystick
struct JoystickPins {
    uint8_t axisXPin;
    uint8_t axisYPin;
    uint8_t buttonPin;
};

/// @brief Clase que recolecta el estado de los pines de un joystick
class JoystickCollector : public Collector<Joystick> {
public:

    /// @brief Constructor base
    /// @param axisXPin Pin del eje X del joystick
    /// @param axisYPin Pin del eje Y del joystick
    /// @param buttonPin Pin del botón del joystick
    JoystickCollector(uint8_t axisXPin, uint8_t axisYPin, uint8_t buttonPin);

    /// @brief Constructor con struct
    /// @param pins Pines a usar
    explicit JoystickCollector(const JoystickPins& pins);

    /// @brief Inicializa los pines a usar
    void beginPins() override;

    /// @brief Obtiene el estado actual del joystick
    /// @return El estado actual del joystick
    [[nodiscard]]
    Joystick getData() override;

private:
    static constexpr int8_t MIN_JOYSTICK_VALUE{ -100 };
    static constexpr uint8_t MAX_JOYSTICK_VALUE{ 100 };

    static constexpr uint8_t MIN_ANALOG_INPUT{ 0 };
    static constexpr uint16_t MAX_ANALOG_INPUT{ 4095 };

    static constexpr uint8_t DEAD_ZONE{ 10 };

    AnalogInput axisX_m;
    AnalogInput axisY_m;

    DigitalInput button_m;

    [[nodiscard]]
    static int8_t getScaledValue(uint16_t toScale);

    [[nodiscard]]
    static int8_t getAppliedDeadZone(int8_t toApply);

    [[nodiscard]]
    static int8_t processAxisData(const AnalogInput& axis);
};

#endif // !JOYSTIC_COLLECTOR_HEADER
