#include "ModeCollector.hpp"

ModeCollector::ModeCollector(uint8_t independentModePin, uint8_t fixedSpeedPin, uint8_t autonomousModePin)
    : independentMode_m{ independentModePin }
    , fixedMode_m{ fixedSpeedPin }
    , autonomousMode_m{ autonomousModePin }
{
}

ModeCollector::ModeCollector(const ModeSelectionPins & pins)
    : ModeCollector{ pins.independentPin, pins.fixedSpeedPin, pins.autonomousPin }
{
}

void ModeCollector::beginPins() {
    independentMode_m.begin();
    fixedMode_m.begin();
    autonomousMode_m.begin();
}

Modes ModeCollector::getData() {
    if(fixedMode_m.read()) {
        return Modes_FIXED_SPEED;
    }
    else if(autonomousMode_m.read()) {
        return Modes_AUTONOMOUS;
    }

    return Modes_INDEPENDENT;
}
