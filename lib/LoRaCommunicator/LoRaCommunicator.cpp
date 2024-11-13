#include "LoRaCommunicator.hpp"

LoRaCommunicator::LoRaCommunicator(SX1262 &radio)
    : radio_m{ radio }
    , receivedDataBuffer_m(BUFFER_SIZE)
{
}

void LoRaCommunicator::initializeRadio(const LoRaParameters& parameters) {
    const int16_t radioStatus{ 
        radio_m.begin(
            parameters.frequencyInMHz,
            parameters.bandwidthInKHz, 
            parameters.spreadingFactor,
            parameters.codingRate, 
            parameters.syncWord,
            parameters.outputPowerInDBm,
            parameters.preambleLength
        )
    };

    throwIfError<std::invalid_argument>(radioStatus, "Unable to initialize Radio with the given arguments");
}

void LoRaCommunicator::sendPackage(std::span<const uint8_t> package) {
    const int16_t transmisionStatus{ radio_m.transmit(package.data(), package.size()) };

    throwIfError<std::runtime_error>(transmisionStatus, "Unable to send the package");
}

std::vector<uint8_t> LoRaCommunicator::receivePackage(size_t timeoutInms) {
    receivedDataBuffer_m.resize(BUFFER_SIZE);

    const int16_t receiveStatus{ attemptReceive(timeoutInms) };

    throwIfError<std::runtime_error>(receiveStatus, "Unable to receive the package");

    receivedDataBuffer_m.resize(radio_m.getPacketLength(true));
    
    return receivedDataBuffer_m;
}

int16_t LoRaCommunicator::attemptReceive(size_t timeoutInms) {
    const uint32_t startTime{ millis() };
    uint32_t timeElapsed{ 0 };

    int16_t receiveStatus{ radio_m.receive(receivedDataBuffer_m.data(), receivedDataBuffer_m.size()) };

    while ((timeElapsed < timeoutInms) && (receiveStatus == RADIOLIB_ERR_RX_TIMEOUT)) {
        receiveStatus = radio_m.receive(receivedDataBuffer_m.data(), receivedDataBuffer_m.size());

        timeElapsed = (millis() - startTime);
        delay(1);
    }

    return receiveStatus;
}
