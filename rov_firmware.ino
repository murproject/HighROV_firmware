
/*
 Name:		rov_firmware.ino
 Created:	15.01.2018 14:16:59
 Author:	zinjk
*/


#include <Arduino.h>
#include <Wire.h>
#include "HighROV.h"

void setup() {  
    
    //delay(500);
    Wire.begin();
    //Wire.setClock(100000);
    delay(100);
    Serial.begin(115200);
    HighROV::init();
}

void loop() {
    HighROV::run();
}
