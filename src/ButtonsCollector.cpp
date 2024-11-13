#include "ButtonsCollector.hpp"

ButtonsCollector::ButtonsCollector(uint8_t buttonAPin, uint8_t buttonBPin, uint8_t buttonXPin, uint8_t buttonYPin) 
    : buttonA_m{ buttonAPin }
    , buttonB_m{ buttonBPin }
    , buttonX_m{ buttonXPin }
    , buttonY_m{ buttonYPin }
{
}

ButtonsCollector::ButtonsCollector(const ButtonsPins &pins) 
    : ButtonsCollector{ pins.buttonAPin, pins.buttonBPin, pins.buttonXPin, pins.buttonYPin }
{
}

void ButtonsCollector::beginPins() {
    buttonA_m.begin();
    buttonB_m.begin();
    buttonX_m.begin();
    buttonY_m.begin();
}

Buttons ButtonsCollector::getData() {
    Buttons data = Buttons_init_zero;

    data.buttonA = buttonA_m.read();
    data.buttonB = buttonB_m.read();
    data.buttonX = buttonX_m.read();
    data.buttonY = buttonY_m.read();

    return data;
}
