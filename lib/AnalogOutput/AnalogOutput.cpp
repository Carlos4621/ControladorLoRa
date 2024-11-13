#include "AnalogOutput.hpp"

AnalogOutput::AnalogOutput(uint8_t pin)
    : Pin{ pin, OUTPUT } {
}

void AnalogOutput::write(uint8_t value) {
    analogWrite(this->getPin(), value);
}
