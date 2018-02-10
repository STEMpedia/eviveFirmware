/*
  High power circuit switching

  Turns on and off a high power circuit connected on relay
  when pressing pushbutton on evive.

  available on <http://www.evive.cc>
  modified 13 Sep 2017
  by Nihar Shah

  This example code is in the public domain.
*/

//#define button 38 // use for upper button
#define button 39 // use fot lower button
#define relay 2
int state = 0;         // variable for reading the pushbutton status
void setup() {
  // put your setup code here, to run once:
  // initialize the relay pin as an output:
  pinMode(relay, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(button, INPUT);
}

void loop() {
  // read the state of the pushbutton value:
  state = digitalRead(button);
  // check if the pushbutton is pressed.
  // if it is, the state is HIGH:
  if (state == HIGH) {
    // turn relay on:
    digitalWrite(relay, LOW);
  } else {
    // turn relay off:
    digitalWrite(relay, HIGH);
  }
}
