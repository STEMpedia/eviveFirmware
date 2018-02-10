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

#include "Navkey.h"

volatile bool menuPress = 0;	//If ever put into an interrupt, make these variables volatile
uint8_t menuMove = 0;
unsigned long lastKeyMoveTime = 0;

void navKeyUpdate(){
	//unsigned long thisTime=millis();
	if ((millis()-lastKeyMoveTime)<MIN_TIME2){ //Too less time has passed
		menuPress=0;
		menuMove=0;
		return;
	}
	else{ //Enough time has passed
		if(digitalRead(NAVKEY_PRESS)){ //Press
			lastKeyMoveTime=millis();
			menuPress = 1;
			#ifdef __DEBUG__
			Serial.println(F("Navkey Press"));
			#endif
			menuMove=0;
			return;
		}
		else{
			menuPress = 0;
			uint16_t navKeyMove=analogRead(NAVKEY_MOVE);
			if (navKeyMove<20){ //No press, no move
				menuMove=0;
			}
			else{ //No press, yes move
				//#ifdef __DEBUG__
				Serial.print(F("NavKeyMove: "));
				Serial.println(navKeyMove);
				//#endif
				if ((navKeyMove>NAVKEYMOVE_UP_LOW)&&(navKeyMove<NAVKEYMOVE_UP_HIGH)){ //Up
					menuMove=1;
					lastKeyMoveTime=millis();
				}
				else if ((navKeyMove>NAVKEYMOVE_RIGHT_LOW)&&(navKeyMove<NAVKEYMOVE_RIGHT_HIGH)){ //Right
					menuMove=2;
					lastKeyMoveTime=millis();
				}
				else if ((navKeyMove>NAVKEYMOVE_DOWN_LOW)&&(navKeyMove<NAVKEYMOVE_DOWN_HIGH)){ //Down
					menuMove=3;
					lastKeyMoveTime=millis();
				}
				else if ((navKeyMove>NAVKEYMOVE_LEFT_LOW)&&(navKeyMove<NAVKEYMOVE_LEFT_HIGH)){ //Left
					menuMove=4;
					lastKeyMoveTime=millis();
				}
			}
		}
	}
}

//Use Attach Center Press key of Navigation Key (Joystick) as Interrupt. The program running on a controller is normally running sequentially instruction by instruction. An interrupt is an external event that interrupts the running program and runs a special interrupt service routine (here ISR = navKeyInterruptCenterPress). After the ISR has been finished, the running program is continued with the next instruction.
void navKeyAttachInterruptMenuPress(){
		//Define void navKeyInterruptCenterPress() in code
		attachInterrupt(digitalPinToInterrupt(NAVKEY_PRESS), navKeyInterruptCenterPress, RISING);
}

//Dettach Center Press key of Navigation Key (Joystick) as Interrupt
void navKeyDettachInterruptMenuPress(){
	detachInterrupt(digitalPinToInterrupt(NAVKEY_PRESS));
}

//Comment following function if ISR function is required
//and paste it at required destination (even outside this library)
// void navKeyInterruptCenterPress(){
	// put your ISR (intrrupt) code here.
// }
