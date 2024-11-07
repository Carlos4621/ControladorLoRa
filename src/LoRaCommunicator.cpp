#include "LoRaCommunicator.hpp"

LoRaCommunicator::LoRaCommunicator(SX1262 &radio)
    : radio_m{ radio }
{
}

void LoRaCommunicator::initializeRadio(const LoRaParameters& parameters) {

    const int16_t radioInitialized{ radio_m.begin(
    parameters.frecuencyInMHz,
    parameters.bandwidhtInKHz, 
    parameters.spreadingFactor,
    parameters.codingRate, 
    parameters.syncWord,
    parameters.outputPowerInDBm,
    parameters.preambleLenght)
    };

    if (radioInitialized != RADIOLIB_ERR_NONE) {
        throw std::invalid_argument{ "Unable to initialize Radio with the given parameters" };
    }
}

void LoRaCommunicator::sendPackage(const std::array<uint8_t, BUFFER_SIZE>& package) {
    const int16_t transmisionState{ radio_m.transmit(package.data(), package.size()) };

    if (transmisionState != RADIOLIB_ERR_NONE) {
        throw std::runtime_error{ "Unable to send the package" };
    }
}

std::array<uint8_t, LoRaCommunicator::BUFFER_SIZE> LoRaCommunicator::receivePackage() {
    int16_t receiveState{ radio_m.receive(receivedDataBuffer.data(), receivedDataBuffer.size()) };

    while (receiveState == RADIOLIB_ERR_RX_TIMEOUT) {
        delay(10);
        receiveState = radio_m.receive(receivedDataBuffer.data(), receivedDataBuffer.size());
    }
    

    return receivedDataBuffer;
}
