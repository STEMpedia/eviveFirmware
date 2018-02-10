/*
   evive Digital Read TFT Display

   This code demonstrates how to display digital state on TFT Screen.

   Created by Pankaj Kumar Verma
   On 13 Mar, 2017
*/
#include <evive.h>
boolean state = false;
void setup() {
  Serial.begin(9600);
  tft_init(INITR_GREENTAB); // initialize a ST7735S chip, green tab
  Serial.println("Initialized");
  tft.fillScreen(ST7735_BLACK);     // fill with black colour
  pinMode(TACTILESW1, INPUT);       // set as input
}

void loop() {
  tft.drawRoundRect(20, 30, 120, 68, 10, ST7735_WHITE);   // Draw rectangle 
  tft.setTextColor(ST7735_WHITE);                         // set white colour
  tft.setTextSize(2);                                     // size 2
  tft.setCursor(50, 40);                                  // set cursor at 50,40
  tft.println("STATE");                                   // print state 
  state = digitalRead(TACTILESW1);                        // check state
  if (state == true) {                                    // if true set green colour
    tft.fillRoundRect(40, 65, 80, 25, 5, ST7735_GREEN);
  }
  else {
    tft.fillRoundRect(40, 65, 80, 25, 5, ST7735_RED);     // if false set red rectangle
  }
}
