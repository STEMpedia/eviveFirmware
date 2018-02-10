/*
 Fading

 This example shows how to fade an on-board LED 
 using the analogWrite() function.

 The analogWrite() function uses PWM, so if
 you want to change the pin you're using, be
 sure to use another PWM capable pin. On Evive
 the PWM pins are digital pin 2 to 13.

 This example code is in the public domain.

 Modified 9 Sept 2017
 by Nihar Shah
 */
 
#include <evive.h>

#define led 13                   // the PWM pin the LED is attached to
int brightness = 0;              // how bright the LED is
int fadeAmount = 5;              // how many points to fade the LED by

// the setup routine runs once when you press reset:
void setup() {
  pinMode(led, OUTPUT);          // declare LED to be an output:
}

// the loop routine runs over and over again forever:
void loop() {
  analogWrite(led, brightness);   // set the brightness of pin 9:

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade:
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }

  delay(50);                      // wait for 50 milliseconds to see the dimming effect

}
