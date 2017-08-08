/*
 * evive.cpp
 * Created on: April 16, 2016
 * Author: dhrups
 * Last update: May 10, 2016
 * Version: 1.0
 */
#include "evive.h"

#ifdef EVIVE_LIBRARY_MODE
void setup(){
	Serial.begin(BAUDRATE);
	Serial.println("In the setup loop now");
	tft_init();
	Serial.println("setup ends");
}

void loop(){
	tft_update();
	action();
}
#endif
