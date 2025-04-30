#ifndef TRANSMISOR_HEADER
#define TRANSMISOR_HEADER

#include "GUI.hpp"
#include "LoRaCommunicator.hpp"
#include "ControllerCollector.hpp"
#include "ControllerDataEncoder.hpp"

/// @brief Clase encargada de transmitir los datos de los joysticks y botones al receptor.
class Transmisor {
public:

    /// @brief Constructor base
    /// @param radio Instancia de radio a usar
    /// @param display Instancia de display a usar 
    /// @param rightJoystickPins Pins del joystick derecho
    /// @param leftJoystickPins Pins del joystick izquierdo
    /// @param cameraJoystickPin Pins del joystick de la cámara
    /// @param buttonsPins Pins de los botones
    /// @param modeSelectionPins Pins del switch de selección de modo
    /// @param fixedSpeedPin Pins del potenciómetro de velocidad fija
    Transmisor(SX1262& radio, SSD1306Wire& display, const JoystickPins& rightJoystickPins, const JoystickPins& leftJoystickPins, 
        const JoystickPins& cameraJoystickPin, const ButtonsPins& buttonsPins, const ModeSelectionPins& modeSelectionPins, uint8_t fixedSpeedPin);

    /// @brief Inicializa el radio con los parámetros dados
    /// @param params Parámetros de LoRa a usar
    void initializeRadio(const LoRaParameters& params);

    /// @brief Inicializa los pines de los joysticks y botones
    void initializePins();

    /// @brief Bucle principal de la aplicación
    [[noreturn]]
    void start();

private:
    GUI gui_m;
    LoRaCommunicator radio_m;

    ControllerCollector collector_m;

    ControllerDataEncoder encoder_m;
};

#endif // !TRANSMISOR_HEADER