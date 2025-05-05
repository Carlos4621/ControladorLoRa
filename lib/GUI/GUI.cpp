#include "GUI.hpp"

GUI::GUI(SSD1306Wire &display) 
    : display_m{ display }
{
}

struct GUI::Style {
    static constexpr uint8_t DisplayMiddle_X_Position{ 64 };
    static constexpr uint8_t DisplayMiddle_Y_Position{ 32 };

    struct Motor {
        static constexpr uint8_t LeftLabel_X{ 5 };
        static constexpr uint8_t LeftLabel_Y{ 29 };
        static constexpr uint8_t LeftValue_X{ 15 };
        static constexpr uint8_t LeftValue_Y{ 29 };

        static constexpr uint8_t RightLabel_X{ 93 };
        static constexpr uint8_t RightLabel_Y{ 29 };
        static constexpr uint8_t RightValue_X{ 103 };
        static constexpr uint8_t RightValue_Y{ 29 };
    };

    struct Camera {
        static constexpr uint8_t XLabel_X{ 44 };
        static constexpr uint8_t XLabel_Y{ 25 };
        static constexpr uint8_t XValue_X{ 60 };
        static constexpr uint8_t XValue_Y{ 25 };

        static constexpr uint8_t YLabel_X{ 44 };
        static constexpr uint8_t YLabel_Y{ 34 };
        static constexpr uint8_t YValue_X{ 60 };
        static constexpr uint8_t YValue_Y{ 35 };
    };

    struct Mode {
        static constexpr uint8_t Label_X{ 1 };
        static constexpr uint8_t Label_Y{ 51 };
        static constexpr uint8_t Value_X{ 31 };
        static constexpr uint8_t Value_Y{ 51 };
    };

    struct Fixed {
        static constexpr uint8_t Label_X{ 80 };
        static constexpr uint8_t Label_Y{ 51 };
        static constexpr uint8_t Value_X{ 109 };
        static constexpr uint8_t Value_Y{ 51 };
    };

    struct Signal {
        static constexpr uint8_t RSSILabel_X{ 1 };
        static constexpr uint8_t RSSILabel_Y{ 1 };
        static constexpr uint8_t RSSIValue_X{ 26 };
        static constexpr uint8_t RSSIValue_Y{ 1 };

        static constexpr uint8_t SNRLabel_X{ 1 };
        static constexpr uint8_t SNRLabel_Y{ 13 };
        static constexpr uint8_t SNRValue_X{ 25 };
        static constexpr uint8_t SNRValue_Y{ 13 };
    };

    struct Buttons {
        static constexpr uint8_t ALabel_X{ 56 };
        static constexpr uint8_t ALabel_Y{ 51 };
        
        static constexpr uint8_t BLabel_X{ 65 };
        static constexpr uint8_t BLabel_Y{ 51 };
        
        static constexpr uint8_t XLabel_X{ 47 };
        static constexpr uint8_t XLabel_Y{ 51 };
        
        static constexpr uint8_t YLabel_X{ 56 };
        static constexpr uint8_t YLabel_Y{ 42 };
    };
};

void GUI::displayWaitingConnection() {
    configureFont(16, TEXT_ALIGN_CENTER_BOTH);
    display_m.clear();
    display_m.drawString(Style::DisplayMiddle_X_Position, Style::DisplayMiddle_Y_Position, "Conectando...");
    display_m.display();
}

void GUI::displayConnectionSuccesfull() {
    configureFont(24, TEXT_ALIGN_CENTER_BOTH);
    display_m.clear();
    display_m.drawString(Style::DisplayMiddle_X_Position, Style::DisplayMiddle_Y_Position, "Conectado");
    display_m.display();
}

void GUI::displayError(std::string_view errorString) {
    configureFont(10, TEXT_ALIGN_LEFT);
    display_m.clear();

    std::string textToShow{ "Error:\n" };
    textToShow.append(errorString);
    textToShow.append("\n\nPlease restart");

    display_m.write(textToShow.c_str());
    display_m.display();
}

