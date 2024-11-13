#include "ControllerDataEncoder.hpp"

std::vector<uint8_t> ControllerDataEncoder::encode(const ControllerData& toEncode) {
    encodeBuffer_m.resize(ControllerData_size);

    pb_ostream_t encodeStream_m = pb_ostream_from_buffer(encodeBuffer_m.data(), encodeBuffer_m.size());

    const bool status{ pb_encode(&encodeStream_m, ControllerData_fields, &toEncode) };

    if (!status) {
        throw std::runtime_error{ "Unable to encode the data" };
    }

    encodeBuffer_m.resize(encodeStream_m.bytes_written);

    return encodeBuffer_m;
}
