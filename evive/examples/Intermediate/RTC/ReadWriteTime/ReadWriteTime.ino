/*
  evive RTC Read/Write Operation

  This code demonstrate how to read and write on PCF8563 (a Real Time Clock)

  Code modified by
  Nihar Shah
*/
#include <evive.h>
#include "RTC.h"

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  // change the following to set your initial time
  second = 00;
  minute = 18;
  hour = 17;
  dayOfWeek = 6;
  dayOfMonth = 29;
  month = 12;
  year = 17; // enter only year
  // comment out the next line and upload again to set and keep the time from resetting every reset
  //setPCF8563();
}

void loop()
{
  readPCF8563();
  Serial.print(days[dayOfWeek]);
  Serial.print(" ");
  Serial.print(dayOfMonth, DEC);
  Serial.print("/");
  Serial.print(month, DEC);
  Serial.print("/20");
  Serial.print(year, DEC);
  Serial.print(" - ");
  Serial.print(hour, DEC);
  Serial.print(":");
  if (minute < 10)
  {
    Serial.print("0");
  }
  Serial.print(minute, DEC);
  Serial.print(":");
  if (second < 10)
  {
    Serial.print("0");
  }
  Serial.println(second, DEC);
  delay(1000);
}
