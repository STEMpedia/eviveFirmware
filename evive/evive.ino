 /*
 * This firmware is developed for evive [http://evive.cc].
 * This is licensed under Creative Commons 4.0 BY-SA.
 * Written by Dhrupal R Shah for Agilo Technologies.
 * Last update: 2017, Jan 31
 *
 * NOTE: Works with Arduino IDE 1.6.6 or later [https://www.arduino.cc/en/Main/Software]
 */

//evive.h includes all the libraries for evive functionalities.
#include "evive.h"

void setup(){
  Serial.begin(BAUDRATE);
  lcd_init();

}

void loop(){
  lcd_update();
  action();
}
