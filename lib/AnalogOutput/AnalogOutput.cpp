#include "AnalogOutput.hpp"

AnalogOutput::AnalogOutput(uint8_t pin)
    : Pin{ pin, OUTPUT } {
}

void AnalogOutput::write(int value) {
    analogWrite(this->getPin(), value);
}
