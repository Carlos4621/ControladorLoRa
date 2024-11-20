#pragma once
#ifndef JOYSTIC_COLLECTOR_HEADER
#define JOYSTIC_COLLECTOR_HEADER

#include <pb.h>
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
    static constexpr int8_t MIN_JOYSTICK_VALUE{ -100 };
    static constexpr uint8_t MAX_JOYSTICK_VALUE{ 100 };

    static constexpr uint8_t MIN_ANALOG_INPUT{ 0 };
    static constexpr uint16_t MAX_ANALOG_INPUT{ 4095 };

    static constexpr uint8_t DEAD_ZONE{ 10 };

    AnalogInput axisX_m;
    AnalogInput axisY_m;

    DigitalInput button_m;

    [[nodiscard]]
    int8_t getScaledValue(uint16_t toScale);

    [[nodiscard]]
    int8_t getAppliedDeadZone(int8_t toApply);
};

#endif // !JOYSTIC_COLLECTOR_HEADER
