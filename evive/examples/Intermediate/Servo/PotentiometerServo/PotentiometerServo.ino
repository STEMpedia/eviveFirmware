/*
   evive servo example
   this example demonstrates how to use servo motor for angle on evive
   input is given by POTx where x can be 1 or 2
   x is where the servo is attached
   by Nihar Shah
   modified 13 Sep 2017
*/
#include<evive.h>
Servo myservo;  // create servo object to control a servo
int angle=0;
void setup() {
  myservo.attach(SERVO1_ATTACH);  // attaches the servo on pin S1 to the servo object
}

void loop() {
  angle = analogRead(POT1);            // reads the value of the potentiometer (value between 0 and 1023)
  angle = map(angle, 0, 1023, 0, 180);     // scale it to use it with the servo (value between 0 and 180)
  myservo.write(angle);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
