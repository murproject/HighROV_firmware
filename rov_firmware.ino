
/*
 Name:		rov_firmware.ino
 Created:	15.01.2018 14:16:59
 Author:	zinjk
*/

#include <Arduino.h>
#include <Wire.h>
#include "HighROV.h"
#include <time.h>

bool debug_mode = 1; // change to 1 to enable waiting for serial connection for 2 secs


void setup() {
    Wire.begin();
    Wire.setTimeout(1000);
    Wire.setClock(10000);

    delay(100);

    SerialUSB.begin(115200);
    unsigned int t_on = millis();

    while(!SerialUSB && debug_mode){
      if(millis() >= t_on + 2000){  
        break;
      }else{
        analogWrite(LED_BUILTIN, sin(millis() * 0.05) * 127 + 127);
        delay(1);
      }
    }
    if(debug_mode){
      delay(200);
    }
    // Serial.begin(115200);
    // Serial1.begin(115200);

    HighROV::init();
}



void loop() {
    HighROV::run();
}
