#pragma once
#ifndef BTS7960_HEADER
#define BTS7960_HEADER

#include <cstdint>
#include "AnalogOutput.hpp"
#include <stdexcept>

class BTS7960 {
public:
    BTS7960(uint8_t pinRightPWM, uint8_t pinLeftPWM);

    void configurePins();

    void setHoraryRotation(uint8_t percentage);
    void setAntihoraryRotation(uint8_t percentage);

    void stopMotor();

private:
    enum class Direction : uint8_t { Horary = 0, Antihorary };

    static constexpr uint8_t MAX_ANALOG_OUTPUT{ 255 };

    static constexpr uint8_t MAX_PERCENTAGE{ 100 };

    AnalogOutput pinRightPWM_m;
    AnalogOutput pinLeftPWM_m;

    [[nodiscard]]
    static uint8_t getConvertedAnalogOutput(uint8_t percentage) noexcept;

    void setRotation(uint8_t percentage, const Direction& direction);

    void verifyPercentageRange(uint8_t percentage);
};

#endif // !BTS7960_HEADER