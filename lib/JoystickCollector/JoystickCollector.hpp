#pragma once
#ifndef JOYSTIC_COLLECTOR_HEADER
#define JOYSTIC_COLLECTOR_HEADER

#include "Collector.hpp"
#include "AnalogInput.hpp"
#include "DigitalInput.hpp"
#include "Joystick.pb.h"

struct JoystickPins {
    uint8_t axisXPin;
    uint8_t axisYPin;
    uint8_t buttonPin;
};

class JoystickCollector : public Collector<Joystick> {
public:
    JoystickCollector(uint8_t axisXPin, uint8_t axisYPin, uint8_t buttonPin);
    explicit JoystickCollector(const JoystickPins& pins);

    void beginPins() override;

    [[nodiscard]]
    Joystick getData() override;

private:
    AnalogInput axisX_m;
    AnalogInput axisY_m;

    DigitalInput button_m;
};

#endif // !JOYSTIC_COLLECTOR_HEADER
