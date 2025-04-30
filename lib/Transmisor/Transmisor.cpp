#include "Transmisor.hpp"

Transmisor::Transmisor(SX1262 &radio, SSD1306Wire &display, const JoystickPins &rightJoystickPins, const JoystickPins &leftJoystickPins, 
const JoystickPins &cameraJoystickPin, const ButtonsPins &buttonsPins, const ModeSelectionPins &modeSelectionPins, uint8_t fixedSpeedPin) 
    : radio_m{ radio }
    , gui_m{ display }
    , collector_m{ rightJoystickPins, leftJoystickPins, cameraJoystickPin, buttonsPins, modeSelectionPins, fixedSpeedPin }
{
}

void Transmisor::initializeRadio(const LoRaParameters &params) {
    radio_m.initializeRadio(params);
}

void Transmisor::initializePins() {
    collector_m.beginPins();
}

void Transmisor::start() {
    ControllerData data;
    std::vector<uint8_t> encodedData;

    while (true) {
        data = collector_m.getControllerData();

        gui_m.showGUI(data, radio_m.getLastRSSI(), radio_m.getLastSNR());

        encodedData = encoder_m.encode(data);

        radio_m.sendPackage(encodedData);

        delay(50);
    }
    
}
