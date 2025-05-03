#ifndef GUI_HEADER
#define GUI_HEADER

#include <pb.h>
#include "Buttons.pb.h"
#include "Modes.pb.h"
#include <heltec_unofficial.h>  
#include <string>
#include <string_view>
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
    struct DisplayElement;

    SSD1306Wire& display_m;

    void configureFont(uint8_t size, OLEDDISPLAY_TEXT_ALIGNMENT alignment);
    
    template<typename T>
    void displayLabelAndValue(std::string_view label, T value, uint8_t labelX, uint8_t labelY, uint8_t valueX,
        uint8_t valueY, std::string_view suffix = "");
};

#endif // !GUI_HEADER