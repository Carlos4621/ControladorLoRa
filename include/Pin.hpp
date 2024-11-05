#pragma once
#ifndef PIN_HEADER
#define PIN_HEADER

#include <Arduino.h>
#include <cstdint>

class Pin {
public:
    Pin(uint8_t pin, bool pinMode);

    void begin();

    [[nodiscard]]
    uint8_t getPin() const noexcept;

private:

    uint8_t pin_m;
    bool pinMode_m;
};


#endif // !PIN_HEADER