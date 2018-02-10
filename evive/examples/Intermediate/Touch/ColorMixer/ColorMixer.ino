/*
   Colour Mixer
   This code demonstrates three fruits (Apple , Grape and Blueberry) connected to different touch inputs
   this code checks all combination of colors if any fruit is touched and add colours and display total colour in Screen

   Made by Nihar Shah
   On 31 Dec, 2017
*/
#define red 1
#define green 2
#define blue 3
#include <evive.h>
void setup() {
  tft_init(INITR_GREENTAB);              // initialize a ST7735S chip, black tab
  tft.fillScreen(ST7735_BLACK);         // clear screen
  touchPins.begin(0x5A);                      // start touch
}
bool r, g, b;
void loop() {
  r = isTouched(red);                     // check red is touched or not?
  g = isTouched(green);                   // check green is touched or not?
  b = isTouched(blue);                   // check blue is touched or not?
  //enter all the combinations 
  if (r & g & b)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_WHITE);
  else if (r & g)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_YELLOW);
  else if (r & b)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_MAGENTA);
  else if (g & b)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_CYAN);
  else if (r)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_RED);
  else if (g)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_GREEN);
  else if (b)
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_BLUE);
  else
    tft.fillRoundRect(20, 30, 120, 68, 10, ST7735_BLACK);
}
