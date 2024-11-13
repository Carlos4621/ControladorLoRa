#pragma once
#ifndef FIXED_SPEED_HEADER
#define FIXED_SPEED_HEADER

#include "Collector.hpp"
#include "AnalogInput.hpp"

class FixedSpeedCollector : public Collector<int32_t> {
public:
    FixedSpeedCollector(uint8_t fixedSpeedPin);

    void beginPins() override;

    [[nodiscard]]
    int32_t getData() override;

private:
    static constexpr uint16_t MIN_ANALOG_VALUE{ 0 };
    static constexpr uint16_t MAX_ANALOG_VALUE{ 4095 };

    static constexpr uint16_t MIN_FIXED_VALUE{ 0 };
    static constexpr uint16_t MAX_FIXED_VALUE{ 100 };

    AnalogInput fixedSpeed_m;

};

#endif // !FIXED_SPEED_HEADER
