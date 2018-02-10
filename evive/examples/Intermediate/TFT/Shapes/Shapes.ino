/*
  Using TFT Display to draw shapes

  This code shows how to use TFT display attached on Evive.
  available on <http://www.evive.cc>
  modified 9 Sep 2017
  by Nihar Shah
  functions are on <http://learn.evive.cc/index.html?t=TFT>
  This example code is in the public domain.
*/

#include <evive.h>
void setup() {
  tft_init(INITR_BLACKTAB); // this is used to initialize TFT display
  tft.fillScreen(ST7735_BLACK); // this filles display with black colour
}
void loop() {
  // Drawing Lines
  tft.drawLine(10, 10, 150, 118, ST7735_RED);
  tft.drawLine(10, 118, 150, 10, ST7735_RED);
  delay(1000);
  tft.fillScreen(ST7735_BLACK);

  // Drawing Fast Verticle Lines
  for (int i = 10; i < 151; i = i + 10)
  {
    tft.drawFastVLine(i, 1, 128, ST7735_RED);
  }

  // Drawing Fast Horizontal Lines
  for (int i = 10; i < 121; i = i + 10)
  {
    tft.drawFastHLine(1, i, 160, ST7735_RED);
  }
  delay(1000);
  tft.fillScreen(ST7735_BLACK);

  // Draw Rectangle
  tft.drawRect(10, 10, 140, 108, ST7735_WHITE);
  tft.fillRect(20, 20, 120, 88, ST7735_RED);
  delay(1000);
  tft.fillScreen(ST7735_BLACK);

  // Draw Round Rectangle
  tft.drawRoundRect(10, 10, 140, 108, 10, ST7735_WHITE);
  tft.fillRoundRect(20, 20, 120, 88, 4, ST7735_RED);
  delay(1000);
  tft.fillScreen(ST7735_BLACK);

  // Draw Circle
  tft.drawCircle(80, 64, 60, ST7735_WHITE);
  tft.fillCircle(80, 64, 50, ST7735_RED);
  delay(1000);
  tft.fillScreen(ST7735_BLACK);

  // Draw Triangle
  tft.drawTriangle(80, 10, 10, 118, 150, 118, ST7735_WHITE);
  tft.fillTriangle(80, 30, 30, 108, 130, 108, ST7735_RED);
  delay(1000);
  tft.fillScreen(ST7735_BLACK);
}
