#ifndef CONTROLLER_DATA_ENCODER_HEADER
#define CONTROLLER_DATA_ENCODER_HEADER

#include <pb_encode.h>
#include <vector>
#include "ControllerData.pb.h"
#include <stdexcept>

/// @brief Codificador de ControllerData
class ControllerDataEncoder {
public:

    /// @brief Codifica un ControllerData en una serie de bytes
    /// @param data Data a codificar
    /// @return Data codificada
    [[nodiscard]]
    std::vector<uint8_t> encode(const ControllerData& data);

private:

    std::vector<uint8_t> encodeBuffer_m{};
};

#endif // !CONTROLLER_DATA_ENCODER_HEADER
