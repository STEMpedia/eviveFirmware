/*
 * menuPress = True or False
 * menuMove = 1 (up), 2 (right), 3 (down) and 4 (left)
 * 
  */
#ifndef NAVKEY_H
#define NAVKEY_H

#include "evive.h"

//set range after min/max for all cases like battery powered, USB, VIN
#define NAVKEYMOVE_UP_LOW       190
#define NAVKEYMOVE_UP_HIGH      230
#define NAVKEYMOVE_RIGHT_LOW    375
#define NAVKEYMOVE_RIGHT_HIGH   425
#define NAVKEYMOVE_DOWN_LOW     555
#define NAVKEYMOVE_DOWN_HIGH    625
#define NAVKEYMOVE_LEFT_LOW     800
#define NAVKEYMOVE_LEFT_HIGH    860
#ifndef NAVKEY_MOVE
#define NAVKEY_MOVE				A11
#endif
#ifndef NAVKEY_PRESS
#define NAVKEY_PRESS			19
#endif
#ifndef MIN_TIME1_5
#define MIN_TIME2				200
               
#endif

extern volatile bool menuPress;	//If ever put into an interrupt, make these variables volatile
extern uint8_t menuMove;
extern unsigned long lastKeyMoveTime;

void navKeyUpdate();
void navKeyAttachInterruptMenuPress();
void navKeyDettachInterruptMenuPress();
//Define void navKeyInterruptCenterPress() in code
void navKeyInterruptCenterPress();	//Declaration
#endif
