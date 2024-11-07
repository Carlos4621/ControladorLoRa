#pragma once
#ifndef DISPLAY_HEADER
#define DISPLAY_HEADER

#include <heltec_unofficial.h>

struct GUIData {
    float RSSI;
    float SNR;
    uint8_t selectedMode;
    int8_t rightMotorValue;
    int8_t leftMotorValue;
    int8_t fixedValue;

    bool buttonA;
    bool buttonB;
    bool buttonX;
    bool buttonY;
};

class GUI {
public:
    GUI(SSD1306Wire& display);

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