/*
  Using TFT Display

  This code shows how to use TFT display attached on Evive.
  available on <http://www.evive.cc>
  modified 9 Sep 2017
  by Nihar Shah

  This example code is in the public domain.
*/

#include <evive.h>
void setup() {
  tft_init(INITR_BLACKTAB); // this is used to initialize TFT display
  tft.fillScreen(ST7735_BLACK); // this filles display with black colour
  tft.setCursor(0,10); // this sets corser to write on (0,10) location
  tft.println("Hello World!"); //print function
  tft.println("");
  tft.print("I am evive! ");
  
  // put your setup code here, to run once:

}
void loop() {
  // put your main code here, to run repeatedly:

}
