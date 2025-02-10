#include "CameraDirectioner.hpp"

CameraDirectioner::CameraDirectioner(uint8_t pinHorizontalServo, uint8_t pinVerticalServo) 
    : pinHorizontalServo_m{ pinHorizontalServo }
    , pinVerticalServo_m{ pinVerticalServo }
{
}

void CameraDirectioner::beginPins() {
    horizontalServo_m.attach(pinHorizontalServo_m);
    verticalServo_m.attach(pinVerticalServo_m);
}

void CameraDirectioner::centralize() {
    horizontalServo_m.writeMicroseconds(CentralizedServoMicroseconds);
    verticalServo_m.writeMicroseconds(CentralizedServoMicroseconds);
}

void CameraDirectioner::applyDirectionData(const Joystick &controllerData) {
    applyOnServo(horizontalServo_m, controllerData.axisX);
    applyOnServo(verticalServo_m, controllerData.axisY);
}

bool CameraDirectioner::isAValidMicroseconds(int microseconds) {
    return (MinMicroseconds <= microseconds) && (microseconds <= MaxMicroseconds);
}

void CameraDirectioner::applyOnServo(Servo &servo, int32_t axisValue) {
    if (axisValue == 0) {
        return;
    }
    
    const auto currentAngle{ servo.readMicroseconds() };
    const auto objetiveAngle{ currentAngle + axisValue };

    if (isAValidMicroseconds(objetiveAngle)) {
        servo.writeMicroseconds(objetiveAngle);
    }
}
