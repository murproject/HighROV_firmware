#define SERIAL_RX_BUFFER_SIZE 256
/*
 Name:		rov_firmware.ino
 Created:	15.01.2018 14:16:59
 Author:	zinjk
*/


#include <Arduino.h>
#include "Rov.h"

rov::Rov robot;

void setup() {
	
	Serial.begin(115200);
	robot.init();
}

void loop() {
	robot.run();
}


