#pragma once
#ifndef MOTOR_CONTROLLER_HEADER
#define MOTOR_CONTROLLER_HEADER

#include <pb.h>
#include "ControllerData.pb.h"
#include "BTS7960.hpp"

class MotorController {
public:
    MotorController(const BTS7960Pins& rightMotorPins, const BTS7960Pins& leftMotorPins, const BTS7960Pins& handMotorPins);

    void initializeBTS7960s();

    void applyMotorData(const ControllerData& dataToApply);

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