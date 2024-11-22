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

    data.axisX = processAxisData(axisX_m);
    data.axisY = processAxisData(axisY_m);

    data.button = button_m.read();

    return data;
}

int8_t JoystickCollector::getScaledValue(uint16_t toScale) {
    return static_cast<int8_t>(map(toScale, MIN_ANALOG_INPUT, MAX_ANALOG_INPUT, MIN_JOYSTICK_VALUE, MAX_JOYSTICK_VALUE));
}

int8_t JoystickCollector::getAppliedDeadZone(int8_t toApply) {
    if (toApply < -DEAD_ZONE || toApply > DEAD_ZONE) {
        return toApply;
    }

    return 0;
}

int8_t JoystickCollector::processAxisData(const AnalogInput &axis) {
    const auto rawAxisData{ axis.read() };
    const auto scaledAxis{ getScaledValue(rawAxisData) };

    return getAppliedDeadZone(scaledAxis);
}
