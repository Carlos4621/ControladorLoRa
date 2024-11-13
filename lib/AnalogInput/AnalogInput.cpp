#include "AnalogInput.hpp"

AnalogInput::AnalogInput(uint8_t pin) 
    : Pin{ pin, INPUT } {
}

uint16_t AnalogInput::read() const noexcept {
    return analogRead(this->getPin());
}
