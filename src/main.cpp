#include <Arduino.h>
#include "Display.hpp"
#include <heltec_unofficial.h>
#include "BTS7960.hpp"

Display dis{ display };

GUIData data;

void setup() {
	heltec_setup();

	Serial.begin(9600);

	data.leftMotorValue = -100;
	data.rightMotorValue = -100;
	data.selectedMode = 3;
	data.fixedValue = -100;
	data.RSSI = -120;
	data.SNR = -5;
}
                    
void loop() {
	heltec_loop();

	dis.displayConnectingWaiting();

	delay(1000);

	dis.displayConnectionSuccesfull();

	delay(1000);

	dis.showGUI(data);

	delay(1000);
}
