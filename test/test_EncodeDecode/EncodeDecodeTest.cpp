#include <Arduino.h>
#include <unity.h>
#include <heltec_unofficial.h>
#include "ControllerDataDecoder.hpp"
#include "ControllerDataEncoder.hpp"
#include "ControllerData.pb.h"

static constexpr int32_t EXPECTED_LEFT_X_AXIS{ 9 };
static constexpr int32_t EXPECTED_LEFT_Y_AXIS{ 45 };
static constexpr bool EXPECTED_LEFT_BUTTON{ false };

static constexpr int32_t EXPECTED_RIGHT_X_AXIS{ -55 };
static constexpr int32_t EXPECTED_RIGHT_Y_AXIS{ 11 };
static constexpr bool EXPECTED_RIGHT_BUTTON{ true };

static constexpr bool EXPECTED_BUTTON_A{ false };
static constexpr bool EXPECTED_BUTTON_B{ true };
static constexpr bool EXPECTED_BUTTON_X{ true };
static constexpr bool EXPECTED_BUTTON_Y{ false };

static constexpr Modes EXPECTED_MODE{ Modes_FIXED_SPEED };

static constexpr int32_t EXPECTED_FIXED_SPEED{ 46 };

void fillWithData(ControllerData &toFill);

void test_encode_decode();

void test_has_not_value_returns_zero();

void setup() {
    heltec_setup();
    UNITY_BEGIN();
    RUN_TEST(test_encode_decode);
    RUN_TEST(test_has_not_value_returns_zero);
    UNITY_END();
}

void loop() {
}

void fillWithData(ControllerData &toFill) {

    toFill.has_rightJoystick = true;
    toFill.rightJoystick.axisX = EXPECTED_RIGHT_X_AXIS;
    toFill.rightJoystick.axisY = EXPECTED_RIGHT_Y_AXIS;
    toFill.rightJoystick.button = EXPECTED_RIGHT_BUTTON;

    toFill.has_leftJoystick = true;
    toFill.leftJoystick.axisX = EXPECTED_LEFT_X_AXIS;
    toFill.leftJoystick.axisY = EXPECTED_LEFT_Y_AXIS;
    toFill.leftJoystick.button = EXPECTED_LEFT_BUTTON;

    toFill.fixedSpeed = EXPECTED_FIXED_SPEED;

    toFill.selectedMode = EXPECTED_MODE;

    toFill.has_buttons = true;
    toFill.buttons.buttonA = EXPECTED_BUTTON_A;
    toFill.buttons.buttonB = EXPECTED_BUTTON_B;
    toFill.buttons.buttonX = EXPECTED_BUTTON_X;
    toFill.buttons.buttonY = EXPECTED_BUTTON_Y;
}

void test_encode_decode() {
    ControllerData data = ControllerData_init_zero;

    fillWithData(data);

    ControllerDataEncoder encoder;

    const auto encodedData{ encoder.encode(data) };

    ControllerDataDecoder decoder;

    const auto decodedData{ decoder.decode(encodedData) };

    TEST_ASSERT_EQUAL(EXPECTED_RIGHT_X_AXIS, decodedData.rightJoystick.axisX);
    TEST_ASSERT_EQUAL(EXPECTED_RIGHT_Y_AXIS, decodedData.rightJoystick.axisY);
    TEST_ASSERT_EQUAL(EXPECTED_RIGHT_BUTTON, decodedData.rightJoystick.button);

    TEST_ASSERT_EQUAL(EXPECTED_LEFT_X_AXIS, decodedData.leftJoystick.axisX);
    TEST_ASSERT_EQUAL(EXPECTED_LEFT_Y_AXIS, decodedData.leftJoystick.axisY);
    TEST_ASSERT_EQUAL(EXPECTED_LEFT_BUTTON, decodedData.leftJoystick.button);

    TEST_ASSERT_EQUAL(EXPECTED_BUTTON_A, decodedData.buttons.buttonA);
    TEST_ASSERT_EQUAL(EXPECTED_BUTTON_B, decodedData.buttons.buttonB);
    TEST_ASSERT_EQUAL(EXPECTED_BUTTON_X, decodedData.buttons.buttonX);
    TEST_ASSERT_EQUAL(EXPECTED_BUTTON_Y, decodedData.buttons.buttonY);

    TEST_ASSERT_EQUAL(EXPECTED_FIXED_SPEED, decodedData.fixedSpeed);

    TEST_ASSERT_EQUAL(EXPECTED_MODE, decodedData.selectedMode);
}

void test_has_not_value_returns_zero() {
    ControllerData data = ControllerData_init_zero;

    fillWithData(data);

    data.has_rightJoystick = false;
    data.has_leftJoystick = false;
    data.has_buttons = false;

    ControllerDataEncoder encoder;

    const auto encodedData{ encoder.encode(data) };

    ControllerDataDecoder decoder;

    const auto decodedData{ decoder.decode(encodedData) };

    TEST_ASSERT_EQUAL(0, decodedData.rightJoystick.axisX);
    TEST_ASSERT_EQUAL(0, decodedData.rightJoystick.axisY);
    TEST_ASSERT_EQUAL(0, decodedData.rightJoystick.button);

    TEST_ASSERT_EQUAL(0, decodedData.leftJoystick.axisX);
    TEST_ASSERT_EQUAL(0, decodedData.leftJoystick.axisY);
    TEST_ASSERT_EQUAL(0, decodedData.leftJoystick.button);

    TEST_ASSERT_EQUAL(false, decodedData.buttons.buttonA);
    TEST_ASSERT_EQUAL(false, decodedData.buttons.buttonB);
    TEST_ASSERT_EQUAL(false, decodedData.buttons.buttonX);
    TEST_ASSERT_EQUAL(false, decodedData.buttons.buttonY);
}
