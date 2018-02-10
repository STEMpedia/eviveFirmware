/* Analog Data Read
 * Read analog data of Potentiometer 1 (A9) on evive and publish it on Serial communication.
 * Serial communication baud rate is 250000
 * You can open Serial monitor in Arduino IDE using button in Tools menu
 * You can also try using Serial Plotter to plot data.
 * 
 * Written by by Nihar Shah, Agilo Research
 * on 29 December 2017
 * 
 * Explore more at https://evive.cc/tutorial/arduino
 */

#include <evive.h>          //include evive library

void setup() {
Serial.begin(250000);       //Set the Serial Port 1 (USB) with BAUD rate of 250000
pinMode(POT1,INPUT);        //Set pin as input mode (POT1 = A9)
}

int potData;                //variable to store analog reading of potentiometer 1

void loop() {
//read 
potData = analogRead(POT1); //reads analog data of potentiometer on Pin 1
Serial.println(potData);    //prints new data and changes to next line
delay(100);                 //delay of 100 milli seconds in each loop
}
