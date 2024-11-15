#include <Arduino.h>
#include <unity.h>
#include <heltec_unofficial.h>
#include "AnalogInput.hpp"
#include "AnalogOutput.hpp"
#include "DigitalInput.hpp"
#include "DigitalOutput.hpp"

static constexpr uint8_t DIGITAL_INPUT_OUTPUT_PIN{ 4 };
static constexpr uint8_t ANALOG_INPUT_OUTPUT_PIN{ 1 };

static constexpr int EXPECTED_ANALOG_READ{ 783 };

void test_digital_input_output();
void test_analog_input_output();

void setup() {
    heltec_setup();
    UNITY_BEGIN();
    RUN_TEST(test_digital_input_output);
    UNITY_END();
}

void loop() {

}

void test_digital_input_output() {
    DigitalInput input{ DIGITAL_INPUT_OUTPUT_PIN };

    input.begin();

    DigitalOutput output{ DIGITAL_INPUT_OUTPUT_PIN };

    output.begin();

    output.write(false);

    TEST_ASSERT_EQUAL(false, input.read());

    output.write(true);

    TEST_ASSERT_EQUAL(true, input.read());

    output.write(false);

    TEST_ASSERT_EQUAL(false, input.read());
}

void test_analog_input_output() {
    AnalogInput input{ ANALOG_INPUT_OUTPUT_PIN };

    input.begin();

    AnalogOutput output{ ANALOG_INPUT_OUTPUT_PIN };

    output.begin();

    output.write(0);

    input.begin();

    TEST_ASSERT_EQUAL(0, input.read());

    output.write(EXPECTED_ANALOG_READ);

    TEST_ASSERT_EQUAL(EXPECTED_ANALOG_READ, input.read());

    output.write(0);

    TEST_ASSERT_EQUAL(0, input.read());
}
