#pragma once
#ifndef LORA_COMMUNICATOR_HEADER
#define LORA_COMMUNICATOR_HEADER

#include <heltec_unofficial.h>
#include <array>

struct LoRaParameters {
    float frecuencyInMHz;
    float bandwidhtInKHz;

    uint8_t spreadingFactor;
    uint8_t codingRate;
    uint8_t syncWord;
    uint8_t outputPowerInDBm;

    size_t preambleLenght;
    bool enableCRC;
};

template<size_t PackageLenght>
class LoRaCommunicator {
public:
    explicit LoRaCommunicator(SX1262& radio);

    void initializeRadio(const LoRaParameters& parameters);

    void sendPackage(const std::array<uint8_t, PackageLenght>& package);

    [[nodiscard]]
    std::array<uint8_t, PackageLenght> receivePackage(size_t timeoutInms);

private:
    SX1262& radio_m;

    std::array<uint8_t, PackageLenght> receivedDataBuffer;
};

template<size_t PackageLenght>
inline LoRaCommunicator<PackageLenght>::LoRaCommunicator(SX1262 &radio)
    : radio_m{ radio }
{
}

template<size_t PackageLenght>
inline void LoRaCommunicator<PackageLenght>::initializeRadio(const LoRaParameters& parameters) {
    const int16_t radioStatus{ 
        radio_m.begin(
            parameters.frecuencyInMHz,
            parameters.bandwidhtInKHz, 
            parameters.spreadingFactor,
            parameters.codingRate, 
            parameters.syncWord,
            parameters.outputPowerInDBm,
            parameters.preambleLenght
        )
    };

    if (radioStatus != RADIOLIB_ERR_NONE) {
        throw std::invalid_argument{ "Unable to initialize Radio with the given parameters" };
    }
}

template <size_t PackageLenght>
inline void LoRaCommunicator<PackageLenght>::sendPackage(const std::array<uint8_t, PackageLenght> &package) {
    const int16_t transmisionStatus{ radio_m.transmit(package.data(), package.size()) };

    if (transmisionStatus != RADIOLIB_ERR_NONE) {
        throw std::runtime_error{ "Unable to send the package" };
    }
}

template <size_t PackageLenght>
inline std::array<uint8_t, PackageLenght> LoRaCommunicator<PackageLenght>::receivePackage(size_t timeoutInms) {
    const uint32_t startTime{ millis() };
    uint32_t timeElapsed{ 0 };

    int16_t receiveStatus{ radio_m.receive(receivedDataBuffer.data(), receivedDataBuffer.size()) };

    while ((timeElapsed < timeoutInms) && (receiveStatus == RADIOLIB_ERR_RX_TIMEOUT)) {
        receiveStatus = radio_m.receive(receivedDataBuffer.data(), receivedDataBuffer.size());

        timeElapsed = (millis() - startTime);
        delay(1);
    }

    if (receiveStatus != RADIOLIB_ERR_NONE) {
        throw std::runtime_error{ "Unable to receive the package" };
    }
    
    return receivedDataBuffer;
}

#endif // !LORA_COMMUNICATOR_HEADER
