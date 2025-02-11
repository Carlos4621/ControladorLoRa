#pragma once
#ifndef BTS7960_HEADER
#define BTS7960_HEADER

#include <cstdint>
#include "AnalogOutput.hpp"
#include <stdexcept>

/// @brief Pines para un objeto BTS7960
struct BTS7960Pins {
    uint8_t pinRightPWM;
    uint8_t pinLeftPWM;
};

/// @brief Representación de un driver de motor BTS7960
class BTS7960 {
public:

    /// @brief Constructor base
    /// @param pinRightPWM Pin GPIO de la entrada RPWM del driver
    /// @param pinLeftPWM Pin GPIO de la entrada LPWM del driver
    BTS7960(uint8_t pinRightPWM, uint8_t pinLeftPWM);

    /// @brief Constructor con struct
    /// @param pins Struct con los pines a usar
    explicit BTS7960(const BTS7960Pins& pins);

    /// @brief Inicializa los pines a usar
    void beginPins();

    /// @brief Escribe en la entrada RPWM del driver
    /// @param percentage Porcentaje de la potencia del giro. Si percentage > 100 lanza std::out_of_range
    void setHoraryRotation(uint8_t percentage);

    /// @brief Escribe en la entrada LPWM del driver
    /// @param percentage Porcentaje de la potencia del giro. Si percentage > 100 lanza std::out_of_range
    void setAntihoraryRotation(uint8_t percentage);

    /// @brief Escribe en la estrada RPWM o LPWM dependiendo del signo del porcentaje. Si percentage > 0 entonces RPWM, si percentage < 0 entonces LPWM
    /// @param percentage Porcentaje relativo del giro. Si percentage < -100 || percentage > 100 lanza std::out_of_range
    void setRelativeSpeed(int percentage);

    /// @brief Establece en 0 las dos entradas RPWM y LPWM del driver
    void stopMotor();

private:
    enum class Direction : uint8_t { Horary = 0, Antihorary };

    static constexpr uint8_t MAX_ANALOG_OUTPUT{ 255 };

    static constexpr uint8_t MAX_PERCENTAGE{ 100 };
    static constexpr int8_t MIN_PERCENTAGE{ -100 };

    AnalogOutput pinRightPWM_m;
    AnalogOutput pinLeftPWM_m;

    [[nodiscard]]
    static uint8_t getConvertedAnalogOutput(uint8_t percentage) noexcept;

    void setRotation(uint8_t percentage, const Direction& direction);

    void verifyPercentageRange(int8_t percentage);
};

#endif // !BTS7960_HEADER