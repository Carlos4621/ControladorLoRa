#include "AnalogOutput.hpp"

AnalogOutput::AnalogOutput(uint8_t pin)
    : Pin{ pin, OUTPUT } {
}

void AnalogOutput::write(uint16_t value) {
    analogWrite(this->getPin(), value);
}
