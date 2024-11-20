#pragma once
#ifndef RECEPTOR_HEADER
#define RECEPTOR_HEADER

#include "BTS7960.hpp"
#include "LoRaCommunicator.hpp"
#include "GUI.hpp"
#include "ControllerDataDecoder.hpp"

class Receptor {
public:
    Receptor(SX1262& radio, SSD1306Wire& display, const BTS7960Pins& rightMotorPins, const BTS7960& leftMotorPins);

    void initializeBTS7960Pins();
    void initializeRadio(const LoRaParameters& params);

    [[noreturn]]
    void start();

private:
    static constexpr size_t RECEIVE_PACKAGE_TIMEOUT{ 200 };

    GUI gui_m;
    LoRaCommunicator radio_m;

    ControllerDataDecoder decoder_m;
    
    BTS7960 rightMotor_m;
    BTS7960 leftMotor_m;

    void updateMotorsData(const ControllerData& data);

    void applyOnIndependentMode(const ControllerData& data);
    void applyOnFixedSpeedMode(const ControllerData& data);

    void showDataOnGUI(const ControllerData& data);

    void manageReconnection();

    [[noreturn]]
    void manageError(const std::exception& e);

    void applyReceivedPackage(std::span<const uint8_t> receivedPackage);
};

#endif // !RECEPTOR_HEADER