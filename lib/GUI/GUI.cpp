#include "GUI.hpp"

GUI::GUI(SSD1306Wire &display) 
    : display_m{ display }
{
}

struct GUI::Style {
    static constexpr uint8_t DisplayMiddle_X_Position{ 64 };
    static constexpr uint8_t DisplayMiddle_Y_Position{ 32 };


    static constexpr uint8_t LeftLabel_X_Position{ 17 };
    static constexpr uint8_t LeftLabel_Y_Position{ 34 };

    static constexpr uint8_t LeftMotorValue_X_Position{ 40 };
    static constexpr uint8_t LeftMotorValue_Y_Position{ 34 };


    static constexpr uint8_t RightLabel_X_Position{ 66 };
    static constexpr uint8_t RightLabel_Y_Position{ 34 };

    static constexpr uint8_t RightMotorValue_X_Position{ 94 };
    static constexpr uint8_t RightMotorValue_Y_Position{ 34 };


    static constexpr uint8_t ModeLabel_X_Position{ 0 };
    static constexpr uint8_t ModeLabel_Y_Position{ 52 };

    static constexpr uint8_t ModeSelected_X_Position{ 31 };
    static constexpr uint8_t ModeSelected_Y_Position{ 52 };


    static constexpr uint8_t FixedLabel_X_Position{ 77 };
    static constexpr uint8_t FixedLabel_Y_Position{ 52 };

    static constexpr uint8_t FixedValue_X_Position{ 107 };
    static constexpr uint8_t FixedValue_Y_Position{ 52 };


    static constexpr uint8_t RSSILabel_X_Position{ 0 };
    static constexpr uint8_t RSSILabel_Y_Position{ 0 };

    static constexpr uint8_t RSSIValue_X_Position{ 26 };
    static constexpr uint8_t RSSIValue_Y_Position{ 0 };


    static constexpr uint8_t SNRLabel_X_Position{ 0 };
    static constexpr uint8_t SNRLabel_Y_Position{ 12 };

    static constexpr uint8_t SNRValue_X_Position{ 24 };
    static constexpr uint8_t SNRValue_Y_Position{ 12 };
};

void GUI::displayWaitingConnection() {
    configureConnectingWaitingFont();

    display_m.clear();

    display_m.drawString(Style::DisplayMiddle_X_Position, Style::DisplayMiddle_Y_Position, "Conectando...");

    display_m.display();
}

void GUI::displayConnectionSuccesfull() {
    configureConnectionSuccesfullFont();

    display_m.clear();

    display_m.drawString(Style::DisplayMiddle_X_Position, Style::DisplayMiddle_Y_Position, "Conectado");

    display_m.display();
}

void GUI::displayError(std::string_view errorString) {
    configureErrorFont();

    display_m.clear();

    std::string textToShow{ "Error:\n" };

    textToShow.append(errorString);
    textToShow.append("\n\nPlease restart");

    display_m.write(textToShow.c_str());

    display_m.display();
}

void GUI::showGUI(const ControllerData& controllerData, float RSSI, float SNR) {
    configureGUIFont();

    display_m.clear();

    if (controllerData.selectedMode == Modes::Modes_FIXED_SPEED) {
        auto [rightMotorValue, leftMotorValue] = MotorController::getFixedSpeedValuesConverted(controllerData);

        displayLeftMotorData(leftMotorValue);
        displayRightMotorData(rightMotorValue);
    }
    else {
        displayLeftMotorData(static_cast<int8_t>(controllerData.leftJoystick.axisY));
        displayRightMotorData(static_cast<int8_t>(controllerData.rightJoystick.axisY));
    }

    displaySelectedMode(controllerData.selectedMode);
    displayFixedValue(static_cast<int8_t>(controllerData.fixedSpeed));

    displayRSSIData(RSSI);
    displaySNRData(SNR);
    
    display_m.display();
}

void GUI::configureConnectingWaitingFont() {
    display_m.setFont(ArialMT_Plain_16);
    display_m.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
}

void GUI::configureConnectionSuccesfullFont() {
    display_m.setFont(ArialMT_Plain_24);
    display_m.setTextAlignment(TEXT_ALIGN_CENTER_BOTH);
}

void GUI::configureErrorFont() {
    display_m.setFont(ArialMT_Plain_10);
    display_m.setTextAlignment(TEXT_ALIGN_LEFT);
}

void GUI::configureGUIFont() {
    display_m.setFont(ArialMT_Plain_10);
    display_m.setTextAlignment(TEXT_ALIGN_LEFT);
}

void GUI::displayRightMotorData(int8_t value) {
    display_m.drawString(Style::RightLabel_X_Position, Style::RightLabel_Y_Position, "Right:");
    display_m.drawString(Style::RightMotorValue_X_Position, Style::RightLabel_Y_Position, std::to_string(value).c_str());
}

void GUI::displayLeftMotorData(int8_t value) {
    display_m.drawString(Style::LeftLabel_X_Position, Style::LeftLabel_Y_Position, "Left:");
    display_m.drawString(Style::LeftMotorValue_X_Position, Style::LeftMotorValue_Y_Position, std::to_string(value).c_str());
}

void GUI::displaySelectedMode(uint8_t value) {
    display_m.drawString(Style::ModeLabel_X_Position, Style::ModeLabel_Y_Position, "Mode:");
    display_m.drawString(Style::ModeSelected_X_Position, Style::ModeLabel_Y_Position, std::to_string(value).c_str());
}

void GUI::displayFixedValue(int8_t value) {
    display_m.drawString(Style::FixedLabel_X_Position, Style::FixedLabel_Y_Position, "Fixed:");
    display_m.drawString(Style::FixedValue_X_Position, Style::FixedValue_Y_Position, std::to_string(value).c_str());
}

void GUI::displayRSSIData(float value) {

    std::string textToShow{ std::to_string(value) };

    textToShow += " dBm";

    display_m.drawString(Style::RSSILabel_X_Position, Style::RSSILabel_Y_Position, "RSSI:");
    display_m.drawString(Style::RSSIValue_X_Position, Style::RSSIValue_Y_Position, textToShow.c_str());
}

void GUI::displaySNRData(float value) {

    std::string textToShow{ std::to_string(value) };

    textToShow += " dB";

    display_m.drawString(Style::SNRLabel_X_Position, Style::SNRLabel_Y_Position, "SNR:");
    display_m.drawString(Style::SNRValue_X_Position, Style::SNRValue_Y_Position, textToShow.c_str());
}
