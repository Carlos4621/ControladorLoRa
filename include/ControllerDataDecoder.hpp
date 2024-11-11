#pragma once
#ifndef CONTROLLER_DATA_DECODER_HEADER
#define CONTROLLER_DATA_DECODER_HEADER

#include <pb_decode.h>
#include <vector>
#include "ControllerData.pb.h"
#include <stdexcept>
#include <Arduino.h>

class ControllerDataDecoder {
public:
    
    [[nodiscard]]
    ControllerData decode(const std::vector<uint8_t>& encodedData);
};

#endif // !CONTROLLER_DATA_DECODER_HEADER