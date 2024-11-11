#pragma once
#ifndef LORA_COMMUNICATOR_HEADER
#define LORA_COMMUNICATOR_HEADER

#include <heltec_unofficial.h>
#include <vector>
#include <stdexcept>

struct LoRaParameters {
    float frequencyInMHz;
    float bandwidthInKHz;

    uint8_t spreadingFactor;
    uint8_t codingRate;
    uint8_t syncWord;
    uint8_t outputPowerInDBm;

    size_t preambleLength;
    bool enableCRC;
};

class LoRaCommunicator {
public:
    explicit LoRaCommunicator(SX1262& radio);

    void initializeRadio(const LoRaParameters& parameters);

    void sendPackage(const std::vector<uint8_t>& package);

    [[nodiscard]]
    std::vector<uint8_t> receivePackage(const size_t timeoutInms);

private:
    static constexpr size_t BUFFER_SIZE{ 32 };

    SX1262& radio_m;

    std::vector<uint8_t> receivedDataBuffer_m;

    template<class ExceptionType>
    void throwIfError(int16_t errorCode, const std::string& message);

    int16_t attemptReceive(const size_t timeoutInms);
};


template <class ExceptionType>
inline void LoRaCommunicator::throwIfError(int16_t errorCode, const std::string &message) {
    if (errorCode != RADIOLIB_ERR_NONE) {
        throw ExceptionType{ message };
    }
}

#endif // !LORA_COMMUNICATOR_HEADER