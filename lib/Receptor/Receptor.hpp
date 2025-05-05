#ifndef RECEPTOR_HEADER
#define RECEPTOR_HEADER

#include "BTS7960.hpp"
#include "LoRaCommunicator.hpp"
#include "GUI.hpp"
#include "ControllerDataDecoder.hpp"
#include "MotorController.hpp"
#include "CameraDirectioner.hpp"

/// @brief Clase que representa el receptor del robot.
class Receptor {
public:

    /// @brief Constructor base
    /// @param radio Radio LoRa a usar
    /// @param display Display OLED a usar
    /// @param rightMotorPins Pines del motor derecho
    /// @param leftMotorPins Pines del motor izquierdo
    /// @param handMotorPins Pines del motor de la mano
    /// @param horizontalCameraServoPin Pines del movimiento horizontal de la cámara
    /// @param verticalCameraServoPin Pines del movimiento vertical de la cámara
    Receptor(SX1262& radio, SSD1306Wire& display, const BTS7960Pins& rightMotorPins, const BTS7960Pins& leftMotorPins, const BTS7960Pins& handMotorPins, 
        uint8_t horizontalCameraServoPin, uint8_t verticalCameraServoPin);

    /// @brief Inicializa los pines de los motores y la cámara.
    void initializePins();

    /// @brief Inicializa el radio con los parámetros dados
    /// @param params Parámetros a usar
    void initializeRadio(const LoRaParameters& params);

    /// @brief Cambia el tiempo de espera para recibir paquetes antes de considerarse como no recibido. Default = 1000ms
    /// @param timeoutInMs Nuevo tiempo de espera en milisegundos
    void changeTimeoutForReceivePackage(size_t timeoutInMs);

    /// @brief Inicia el receptor
    [[noreturn]]
    void start();

private:
    size_t receivePackageTimeoutInMs_m{ 1000 };

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