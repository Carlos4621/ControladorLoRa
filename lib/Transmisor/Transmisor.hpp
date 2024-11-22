#pragma once
#ifndef TRANSMISOR_HEADER
#define TRANSMISOR_HEADER

#include "GUI.hpp"
#include "LoRaCommunicator.hpp"
#include "ControllerCollector.hpp"
#include "ControllerDataEncoder.hpp"

class Transmisor {
public:
    Transmisor(SX1262& radio, SSD1306Wire& display, const JoystickPins& rightJoystickPins, const JoystickPins& leftJoystickPins, 
    const ButtonsPins& buttonsPins, const ModeSelectionPins& modeSelectionPins, uint8_t fixedSpeedPin);

    void initializeRadio(const LoRaParameters& params);

    void initializePins();

    [[noreturn]]
    void start();

private:
    GUI gui_m;
    LoRaCommunicator radio_m;

    ControllerCollector collector_m;

    ControllerDataEncoder encoder_m;
};

#endif // !TRANSMISOR_HEADER