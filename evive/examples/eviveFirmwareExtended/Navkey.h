/*Navkey.cpp contains function for joystick/5way navigation key to update 
	global variables menuPress and menuMove (this are accesible to the user).
	It also include enabling/disenabling interrupt on center press of navkey (Pin 19)
	
  Copyright (C) 2018, Agilo Research

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/

  Created on: Jul 30, 2016
  Last Edit: 20180208
  
  How to use this library:
  A well explained tutorial can be found at:
  https://evive.cc/evive-documentation/menu-interface/user-defined-functions/
  
	States of variables:
	menuPress = True or False
	menuMove = 1 (up), 2 (right), 3 (down) and 4 (left)
  
	Steps:
  1) Function navKeyUpdate() updates two variables: menuMove and menuPress 
	2) Depending on the value of menuPress and menuMove, any activity can be sensed.
	3) To enable/disenable interuppt on Pin 19, use navKeyAttachInterruptMenuPress() or
		navKeyDettachInterruptMenuPress
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

//Global accessible variables 
extern volatile bool menuPress;				//menuPress = True or False. If ever put into an interrupt, make these variables volatile
extern uint8_t menuMove;							//menuMove = 1 (up), 2 (right), 3 (down) and 4 (left)
extern unsigned long lastKeyMoveTime;

void navKeyUpdate();									//Call frequently to update the state of recent activity at navkey/joystick/5way-key
void navKeyAttachInterruptMenuPress();
void navKeyDettachInterruptMenuPress();
//Define void navKeyInterruptCenterPress() in code
void navKeyInterruptCenterPress();		//Declaration
#endif