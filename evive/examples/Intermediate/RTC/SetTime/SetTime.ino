/*
  evive RTC Write Operation

  This code demonstrate how to write on PCF8563 (a Real Time Clock)

  Code modified by
  Nihar Shah
*/
#include <evive.h>
#include "RTC.h"
void setup() {
  second = 00;
  minute = 18;
  hour = 17;
  dayOfWeek = 6;
  dayOfMonth = 29;
  month = 12;
  year = 17; // enter only year
  setPCF8563();
  //now use read function to read time
}

void loop() {
  // put your main code here, to run repeatedly:

}