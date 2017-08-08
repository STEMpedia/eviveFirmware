#ifndef SCREEN_H
#define SCREEN_H

#include "evive.h"

#ifndef ROW_HEIGHT
#define ROW_HEIGHT       10
#endif
#ifndef CHAR_HEIGHT
#define CHAR_HEIGHT     8
#endif
#ifndef TWO_CHAR_HEIGHT
#define TWO_CHAR_HEIGHT     16
#endif
#ifndef CHAR_WIDTH
#define CHAR_WIDTH      6
#endif
#ifndef LEFT_MARGIN
#define LEFT_MARGIN     2
#endif
#ifndef RIGHT_MARGIN
#define RIGHT_MARGIN    2
#endif
#ifndef TOP_MARGIN
#define TOP_MARGIN      14
#endif
#ifndef BOTTOM_MARGIN
#define BOTTOM_MARGIN     2
#endif
#ifndef TFT_HEIGHT
#define TFT_HEIGHT      128
#endif
#ifndef TFT_WIDTH
#define TFT_WIDTH       160
#endif
#ifndef TFT_WIDTH_BY_2
#define TFT_WIDTH_BY_2  80
#endif

//No varible can be assigned any value here as variables are actually declared in motor.cpp
//Using extern, variables can be used in other libraries without declaration.
extern volatile bool DAC_ON_OFF;
extern volatile bool OSCILLOSCOPE_ON_OFF;
extern TFT_ST7735 tft;

void tft_init();
void tft_update();

char* itostr2(const uint8_t& x);
char* itostr31(const int& xx);
char* itostr3(const int& xx);
char* itostr3left(const int& xx);
char* itostr4(const int& xx);
char* itostr4sign(const int& x);

char* ftostr3(const float& x);
char* ftostr4sign(const float& x);
char* ftostr31ns(const float& x); // float to string without sign character
char* ftostr31(const float& x);
char* ftostr32(const float& x);
char* ftostr43(const float& x);
char* ftostr12ns(const float& x);
char* ftostr32sp(const float& x); // remove zero-padding from ftostr32
char* ftostr5(const float& x);
char* ftostr51(const float& x);
char* ftostr52(const float& x);

#endif
