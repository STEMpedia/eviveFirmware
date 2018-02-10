/*
   evive Slide Switch

   This code demonstrates how to use slide switch in Aruino IDE and display state on TFT Screen.

   Created by Pankaj Kumar Verma
   On 13 Mar, 2017
*/


#include <evive.h>
int buttonState1 = 0; // variable for reading the pushbutton pin 1 status
int buttonState2 = 0; // variable for reading the pushbutton pin 2 status

void setup() {
  pinMode(SLIDESW1_D1, INPUT);				// initialize the first slideswitch pins as an input:
  pinMode(SLIDESW1_D2, INPUT);
  pinMode(LED28, OUTPUT);
  pinMode(LED29, OUTPUT);
}

void loop() {
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(SLIDESW1_D1);
  buttonState2 = digitalRead(SLIDESW1_D2);
  // check if the slideswitch is in state 1.
  // if it is, the buttonState1 is HIGH:
  if (buttonState1 == HIGH) {
    digitalWrite(LED28, HIGH);
    digitalWrite(LED29, LOW);
  }
  // check if the slideswitch is in state 2.
  // if it is, the buttonState2 is HIGH:
  else if (buttonState2 == HIGH) {
    digitalWrite(LED29, HIGH);
    digitalWrite(LED28, LOW);
  }
  else {       // if it is in middle state.
    digitalWrite(LED28, LOW);
    digitalWrite(LED29, LOW);
  }
  delay(100);
}
