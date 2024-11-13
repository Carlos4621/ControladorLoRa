#include "DigitalInput.hpp"

DigitalInput::DigitalInput(uint8_t pin) 
    : Pin{ pin, INPUT } {
}

bool DigitalInput::read() const noexcept {
    return digitalRead(this->getPin());
}
