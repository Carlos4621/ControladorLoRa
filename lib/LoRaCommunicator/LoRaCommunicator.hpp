#ifndef LORA_COMMUNICATOR_HEADER
#define LORA_COMMUNICATOR_HEADER

#include <heltec_unofficial.h>
#include <vector>
#include <stdexcept>
#include <span>
#include <optional>

/// @brief Struct con los parámetros de un radio LoRa
struct LoRaParameters {
    float frequencyInMHz;
    float bandwidthInKHz;

    uint8_t spreadingFactor;
    uint8_t codingRate;
    uint8_t syncWord;
    int8_t outputPowerInDBm;

    size_t preambleLength;
};

/// @brief Clase encargada del envío y recibo de series de bytes
class LoRaCommunicator {
public:

    /// @brief Constructor base
    /// @param radio Radio a usar
    explicit LoRaCommunicator(SX1262& radio);

    /// @brief Inicializa el radio con los parámetros dados
    /// @param parameters Parámetros a usar
    void initializeRadio(const LoRaParameters& parameters);

    /// @brief Envía una serie de bytes
    /// @param package Serie de bytes a enviar
    void sendPackage(std::span<const uint8_t> package);

    /// @brief Intenta recibir una serie de bytes, en caso de timeout devuelve std::nullopt
    /// @param timeoutInms Tiempo de espera antes de considerar como no recibido
    /// @param maxPacketSize Tamaño máximo del paquete a recibir. Por defecto 64
    /// @return Paquete recibido en caso satisfactorio, sino std::nullopt
    [[nodiscard]]
    std::optional<std::vector<uint8_t>> receivePackage(size_t timeoutInms, size_t maxPacketSize = 64);

    /// @brief Obtiene el RSSI del último paquete enviado o recibido
    /// @return RSSI del último paquete enviado o recibido
    [[nodiscard]]
    float getLastRSSI() const noexcept;

    /// @brief Obtiene el SNR del último paquete enviado o recibido
    /// @return SNR del último paquete enviado o recibido
    [[nodiscard]]
    float getLastSNR() const noexcept;

private:
    SX1262& radio_m;

    std::vector<uint8_t> receivedDataBuffer_m{};

    template<class ExceptionType>
    static void throwIfError(int16_t errorCode, std::string_view message);

    [[nodiscard]]
    int16_t attemptReceive(size_t timeoutInms);

    [[nodiscard]]
    static bool isRecuperableError(int16_t errorCode) noexcept;
};

template <class ExceptionType>
inline void LoRaCommunicator::throwIfError(int16_t errorCode, std::string_view message) {
    if (errorCode != RADIOLIB_ERR_NONE) {
        throw ExceptionType{ std::string(message.data()) + "\n" + std::to_string(errorCode) };
    }
}

#endif // !LORA_COMMUNICATOR_HEADER