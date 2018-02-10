/*
   evive Touch TFT Display

   This code detects if someone have touched banana attached to channel 1
   of Touch inputs and display the state on TFT Screen.

   Created by Pankaj Kumar Verma
   On 13 Mar, 2017
   Modified by Nihar Shah
   On 30 Dec, 2017
*/

#include <evive.h>
void setup() {
  // put your setup code here, to run once:
  tft_init(INITR_GREENTAB);              // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);
  touchPins.begin(0x5A);
}

void loop() {
  tft.drawRoundRect(20, 30, 120, 68, 10, ST7735_WHITE);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.setCursor(50, 40);
  tft.println("STATE");
  if (isTouched(1))
    tft.fillRoundRect(40, 65, 80, 25, 5, ST7735_GREEN);
  else
    tft.fillRoundRect(40, 65, 80, 25, 5, ST7735_RED);
}
