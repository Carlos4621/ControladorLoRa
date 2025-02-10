#pragma once
#ifndef CONTROLLER_DATA_COLLECTOR_HEADER
#define CONTROLLER_DATA_COLLECTOR_HEADER

#include "ButtonsCollector.hpp"
#include "ModeCollector.hpp"
#include "JoystickCollector.hpp"
#include "ControllerData.pb.h"
#include "FixedSpeedCollector.hpp"

/// @brief Clase encargada de recopilar los datos del control
class ControllerCollector {
public:

    /// @brief Constructor base
    /// @param rightJoystickPins Pines del joystick derecho 
    /// @param leftJoystickPins Pines del joystick izquierdo
    /// @param buttonsPins Pines de los botones
    /// @param modeSelectionPins Pines del seleccionador de modo
    /// @param fixedSpeedPin Pin del fixed speed
    ControllerCollector(const JoystickPins& rightJoystickPins, const JoystickPins& leftJoystickPins, const JoystickPins& cameraJoystick,
        const ButtonsPins& buttonsPins, const ModeSelectionPins& modeSelectionPins, uint8_t fixedSpeedPin);

    /// @brief Inicializa los pines a usar
    void beginPins();

    /// @brief Lee y obtiene el estadp actual de los componentes
    /// @return Estado actual de los componentes
    [[nodiscard]]
    ControllerData getControllerData();

private:
    JoystickCollector rightJoystick_m;
    JoystickCollector leftJoystick_m;

    JoystickCollector cameraJoystick_m;

    FixedSpeedCollector fixedSpeed_m;

    ButtonsCollector buttons_m;

    ModeCollector modes_m;

    [[nodiscard]]
    static bool isJoystickDataEmpty(const Joystick& data);

    [[nodiscard]]
    static bool isButtonsEmpty(const Buttons& data);

    void updateJoystickData(bool& has_joystick, Joystick& data, JoystickCollector& joystick);
    void updateButtonsData(bool& has_buttons, Buttons& data);
};

#endif // !CONTROLLER_DATA_COLLECTOR_HEADER
