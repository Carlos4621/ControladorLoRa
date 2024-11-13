#pragma once
#ifndef BUTTONS_COLLERCTOR_HEADER
#define BUTTONS_COLLERCTOR_HEADER

#include "Collector.hpp"
#include "Buttons.pb.h"
#include "DigitalInput.hpp"

struct ButtonsPins {
    uint8_t buttonAPin;
    uint8_t buttonBPin;
    uint8_t buttonXPin;
    uint8_t buttonYPin;
};

class ButtonsCollector : public Collector<Buttons> {
public:
    ButtonsCollector(uint8_t buttonAPin, uint8_t buttonBPin, uint8_t buttonXPin, uint8_t buttonYPin);
    explicit ButtonsCollector(const ButtonsPins& pins);

    void beginPins() override;

    [[nodiscard]]
    Buttons getData() override;

private:
    DigitalInput buttonA_m;
    DigitalInput buttonB_m;
    DigitalInput buttonX_m;
    DigitalInput buttonY_m;

};

#endif // !BUTTONS_COLLERCTOR_HEADER