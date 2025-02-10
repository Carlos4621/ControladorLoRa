#pragma once
#ifndef RECEPTOR_HEADER
#define RECEPTOR_HEADER

#include "BTS7960.hpp"
#include "LoRaCommunicator.hpp"
#include "GUI.hpp"
#include "ControllerDataDecoder.hpp"
#include "MotorController.hpp"
#include "CameraDirectioner.hpp"

class Receptor {
public:
    Receptor(SX1262& radio, SSD1306Wire& display, const BTS7960Pins& rightMotorPins, const BTS7960Pins& leftMotorPins, const BTS7960Pins& handMotorPins, 
        uint8_t horizontalCameraServoPin, uint8_t verticalCameraServoPin);

    void initializeBTS7960Pins();
    void initializeRadio(const LoRaParameters& params);

    [[noreturn]]
    void start();

private:
    static constexpr size_t ReceivePackageTimeoutInMs{ 200 };

    GUI gui_m;
    LoRaCommunicator radio_m;

    ControllerDataDecoder decoder_m;
    
    MotorController motorController_m;
    CameraDirectioner cameraDirectioner_m;

    void showDataOnGUI(const ControllerData& data);

    void manageReconnection();

    [[noreturn]]
    void manageError(const std::exception& e);

    void applyReceivedPackage(std::span<const uint8_t> receivedPackage);
};

#endif // !RECEPTOR_HEADER