#ifndef  SERVO_CONTROL_H
#define  SERVO_CONTROL_H

#include "evive.h"

//No varible can be assigned any value here as variables are actually declared in motor.cpp
//Using extern, variables can be used in other libraries without declaration.
extern bool _SERVO1_EN;
extern bool _SERVO2_EN;
extern Servo servo1, servo2;

void controlServo();			//auto motor control from pots and slide switches
void addServo1();
void addServo2();
void addServo12();
int prevValueServo1();
int prevValueServo2();

#endif
