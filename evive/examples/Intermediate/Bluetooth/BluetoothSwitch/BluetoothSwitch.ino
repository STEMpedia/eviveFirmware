/*
evive Bluetooth

An example of using the evive to receive data from any Bluetooth enabled device. In
this case, the evive turns on an LED when it receives the character
'H', and turns off the LED when it receives the character 'L'.

The data can be sent from any Bluetooth enabled device. For mobile device find Bluetooth Terminal
in respective App Store.

modified 12 Sep 2017
by Nihar Shah

This example code is in the public domain.
*/
#include<evive.h>
int incomingByte;      // a variable to read incoming serial data into

void setup() {
  // initialize serial communication:
  Serial3.begin(9600);
  // initialize the LED pin as an output:
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  // see if there's incoming serial data:
  if (Serial3.available() > 0) {
    // read the oldest byte in the serial buffer:
    incomingByte = Serial3.read();
    // if it's a capital H (ASCII 72), turn on the LED:
    if (incomingByte == 'H') {
      digitalWrite(LED_BUILTIN, HIGH);
    }
    // if it's an L (ASCII 76) turn off the LED:
    if (incomingByte == 'L') {
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
}

