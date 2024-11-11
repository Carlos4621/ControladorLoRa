#include "ControllerDataDecoder.hpp"

ControllerData ControllerDataDecoder::decode(const std::vector<uint8_t>& encodedData) {
    ControllerData msg = ControllerData_init_zero;

    pb_istream_t decodeStream = pb_istream_from_buffer(encodedData.data(), encodedData.size());

    const bool decodeStatus{ pb_decode(&decodeStream, ControllerData_fields, &msg) };

    if(!decodeStatus) {
        throw std::runtime_error{ "Unable to decode the data" };
    }

    return msg;
}