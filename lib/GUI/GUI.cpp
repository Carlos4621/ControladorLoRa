#include "GUI.hpp"

GUI::GUI(SSD1306Wire &display) 
    : display_m{ display }
{
}

struct GUI::Style {
    static constexpr uint8_t DISPLAY_MIDDLE_X_POSITION{ 64 };
    static constexpr uint8_t DISPLAY_MIDDLE_Y_POSITION{ 32 };

    static constexpr uint8_t LEFT_LABEL_X_POSITION{ 17 };
    static constexpr uint8_t LEFT_LABEL_Y_POSITION{ 34 };

    static constexpr uint8_t LEFT_MOTOR_VALUE_X_POSITION{ 40 };
    static constexpr uint8_t LEFT_MOTOR_VALUE_Y_POSITION{ 34 };


    static constexpr uint8_t RIGHT_LABEL_X_POSITION{ 66 };
    static constexpr uint8_t RIGHT_LABEL_Y_POSITION{ 34 };

    static constexpr uint8_t RIGHT_MOTOR_VALUE_X_POSITION{ 94 };
    static constexpr uint8_t RIGHT_MOTOR_VALUE_Y_POSITION{ 34 };


    static constexpr uint8_t MODE_LABEL_X_POSITION{ 0 };
    static constexpr uint8_t MODE_LABEL_Y_POSITION{ 52 };

    static constexpr uint8_t MODE_SELECTED_X_POSITION{ 31 };
    static constexpr uint8_t MODE_SELECTED_Y_POSITION{ 52 };


    static constexpr uint8_t FIXED_LABEL_X_POSITION{ 77 };
    static constexpr uint8_t FIXED_LABEL_Y_POSITION{ 52 };

    static constexpr uint8_t FIXED_VALUE_X_POSITION{ 107 };
    static constexpr uint8_t FIXED_VALUE_Y_POSITION{ 52 };


    static constexpr uint8_t RRSI_LABEL_X_POSITION{ 0 };
    static constexpr uint8_t RRSI_LABEL_Y_POSITION{ 0 };

    static constexpr uint8_t RRSI_VALUE_X_POSITION{ 26 };
    static constexpr uint8_t RRSI_VALUE_Y_POSITION{ 0 };


    static constexpr uint8_t SNR_LABEL_X_POSITION{ 0 };
    static constexpr uint8_t SNR_LABEL_Y_POSITION{ 12 };

    static constexpr uint8_t SNR_VALUE_X_POSITION{ 24 };
    static constexpr uint8_t SNR_VALUE_Y_POSITION{ 12 };
};

void GUI::displayWaitingConnection() {
    configureConnectingWaitingFont();

    display_m.clear();

    display_m.drawString(Style::DISPLAY_MIDDLE_X_POSITION, Style::DISPLAY_MIDDLE_Y_POSITION, "Conectando...");

    display_m.display();
}

void GUI::displayConnectionSuccesfull() {
    configureConnectionSuccesfullFont();

    display_m.clear();

    display_m.drawString(Style::DISPLAY_MIDDLE_X_POSITION, Style::DISPLAY_MIDDLE_Y_POSITION, "Conectado");

    display_m.display();
}

void GUI::displayError(std::string_view errorString) {
    configureErrorFont();

    display_m.clear();

    std::string textToShow{ "Error: " };

    textToShow.append(errorString);
    textToShow.append("\nPlease restart");

    display_m.write(textToShow.c_str());
}

void GUI::showGUI(const GUIData& data) {
    configureGUIFont();

    display_m.clear();

    displayLeftMotorData(data.leftMotorValue);
    displayRightMotorData(data.rightMotorValue);
   
    displaySelectedMode(data.selectedMode);
    displayFixedValue(data.fixedValue);
;
    displayRSSIData(data.RSSI);
    displaySNRData(data.SNR);
    
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
    display.setTextAlignment(TEXT_ALIGN_LEFT);
}

void GUI::configureGUIFont() {
    display_m.setFont(ArialMT_Plain_10);
    display_m.setTextAlignment(TEXT_ALIGN_LEFT);
}

void GUI::displayRightMotorData(int8_t value) {
    display_m.drawString(Style::RIGHT_LABEL_X_POSITION, Style::RIGHT_LABEL_Y_POSITION, "Right:");
    display_m.drawString(Style::RIGHT_MOTOR_VALUE_X_POSITION, Style::RIGHT_LABEL_Y_POSITION, std::to_string(value).c_str());
}

void GUI::displayLeftMotorData(int8_t value) {
    display_m.drawString(Style::LEFT_LABEL_X_POSITION, Style::LEFT_LABEL_Y_POSITION, "Left:");
    display_m.drawString(Style::LEFT_MOTOR_VALUE_X_POSITION, Style::LEFT_MOTOR_VALUE_Y_POSITION, std::to_string(value).c_str());
}

void GUI::displaySelectedMode(uint8_t value) {
    display_m.drawString(Style::MODE_LABEL_X_POSITION, Style::MODE_LABEL_Y_POSITION, "Mode:");
    display_m.drawString(Style::MODE_SELECTED_X_POSITION, Style::MODE_LABEL_Y_POSITION, std::to_string(value).c_str());
}

void GUI::displayFixedValue(int8_t value) {
    display_m.drawString(Style::FIXED_LABEL_X_POSITION, Style::FIXED_LABEL_Y_POSITION, "Fixed:");
    display_m.drawString(Style::FIXED_VALUE_X_POSITION, Style::FIXED_VALUE_Y_POSITION, std::to_string(value).c_str());
}

void GUI::displayRSSIData(float value) {

    std::string textToShow{ std::to_string(value) };

    textToShow += " dBm";

    display_m.drawString(Style::RRSI_LABEL_X_POSITION, Style::RRSI_LABEL_Y_POSITION, "RSSI:");
    display_m.drawString(Style::RRSI_VALUE_X_POSITION, Style::RRSI_VALUE_Y_POSITION, textToShow.c_str());
}

void GUI::displaySNRData(float value) {

    std::string textToShow{ std::to_string(value) };

    textToShow += " dB";

    display_m.drawString(Style::SNR_LABEL_X_POSITION, Style::SNR_LABEL_Y_POSITION, "SNR:");
    display_m.drawString(Style::SNR_VALUE_X_POSITION, Style::SNR_VALUE_Y_POSITION, textToShow.c_str());
}
