#include "MotorController.hpp"

MotorController::MotorController(const BTS7960Pins& rightMotorPins, const BTS7960Pins& leftMotorPins, const BTS7960Pins& handMotorPins) 
    : rightMotor_m{ rightMotorPins }
    , leftMotor_m{ leftMotorPins }
    , handMotor_m{ handMotorPins }
{
}

void MotorController::beginPins() {
    rightMotor_m.beginPins();
    leftMotor_m.beginPins();
    handMotor_m.beginPins();
}

void MotorController::applyMotorData(const ControllerData &dataToApply) {
    switch (dataToApply.selectedMode) {
    case Modes::Modes_INDEPENDENT:
        applyOnIndependentMode(dataToApply);
        break;

    case Modes::Modes_FIXED_SPEED:
        applyOnFixedSpeedMode(dataToApply);
        break;

    case Modes::Modes_AUTONOMOUS:
        applyOnAutonomousMode();
        break;
    
    default:
        throw std::invalid_argument{ "Invalid mode" };
        break;
    }
}

std::pair<int8_t, int8_t> MotorController::getFixedSpeedValuesConverted(const ControllerData &dataToConvert) noexcept {
    int8_t rightSpeed{ 0 };
    int8_t leftSpeed{ 0 };

    const auto& fixedSpeed{ dataToConvert.fixedSpeed };
    const auto& axisY{ dataToConvert.rightJoystick.axisY };
    const auto& axisX{ dataToConvert.rightJoystick.axisX };

    if (axisY != 0) {
        rightSpeed = leftSpeed = (axisY > 0) ? fixedSpeed : -fixedSpeed;
    } 
    else if (axisX != 0) {
        rightSpeed = (axisX > 0) ? fixedSpeed : -fixedSpeed;
        leftSpeed  = -rightSpeed;
    }

    return {rightSpeed, leftSpeed};
}


void MotorController::applyOnIndependentMode(const ControllerData &dataToApply) {
    rightMotor_m.setRelativeSpeed(dataToApply.rightJoystick.axisY);
    leftMotor_m.setRelativeSpeed(dataToApply.leftJoystick.axisY);
    handMotor_m.stopMotor();
}

void MotorController::applyOnFixedSpeedMode(const ControllerData &dataToApply) {
    const auto [rightSpeed, leftSpeed] = getFixedSpeedValuesConverted(dataToApply);

    rightMotor_m.setRelativeSpeed(rightSpeed);
    leftMotor_m.setRelativeSpeed(leftSpeed);

    handMotor_m.setRelativeSpeed(dataToApply.leftJoystick.axisY);
}

void MotorController::applyOnAutonomousMode() {
    // TODO
}
