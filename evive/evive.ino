 /*
  * Version 1.0.2
  * This firmware is developed for evive [http://evive.cc].
  * This is licensed under GNU GPL V3 [http://www.gnu.org/licenses/gpl.txt].
  * Written by Dhrupal R Shah for evive platform, Agilo Technologies.
  * Last update: 2017, June 4 ,by Harsh Chittora
  * Contact: support@evive.cc
  * Copyright (c) 2017 Agilo Technologies.  All rights reserved.
  *
  * Getting started with evive: http://learn.evive.cc/
  *
  * NOTE: Works with Arduino IDE 1.6.6 or later [https://www.arduino.cc/en/Main/Software]
 */

#include "evive.h"

void setup(){
  Serial.begin(BAUDRATE);			//Default BAUD Rate: 250000, edit the macro in configuration.h
  lcd_init();									//Initialize TFT screen in library screen.cpp
}

void loop(){
  lcd_update();								//Updates the TFT on any action in menu
  action();										//Runs the function in the array actionFuncList
}
