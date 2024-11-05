#include "BTS7960.hpp"

BTS7960::BTS7960(uint8_t pinRPWM, uint8_t pinLPWM) 
    : pinRightPWM_m{ pinRPWM } 
    , pinLeftPWM_m{ pinLPWM }
{
}

void BTS7960::configurePins() {
    pinRightPWM_m.begin();
    pinLeftPWM_m.begin();
}

void BTS7960::setHoraryRotation(uint8_t percentage) {
    setRotation(percentage, Direction::Horary);
}

void BTS7960::setAntihoraryRotation(uint8_t percentage) {
    setRotation(percentage, Direction::Antihorary);
}

void BTS7960::stopMotor() {
    pinRightPWM_m.write(0);
    pinLeftPWM_m.write(0);
}

uint8_t BTS7960::getConvertedAnalogOutput(uint8_t percentage) const noexcept {
    return ((MAX_ANALOG_OUTPUT * percentage) / 100);
}

void BTS7960::setRotation(uint8_t percentage, const Direction &direction) {
    verifyPercentageRange(percentage);

    stopMotor();

    switch (direction) {
    case Direction::Horary:
        pinRightPWM_m.write(getConvertedAnalogOutput(percentage));
        break;

    case Direction::Antihorary:
        pinLeftPWM_m.write(getConvertedAnalogOutput(percentage));
        break;
    
    default:
        throw std::invalid_argument{ "Case not implemented" };
        break;
    }
}

void BTS7960::verifyPercentageRange(uint8_t percentage) {
    if (percentage > 100) {
        throw std::out_of_range{ "Invalid percentage" };
    }
}
