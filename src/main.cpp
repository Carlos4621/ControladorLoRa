#include <Arduino.h>
#include "GUI.hpp"
#include <heltec_unofficial.h>
#include "BTS7960.hpp"
#include "LoRaCommunicator.hpp"

GUI dis{ display };

GUIData data;

LoRaCommunicator<16> lo{ radio };

std::array<uint8_t, 16> testPackage{ 4, 6, 2, 1 };

void setup() {
	heltec_setup();

	Serial.begin(9600);

	data.leftMotorValue = -100;
	data.rightMotorValue = -100;
	data.selectedMode = 3;
	data.fixedValue = -100;
	data.RSSI = -120;
	data.SNR = -5;

	LoRaParameters para;

	para.frecuencyInMHz = 434;
	para.bandwidhtInKHz = 125;
	para.spreadingFactor = 9;
	para.codingRate = 7;
	para.syncWord = RADIOLIB_SX126X_SYNC_WORD_PRIVATE;
	para.outputPowerInDBm = 10;
	para.preambleLenght = 8;

	lo.initializeRadio(para);
}

void loop() {
	heltec_loop();

	try {
		testPackage = lo.receivePackage(100);

		for (size_t i = 0; i < 4; ++i) {
			Serial.println(testPackage[i]);
		}
	}
	catch(const std::exception& e)
	{
		Serial.println(e.what());
	}
}
