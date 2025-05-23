#include "LoRaCommunicator.hpp"

LoRaCommunicator::LoRaCommunicator(SX1262 &radio)
    : radio_m{ radio }
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

std::optional<std::vector<uint8_t>> LoRaCommunicator::receivePackage(size_t timeoutInms, size_t maxPacketSize) {
    receivedDataBuffer_m.resize(maxPacketSize);

    const int16_t receiveStatus{ attemptReceive(timeoutInms) };

    if (isRecuperableError(receiveStatus)) {
        return std::nullopt;
    }

    throwIfError<std::runtime_error>(receiveStatus, "Unable to receive the package");

    return std::vector<uint8_t>(receivedDataBuffer_m.begin(), receivedDataBuffer_m.begin() + radio_m.getPacketLength());
}

float LoRaCommunicator::getLastRSSI() const noexcept {
    return radio_m.getRSSI();
}

float LoRaCommunicator::getLastSNR() const noexcept {
    return radio_m.getSNR();
}

int16_t LoRaCommunicator::attemptReceive(size_t timeoutInms) {
    const uint32_t startTime{ millis() };
    uint32_t timeElapsed{ 0 };

    int16_t receiveStatus{ radio_m.receive(receivedDataBuffer_m.data(), receivedDataBuffer_m.size()) };

    while ((timeElapsed < timeoutInms) && (receiveStatus == RADIOLIB_ERR_RX_TIMEOUT)) {
        receiveStatus = radio_m.receive(receivedDataBuffer_m.data(), receivedDataBuffer_m.size());

        delay(1); // Watchdog

        timeElapsed = (millis() - startTime);
    }

    return receiveStatus;
}

bool LoRaCommunicator::isRecuperableError(int16_t errorCode) noexcept {
    return (errorCode == RADIOLIB_ERR_RX_TIMEOUT) || (errorCode == RADIOLIB_ERR_CRC_MISMATCH);
}
