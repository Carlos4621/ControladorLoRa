#include "ControllerCollector.hpp"

ControllerCollector::ControllerCollector(const JoystickPins &rightJoystickPins, const JoystickPins &leftJoystickPins, const ButtonsPins &buttonsPins
, const ModeSelectionPins &modeSelectionPins, uint8_t fixedSpeedPin)
    : rightJoystick_m{ rightJoystickPins }
    , leftJoystick_m{ leftJoystickPins }
    , buttons_m{ buttonsPins }
    , modes_m{ modeSelectionPins }
    , fixedSpeed_m{ fixedSpeedPin }
{
}

void ControllerCollector::beginComponents() {
    rightJoystick_m.beginPins();
    leftJoystick_m.beginPins();
    buttons_m.beginPins();
    modes_m.beginPins();
    fixedSpeed_m.beginPins();
}

ControllerData ControllerCollector::getControllerData() {
    ControllerData data = ControllerData_init_zero;

    updateJoystickData(data.has_rightJoystick, data.rightJoystick, rightJoystick_m);
    updateJoystickData(data.has_leftJoystick, data.leftJoystick, leftJoystick_m);

    updateButtonsData(data.has_buttons, data.buttons);

    data.fixedSpeed = fixedSpeed_m.getData();

    data.selectedMode = modes_m.getData();

    return data;
}

bool ControllerCollector::isJoystickDataEmpty(const Joystick & data) {
    return (data.axisX == 0) && (data.axisY == 0) && (!data.button);
}

bool ControllerCollector::isButtonsEmpty(const Buttons &data) {
    return !(data.buttonA || data.buttonB || data.buttonX || data.buttonY);
}

void ControllerCollector::updateJoystickData(bool& has_joystick, Joystick& data, JoystickCollector& joystick) {
    const Joystick currentData{ joystick.getData() };

    if (isJoystickDataEmpty(currentData)) {
        has_joystick = false;
    }
    else {
        has_joystick = true;
        data = currentData;
    }
}

void ControllerCollector::updateButtonsData(bool& has_buttons, Buttons& data) {
    const Buttons currentData{ buttons_m.getData() };

    if (isButtonsEmpty(currentData)) {
        has_buttons = false;
    }
    else {
        has_buttons = true;
        data = currentData;
    }
    
}
