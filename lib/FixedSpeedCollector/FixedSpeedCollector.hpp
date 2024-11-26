#pragma once
#ifndef FIXED_SPEED_HEADER
#define FIXED_SPEED_HEADER

#include "Collector.hpp"
#include "AnalogInput.hpp"

/// @brief Collector del fixed speed
class FixedSpeedCollector : public Collector<int32_t> {
public:

    /// @brief Constructor base
    /// @param fixedSpeedPin Número GPIO del pin a usar
    FixedSpeedCollector(uint8_t fixedSpeedPin);

    /// @brief Inicializa el pin a usar
    void beginPins() override;

    /// @brief Obtiene el estado actual del pin
    /// @return El estado actual del pin
    [[nodiscard]]
    int32_t getData() override;

private:
    static constexpr uint8_t MIN_ANALOG_VALUE{ 0 };
    static constexpr uint16_t MAX_ANALOG_VALUE{ 4095 };

    static constexpr uint8_t MIN_FIXED_VALUE{ 0 };
    static constexpr uint8_t MAX_FIXED_VALUE{ 100 };

    AnalogInput fixedSpeed_m;
    
};

#endif // !FIXED_SPEED_HEADER
