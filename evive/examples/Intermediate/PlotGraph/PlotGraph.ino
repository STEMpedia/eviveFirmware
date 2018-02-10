/*
	This example shows how to plot any variable on evive TFT display.
 
	Made by Dhrupal Shah, Agilo Research
	Created on: 20180208
*/

#include<evive.h>                         //include evive library

TftMonitor tftMonitor;                     // Initialize a class object

void setup(){
  tft_init(INITR_BLACKTAB);               //Use either INITR_BLACKTAB or INITR_GREENTAB. Initialize TFT screen in library screen.cpp
  tftMonitor.begin();                     // Begins tftMonitor
  pinMode(A9,INPUT);                      // Set pin as input mode (POT1 = A9) 
}

// the loop function runs continuously when you select the user defined function
void loop(){
  tftMonitor.print("Pot 1 value: ");
  tftMonitor.println(analogRead(A9));     // Pot1 Value is printed on TFT Monitor
  delay(50);
}
