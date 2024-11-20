#pragma once
#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <pb.h>
#include "Buttons.pb.h"
#include "Modes.pb.h"
#include <heltec_unofficial.h>
#include <string>

struct GUIData {
    float RSSI;
    float SNR;
    Modes selectedMode;
    int8_t rightMotorValue;
    int8_t leftMotorValue;
    int8_t fixedValue;

    Buttons buttons;
};

class GUI {
public:
    explicit GUI(SSD1306Wire& display);

    void displayConnectingWaiting();

    void displayConnectionSuccesfull();

    void showGUI(const GUIData& data);

private:

    struct Style;

    SSD1306Wire& display_m;

    void configureConnectingWaitingFont();
    void configureConnectionSuccesfullFont();
    void configureGUIFont();

    void displayRightMotorData(int8_t value);
    void displayLeftMotorData(int8_t value);
    void displaySelectedMode(uint8_t value);
    void displayFixedValue(int8_t value);
    void displayRSSIData(float value);
    void displaySNRData(float value);
};

#endif // !DISPLAY_HEADER