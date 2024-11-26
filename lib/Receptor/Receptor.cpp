#include "Receptor.hpp"

Receptor::Receptor(SX1262 &radio, SSD1306Wire &display, const BTS7960Pins &rightMotorPins, const BTS7960Pins &leftMotorPins, const BTS7960Pins& handMotorPins)
    : radio_m{ radio }
    , gui_m{ display }
    , motorController_m{ rightMotorPins, leftMotorPins, handMotorPins }
{
}

void Receptor::initializeBTS7960Pins() {
    motorController_m.beginPins();
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
    std::optional<std::vector<uint8_t>> receivedPackage;

    while (true) {
        try {
            receivedPackage = std::move(radio_m.receivePackage(RECEIVE_PACKAGE_TIMEOUT));

            if (!receivedPackage.has_value()) {
                manageReconnection();
            }
            else {
                applyReceivedPackage(receivedPackage.value());
            }
        }
        catch(const std::exception& e) {
            manageError(e);
        }
    }
}

void Receptor::showDataOnGUI(const ControllerData &data) {
    gui_m.showGUI(data, radio_m.getLastRSSI(), radio_m.getLastSNR());
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

    motorController_m.applyMotorData(decodedPackage);
}
