#pragma once
#ifndef CONTROLLER_DATA_COLLECTOR_HEADER
#define CONTROLLER_DATA_COLLECTOR_HEADER

#include "ButtonsCollector.hpp"
#include "ModeCollector.hpp"
#include "JoystickCollector.hpp"
#include "ControllerData.pb.h"
#include "FixedSpeedCollector.hpp"

class ControllerCollector {
public:
    ControllerCollector(const JoystickPins& rightJoystickPins, const JoystickPins& leftJoystickPins, const ButtonsPins& buttonsPins
        , const ModeSelectionPins& modeSelectionPins, uint8_t fixedSpeedPin);

    void beginPins();

    [[nodiscard]]
    ControllerData getControllerData();

private:
    JoystickCollector rightJoystick_m;
    JoystickCollector leftJoystick_m;

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
