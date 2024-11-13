#include "JoystickCollector.hpp"

JoystickCollector::JoystickCollector(uint8_t axisXPin, uint8_t axisYPin, uint8_t buttonPin) 
    : axisX_m{ axisXPin }
    , axisY_m{ axisYPin }
    , button_m{ buttonPin }
{
}

JoystickCollector::JoystickCollector(const JoystickPins &pins)
    : JoystickCollector{ pins.axisXPin, pins.axisYPin, pins.buttonPin }
{
}

void JoystickCollector::beginPins() {
    axisX_m.begin();
    axisY_m.begin();
    button_m.begin();
}

Joystick JoystickCollector::getData() {
    Joystick data = Joystick_init_zero;

    data.axisX = axisX_m.read();
    data.axisY = axisY_m.read();
    data.button = button_m.read();

    return data;
}
