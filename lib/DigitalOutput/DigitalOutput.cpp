#include "DigitalOutput.hpp"

DigitalOutput::DigitalOutput(uint8_t pin)
    : Pin{ pin, OUTPUT } {
}

void DigitalOutput::write(bool value) {
    digitalWrite(this->getPin(), value);
}
