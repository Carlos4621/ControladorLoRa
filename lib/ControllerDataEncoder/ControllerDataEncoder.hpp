#pragma once
#ifndef CONTROLLER_DATA_ENCODER_HEADER
#define CONTROLLER_DATA_ENCODER_HEADER

#include <pb_encode.h>
#include <vector>
#include "ControllerData.pb.h"
#include <stdexcept>

class ControllerDataEncoder {
public:

    [[nodiscard]]
    std::vector<uint8_t> encode(const ControllerData& data);

private:

    std::vector<uint8_t> encodeBuffer_m{};
};

#endif // !CONTROLLER_DATA_ENCODER_HEADER
