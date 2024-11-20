#pragma once
#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <pb.h>
#include "Buttons.pb.h"
#include "Modes.pb.h"
#include <heltec_unofficial.h>
#include <string>
#include "MotorController.hpp"

class GUI {
public:
    explicit GUI(SSD1306Wire& display);

    void displayWaitingConnection();

    void displayConnectionSuccesfull();

    void displayError(std::string_view errorString);

    void showGUI(const ControllerData& controllerData, float RSSI, float SNR);

private:
    struct Style;

    SSD1306Wire& display_m;

    void configureConnectingWaitingFont();
    void configureConnectionSuccesfullFont();
    void configureErrorFont();
    void configureGUIFont();

    void displayRightMotorData(int8_t value);
    void displayLeftMotorData(int8_t value);
    void displaySelectedMode(uint8_t value);
    void displayFixedValue(int8_t value);
    void displayRSSIData(float value);
    void displaySNRData(float value);
};

#endif // !DISPLAY_HEADER