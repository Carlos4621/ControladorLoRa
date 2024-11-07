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

class LoRaCommunicator {

    static constexpr uint8_t BUFFER_SIZE{ 16 };

public:
    LoRaCommunicator(SX1262& radio);

    void initializeRadio(const LoRaParameters& parameters);

    void sendPackage(const std::array<uint8_t, BUFFER_SIZE>& package);

    std::array<uint8_t, BUFFER_SIZE> receivePackage();
    
private:
    SX1262& radio_m;

    std::array<uint8_t, BUFFER_SIZE> receivedDataBuffer;

};

#endif // !LORA_COMMUNICATOR_HEADER