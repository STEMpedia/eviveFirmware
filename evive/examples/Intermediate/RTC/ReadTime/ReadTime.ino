/* Read RTC
 *  this code shows how to collect data frm RTC on Evive
 *  
 *  functions available on <http://learn.evive.cc/index.html?t=RTC>
 *  
 *  modified Nihar Shah 9 Sept 2017
 *  
 */
#include <evive.h>
#include "RTC.h"
void setup() {
 Serial.begin(9600);
 Wire.begin();
 // put your setup code here, to run once:
}

void loop() {
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