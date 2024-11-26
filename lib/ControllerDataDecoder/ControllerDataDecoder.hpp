#pragma once
#ifndef CONTROLLER_DATA_DECODER_HEADER
#define CONTROLLER_DATA_DECODER_HEADER

#include <pb_decode.h>
#include <vector>
#include "ControllerData.pb.h"
#include <stdexcept>
#include <Arduino.h>
#include <span>

/// @brief Decodificador de ControllerData
class ControllerDataDecoder {
public:

    /// @brief Decodifica una serie de bytes en un ControllerData
    /// @param encodedData Data a decodificar
    /// @return Datos decodificados
    [[nodiscard]]
    static ControllerData decode(std::span<const uint8_t> encodedData);
};

#endif // !CONTROLLER_DATA_DECODER_HEADER