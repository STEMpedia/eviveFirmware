#include "navkey.h"

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
