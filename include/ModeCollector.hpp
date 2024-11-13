#pragma once
#ifndef MODE_COLLECTOR_HEADER
#define MODE_COLLECTOR_HEADER

#include "Collector.hpp"
#include "DigitalInput.hpp"
#include "Modes.pb.h"

struct ModeSelectionPins {
    uint8_t independentPin;
    uint8_t fixedSpeedPin;
    uint8_t autonomousPin;
};

class ModeCollector : public Collector<Modes> {
public:
    ModeCollector(uint8_t independentModePin, uint8_t fixedModePin, uint8_t autonomousModePin);
    explicit ModeCollector(const ModeSelectionPins& pins);

    void beginPins() override;

    Modes getData() override;

private:
    DigitalInput independentMode_m;
    DigitalInput fixedMode_m;
    DigitalInput autonomousMode_m;

};

#endif // !MODE_COLLECTOR_HEADER