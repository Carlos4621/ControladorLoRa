#pragma once
#ifndef LORA_COMMUNICATOR_HEADER
#define LORA_COMMUNICATOR_HEADER

#include <heltec_unofficial.h>
#include <vector>
#include <stdexcept>
#include <span>
#include <optional>

struct LoRaParameters {
    float frequencyInMHz;
    float bandwidthInKHz;

    uint8_t spreadingFactor;
    uint8_t codingRate;
    uint8_t syncWord;
    int8_t outputPowerInDBm;

    size_t preambleLength;
};

class LoRaCommunicator {
public:
    explicit LoRaCommunicator(SX1262& radio);

    void initializeRadio(const LoRaParameters& parameters);

    void sendPackage(std::span<const uint8_t> package);

    [[nodiscard]]
    std::optional<std::vector<uint8_t>> receivePackage(size_t timeoutInms);

    [[nodiscard]]
    float getLastRSSI() const noexcept;

    [[nodiscard]]
    float getLastSNR() const noexcept;

private:
    static constexpr size_t BUFFER_SIZE{ 32 };

    SX1262& radio_m;

    std::vector<uint8_t> receivedDataBuffer_m{};

    template<class ExceptionType>
    static void throwIfError(int16_t errorCode, std::string_view message);

    int16_t attemptReceive(size_t timeoutInms);

    static bool isRecuperableError(int16_t errorCode) noexcept;
};

template <class ExceptionType>
inline void LoRaCommunicator::throwIfError(int16_t errorCode, std::string_view message) {
    if (errorCode != RADIOLIB_ERR_NONE) {
        throw ExceptionType{ std::string(message.data()) + "\n" + std::to_string(errorCode) };
    }
}

#endif // !LORA_COMMUNICATOR_HEADER