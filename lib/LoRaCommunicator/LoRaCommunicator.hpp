#pragma once
#ifndef LORA_COMMUNICATOR_HEADER
#define LORA_COMMUNICATOR_HEADER

#include <heltec_unofficial.h>
#include <vector>
#include <stdexcept>
#include <span>

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
    std::vector<uint8_t> receivePackage(size_t timeoutInms);

private:
    static constexpr size_t BUFFER_SIZE{ 32 };

    SX1262& radio_m;

    std::vector<uint8_t> receivedDataBuffer_m{};

    template<class ExceptionType>
    void throwIfError(int16_t errorCode, std::string_view message);

    int16_t attemptReceive(size_t timeoutInms);
};

template <class ExceptionType>
inline void LoRaCommunicator::throwIfError(int16_t errorCode, std::string_view message) {
    if (errorCode != RADIOLIB_ERR_NONE) {
        #ifdef EXCEPTIONS_ENABLED
        throw ExceptionType{ message.data() };
        #endif

        receivedDataBuffer_m.clear();
    }
}

#endif // !LORA_COMMUNICATOR_HEADER