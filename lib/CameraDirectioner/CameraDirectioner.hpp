#pragma once
#ifndef CAMERA_DIRECTIONER_HEADER
#define CAMERA_DIRECTIONER_HEADER

#include <ESP32Servo.h>
#include <stdexcept>
#include <pb.h>
#include "ControllerData.pb.h"

// |: Hacer clase que junte esta clase con el MotorController, haciendo que dichas clases solo tengan acceso a la información necesaria
// Hacer que el botón del joystick sirva para cambiar la sensibilidad

/// @brief Clase encargada del movimiento XY de la cámara
class CameraDirectioner {
public:

    /// @brief Constructor base
    /// @param pinHorizontalServo Pin en el que está conectado el servo horizontal
    /// @param pinVerticalServo Pin en el que está conectado el servo vertical
    CameraDirectioner(uint8_t pinHorizontalServo, uint8_t pinVerticalServo);

    /// @brief Asigna los pines dados a los servos correspondientes, debe llamarse antes de usar el objeto
    void beginPins();

    /// @brief Coloca los dos servos a 90°
    void centralize();

    /// @brief Realiza el movimiento de la cámara en función a los datos del Joystick
    /// @param controllerData Datos del Joystick
    void applyDirectionData(const Joystick& controllerData);

private:

    static constexpr uint16_t MinMicroseconds{ 600 };
    static constexpr uint16_t MaxMicroseconds{ 2400 };
    static constexpr uint16_t CentralizedServoMicroseconds{ 1350 };

    uint8_t pinVerticalServo_m;
    uint8_t pinHorizontalServo_m;

    Servo horizontalServo_m;
    Servo verticalServo_m;

    [[nodiscard]]
    static bool isAValidMicroseconds(int currentAngle);

    static void applyOnServo(Servo& servo, int32_t axisValue);
};

#endif // !CAMERA_DIRECTIONER_HEADER