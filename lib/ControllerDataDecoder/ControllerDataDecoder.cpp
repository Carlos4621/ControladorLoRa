#include "ControllerDataDecoder.hpp"

ControllerData ControllerDataDecoder::decode(std::span<const uint8_t> encodedData) {
    ControllerData decodedData = ControllerData_init_zero;

    pb_istream_t decodeStream = pb_istream_from_buffer(encodedData.data(), encodedData.size());

    const bool decodeStatus{ pb_decode(&decodeStream, ControllerData_fields, &decodedData) };

    if(!decodeStatus) {
        throw std::runtime_error{ "Unable to decode the data" };
    }

    return decodedData;
}