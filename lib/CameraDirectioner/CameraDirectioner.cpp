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
    horizontalServo_m.write(CentralizedAngle);
    verticalServo_m.write(CentralizedAngle);
}

void CameraDirectioner::applyDirectionData(const Joystick &controllerData) {
    applyOnServo(horizontalServo_m, controllerData.axisX);
    applyOnServo(verticalServo_m, controllerData.axisY);
}

bool CameraDirectioner::isAValidMicroseconds(int microseconds) {
    return (MinAngle <= microseconds) && (microseconds <= MaxAngle);
}

void CameraDirectioner::applyOnServo(Servo &servo, int32_t axisValue) {
    if (axisValue == 0) {
        return;
    }

    const auto currentAngle{ servo.read() };
    const auto objetiveAngle{ currentAngle + (axisValue / AngleStep) };

    if (isAValidMicroseconds(objetiveAngle)) {
        servo.write(objetiveAngle);
    }
}
