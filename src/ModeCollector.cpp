#include "ModeCollector.hpp"

ModeCollector::ModeCollector(uint8_t independentModePin, uint8_t fixedModePin, uint8_t autonomousModePin)
    : independentMode_m{ independentMode_m }
    , fixedMode_m{ fixedModePin }
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
    if (independentMode_m.read()) {
        return Modes_INDEPENDENT;
    }
    else if(fixedMode_m.read()) {
        return Modes_FIXED_SPEED;
    }
    else if(autonomousMode_m.read()) {
        return Modes_AUTONOMOUS;
    }

    // TODO: quitar esto y poner algún tipo de excepción cuando no se lee ningún valor
    return Modes_INDEPENDENT;
}
