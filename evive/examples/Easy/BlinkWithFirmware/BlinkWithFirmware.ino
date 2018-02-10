/* Blink two LEDs on Pin 28 and 29 with evive Firmware
 * Similar to basic example of Blinking an LED on Pin 13 in Arduino, here we 
 * are blinking bi-color LED on Pin 28 and 29. The difference of using evive Firmware
 * is that when we Exit from menu, then only the blink code will run.
 * 
 * To get back to evive menu, you need to reset evive.
 * 
 * Written by by Nihar Shah, Agilo Research
 * on 29 December 2017
 * 
 * Explore more at https://evive.cc/tutorial/arduino
 */
 
#include <evive.h>            // Include evive library

void setup() {
  eviveFirmware();            // Enables the evive menu. It will run till you don't exit.
  pinMode(LED28, OUTPUT);     // Set pin as output mode (LED28 = Pin 28)
  pinMode(LED29, OUTPUT);     // Set pin as output mode (LED29 = Pin 29)
}

//After you exit from evive menu, then only the loop code will run continuously
void loop() {
  drawStatusBar();            // shows variable voltage value (VVR) and battery level
  digitalWrite(LED28, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED29, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                // wait for a second
  digitalWrite(LED29, HIGH);  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED28, LOW);   // turn the LED off by making the voltage LOW
  delay(1000);                // wait for a second
}
