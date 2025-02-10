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

// TODO: Hacer más legible este método
std::pair<int8_t, int8_t> MotorController::getFixedSpeedValuesConverted(const ControllerData &dataToConvert) noexcept {
    int8_t rightSpeed{ 0 };
    int8_t leftSpeed{ 0 };

    if (dataToConvert.rightJoystick.axisY != 0) {
        rightSpeed = leftSpeed =
            (dataToConvert.rightJoystick.axisY > 0) ? dataToConvert.fixedSpeed: -dataToConvert.fixedSpeed;
    }
    else if (dataToConvert.rightJoystick.axisX != 0) {
        rightSpeed = (dataToConvert.rightJoystick.axisX > 0) ? dataToConvert.fixedSpeed : -dataToConvert.fixedSpeed;

        leftSpeed = (dataToConvert.rightJoystick.axisX > 0) ? -dataToConvert.fixedSpeed : dataToConvert.fixedSpeed;
    }

    return std::make_pair(rightSpeed, leftSpeed);
}

void MotorController::applyOnIndependentMode(const ControllerData &dataToApply) {
    rightMotor_m.setRelativeRotation(dataToApply.rightJoystick.axisY);
    leftMotor_m.setRelativeRotation(dataToApply.leftJoystick.axisY);
    handMotor_m.stopMotor();
}

void MotorController::applyOnFixedSpeedMode(const ControllerData &dataToApply) {
    const auto [rightSpeed, leftSpeed] = getFixedSpeedValuesConverted(dataToApply);

    rightMotor_m.setRelativeRotation(rightSpeed);
    leftMotor_m.setRelativeRotation(leftSpeed);

    handMotor_m.setRelativeRotation(dataToApply.leftJoystick.axisY);
}

void MotorController::applyOnAutonomousMode() {
    // TODO
}
