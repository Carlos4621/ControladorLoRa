#ifndef MODE_COLLECTOR_HEADER
#define MODE_COLLECTOR_HEADER

#include <pb.h>
#include "Collector.hpp"
#include "DigitalInput.hpp"
#include "Modes.pb.h"

/// @brief Struct con los pines del modo de operación
struct ModeSelectionPins {
    uint8_t independentPin;
    uint8_t fixedSpeedPin;
    uint8_t autonomousPin;
};

/// @brief Clase encargada de recopilar los datos del modo de operación
class ModeCollector : public Collector<Modes> {
public:

    /// @brief Constructor base
    /// @param independentModePin Pin que indica el modo independiente 
    /// @param fixedSpeedPin Pin que indica el modo fixed
    /// @param autonomousModePin Pin que indica el modo autónomo
    ModeCollector(uint8_t independentModePin, uint8_t fixedSpeedPin, uint8_t autonomousModePin);

    /// @brief Constructor con struct
    /// @param pins Pines a usar
    explicit ModeCollector(const ModeSelectionPins& pins);

    /// @brief Inicializa los pines a usar
    void beginPins() override;

    /// @brief Obtiene el estado actual del modo
    /// @return El estado actual del modo según la prioridad: fijo > autónomo > independiente
    [[nodiscard]]
    Modes getData() override;

private:

    DigitalInput independentMode_m;
    DigitalInput fixedMode_m;
    DigitalInput autonomousMode_m;

};

#endif // !MODE_COLLECTOR_HEADER