void GUI::showGUI(const ControllerData& controllerData, float RSSI, float SNR) {
    configureFont(10, TEXT_ALIGN_LEFT);
    display_m.clear();

    if (controllerData.selectedMode == Modes::Modes_FIXED_SPEED) {
        auto [rightMotorValue, leftMotorValue] = MotorController::getFixedSpeedValuesConverted(controllerData);
        
        displayLabelAndValue("L:", leftMotorValue, 
            Style::Motor::LeftLabel_X, Style::Motor::LeftLabel_Y, 
            Style::Motor::LeftValue_X, Style::Motor::LeftValue_Y);
            
        displayLabelAndValue("R:", rightMotorValue, 
            Style::Motor::RightLabel_X, Style::Motor::RightLabel_Y, 
            Style::Motor::RightValue_X, Style::Motor::RightValue_Y);
    }
    else {
        displayLabelAndValue("L:", static_cast<int8_t>(controllerData.leftJoystick.axisY), 
            Style::Motor::LeftLabel_X, Style::Motor::LeftLabel_Y, 
            Style::Motor::LeftValue_X, Style::Motor::LeftValue_Y);
            
        displayLabelAndValue("R:", static_cast<int8_t>(controllerData.rightJoystick.axisY), 
            Style::Motor::RightLabel_X, Style::Motor::RightLabel_Y, 
            Style::Motor::RightValue_X, Style::Motor::RightValue_Y);
    }

    if (controllerData.has_buttons) {
        if (controllerData.buttons.buttonA) {
            display_m.drawString(Style::Buttons::ALabel_X, Style::Buttons::ALabel_Y, "A");
        }
        
        if (controllerData.buttons.buttonB) {
            display_m.drawString(Style::Buttons::BLabel_X, Style::Buttons::BLabel_Y, "B");
        }
        
        if (controllerData.buttons.buttonX) {
            display_m.drawString(Style::Buttons::XLabel_X, Style::Buttons::XLabel_Y, "X");
        }
    }

    displayLabelAndValue("Cx:", static_cast<int8_t>(controllerData.cameraJoystick.axisX), 
        Style::Camera::XLabel_X, Style::Camera::XLabel_Y, 
        Style::Camera::XValue_X, Style::Camera::XValue_Y);
        
    displayLabelAndValue("Cy:", static_cast<int8_t>(controllerData.cameraJoystick.axisY), 
        Style::Camera::YLabel_X, Style::Camera::YLabel_Y, 
        Style::Camera::YValue_X, Style::Camera::YValue_Y);

    displayLabelAndValue("Mode:", controllerData.selectedMode,
        Style::Mode::Label_X, Style::Mode::Label_Y, 
        Style::Mode::Value_X, Style::Mode::Value_Y);
        
    displayLabelAndValue("Fixed:", static_cast<int8_t>(controllerData.fixedSpeed),
        Style::Fixed::Label_X, Style::Fixed::Label_Y, 
        Style::Fixed::Value_X, Style::Fixed::Value_Y);

    displayLabelAndValue("RSSI:", RSSI,
        Style::Signal::RSSILabel_X, Style::Signal::RSSILabel_Y, 
        Style::Signal::RSSIValue_X, Style::Signal::RSSIValue_Y, " dBm");
        
    displayLabelAndValue("SNR:", SNR,
        Style::Signal::SNRLabel_X, Style::Signal::SNRLabel_Y, 
        Style::Signal::SNRValue_X, Style::Signal::SNRValue_Y, " dB");
    
    display_m.display();
}

void GUI::configureFont(uint8_t size, OLEDDISPLAY_TEXT_ALIGNMENT alignment) {
    switch (size) {
        case 24:
            display_m.setFont(ArialMT_Plain_24);
            break;
        case 16:
            display_m.setFont(ArialMT_Plain_16);
            break;
        case 10:
        default:
            display_m.setFont(ArialMT_Plain_10);
            break;
    }
    display_m.setTextAlignment(alignment);
}

template<typename T>
void GUI::displayLabelAndValue(std::string_view label, T value, uint8_t labelX, uint8_t labelY, uint8_t valueX,
    uint8_t valueY, std::string_view suffix) {

    display_m.drawString(labelX, labelY, label.data());
    
    std::string valueStr{ std::to_string(value) };
    valueStr += suffix;
    
    display_m.drawString(valueX, valueY, valueStr.c_str());
}