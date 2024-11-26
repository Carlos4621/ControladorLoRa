#pragma once
#ifndef MOTOR_CONTROLLER_HEADER
#define MOTOR_CONTROLLER_HEADER

#include <pb.h>
#include "ControllerData.pb.h"
#include "BTS7960.hpp"

class MotorController {
public:

    /// @brief Costructor base
    /// @param rightMotorPins Pines para el manejo del motor derecho
    /// @param leftMotorPins Pines para el manejo del motor izquierdo
    /// @param handMotorPins Pines para el manejo del motor de brazo
    MotorController(const BTS7960Pins& rightMotorPins, const BTS7960Pins& leftMotorPins, const BTS7960Pins& handMotorPins);

    /// @brief Inicializa los pines a usar
    void beginPins();

    /// @brief Aplica los datos de un ControllerData
    /// @param dataToApply Datos a aplicar
    void applyMotorData(const ControllerData& dataToApply);

    /// @brief Convierte los valores de los joysticks a los del fixed speed en caso de estar en el modo fixed spee
    /// @param dataToConvert Data a convertir
    /// @return Par con los valores nuevos de los joysticks
    static std::pair<int8_t, int8_t> getFixedSpeedValuesConverted(const ControllerData& dataToConvert) noexcept;

private:
    BTS7960 rightMotor_m;
    BTS7960 leftMotor_m;
    BTS7960 handMotor_m;

    void applyOnIndependentMode(const ControllerData& dataToApply);
    void applyOnFixedSpeedMode(const ControllerData& dataToApply);
    void applyOnAutonomousMode();
};

#endif // !MOTOR_CONTROLLER_HEADER