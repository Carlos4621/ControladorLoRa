#include "Receptor.hpp"

Receptor::Receptor(SX1262 &radio, SSD1306Wire &display, const BTS7960Pins &rightMotorPins, const BTS7960 &leftMotorPins) 
    : radio_m{ radio }
    , gui_m{ display }
    , rightMotor_m{ rightMotorPins }
    , leftMotor_m{ leftMotorPins }
{
}

void Receptor::initializeBTS7960Pins() {
    rightMotor_m.configurePins();
    leftMotor_m.configurePins();
}

void Receptor::initializeRadio(const LoRaParameters &params) {
    try {
        radio_m.initializeRadio(params);
    }
    catch(const std::exception& e) {
        manageError(e);
    }
}

void Receptor::start() {
    std::vector<uint8_t> receivedPackage;
    ControllerData decodedPackage;

    while (true) {
        try {
            receivedPackage = std::move(radio_m.receivePackage(RECEIVE_PACKAGE_TIMEOUT));

            if (receivedPackage.empty()) {
                manageReconnection();
            }
            else {
                applyReceivedPackage(receivedPackage);
            }  
        }
        catch(const std::exception& e) {
            manageError(e);
        }
    }
}

void Receptor::updateMotorsData(const ControllerData &data) {
    switch (data.selectedMode) {
    case Modes::Modes_INDEPENDENT:
        applyOnIndependentMode(data);
        break;
    
    case Modes::Modes_FIXED_SPEED:
        applyOnFixedSpeedMode(data);
        break;

    case Modes::Modes_AUTONOMOUS:
        // TODO: aún por hacer
        break;
    }
}

void Receptor::applyOnIndependentMode(const ControllerData &data) {
    rightMotor_m.setRelativeRotation(data.rightJoystick.axisY);
    leftMotor_m.setRelativeRotation(data.leftJoystick.axisY);
}

void Receptor::applyOnFixedSpeedMode(const ControllerData &data) {
    if (data.rightJoystick.axisY > 0) {
        rightMotor_m.setHoraryRotation(data.fixedSpeed);
        leftMotor_m.setHoraryRotation(data.fixedSpeed);
    }
    else if(data.rightJoystick.axisY < 0) {
        rightMotor_m.setAntihoraryRotation(data.fixedSpeed);
        leftMotor_m.setAntihoraryRotation(data.fixedSpeed);
    }
}

void Receptor::showDataOnGUI(const ControllerData &data) {
    GUIData toShow;

    toShow.fixedValue = data.fixedSpeed;
    toShow.buttons = data.buttons;
    toShow.selectedMode = data.selectedMode;

    toShow.RSSI = radio_m.getLastRSSI();
    toShow.SNR = radio_m.getLastSNR();
    
    if (data.selectedMode == Modes::Modes_INDEPENDENT) {
        toShow.rightMotorValue = data.rightJoystick.axisY;
        toShow.leftMotorValue = data.leftJoystick.axisY;
    }

    gui_m.showGUI(toShow);
}

void Receptor::manageReconnection() {
    gui_m.displayWaitingConnection();
}

void Receptor::manageError(const std::exception &e) {
    gui_m.displayError(e.what());

    while (true);
}

void Receptor::applyReceivedPackage(std::span<const uint8_t> receivedPackage) {
    ControllerData decodedPackage = std::move(decoder_m.decode(receivedPackage));

    showDataOnGUI(decodedPackage);

    updateMotorsData(decodedPackage);
}
