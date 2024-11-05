#include "Pin.hpp"

Pin::Pin(uint8_t pin, bool pinMode) 
    : pin_m{ pin }
    , pinMode_m{ pinMode } {
}

void Pin::begin() {
    pinMode(pin_m, pinMode_m);
}

uint8_t Pin::getPin() const noexcept {
    return pin_m;
}
