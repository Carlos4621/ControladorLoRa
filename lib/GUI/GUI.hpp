#ifndef GUI_HEADER
#define GUI_HEADER

#include <pb.h>
#include "Buttons.pb.h"
#include "Modes.pb.h"
#include <heltec_unofficial.h>
#include <string>
#include "MotorController.hpp"

/// @brief Clase que permite mostrar datos en patalla
class GUI {
public:

    /// @brief Constructor base
    /// @param display display a usar
    explicit GUI(SSD1306Wire& display);

    /// @brief Muestra un frame de esperando conexión
    void displayWaitingConnection();

    /// @brief Muestra un frame de conexión exitosa
    void displayConnectionSuccesfull();

    /// @brief Muestra un mensaje de error
    /// @param errorString Mensaje de error a mostrar
    void displayError(std::string_view errorString);

    /// @brief Muestra la GUI principal con los valores dados
    /// @param controllerData Data del control a mostrar
    /// @param RSSI Valor del RSSI del paquete enviado
    /// @param SNR Valor del SNR del paquete enviado
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

#endif // !GUI_HEADER