/*
   Serial LED
   In this example you can control LED marked as M1 of Motor using Serial Communication

   Open the serial monitor in Arduino IDE and s
   By Nihar Shah
   On 29 December 2017

*/
#include <evive.h>
void setup() {
  Serial.begin (115200);    // start Serial Communication at 115200
  pinMode(LED28, OUTPUT);
}
char incomingData;
void loop() {
  while (Serial.available())
  {
    incomingData = Serial.read();
  }
  if (incomingData == 'H')
    digitalWrite(LED28, HIGH);
  if (incomingData == 'L')
    digitalWrite(LED28, LOW);

}
