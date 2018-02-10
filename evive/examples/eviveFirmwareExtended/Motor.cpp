/*Motor.cpp is a library to use motor drivers like SN754410NE, L293D, etc. The control parameters
	for each motor have 3 pins: Direction 1, Direction 2 and PWM.
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

  Created on: Nov, 2014
	Developed by Kartik Gupta and Deep Goel with Robocon Team 2014, IIT Kanpur
  Last Edit: 20180208
  
  How to use this library:
  A well explained tutorial can be found at:
	https://evive.cc/evive-documentation/plug-and-play-interface/dc-motor/
	
  Steps:
  1) Declare class object: Motor Motor1 = Motor(motor1Dir1, motor1Dir2, motor1PWM);
  2) Function list:
		-Motor();	Constructor
		-Motor(int Dir1,int Dir2,int Pwm);	Constructor with attachments of pins
		-void attachMotor(int Dir1,int Dir2,int Pwm);	Attachments of pins
		-void moveMotor(int Pwm);	Positive for CW and negative for CCW
		-void moveMotor(int Dir1,int Dir2,int Pwm);	dir1 and dir2 can be 1 or 0,pwm can only be positive for CW
		-void stopMotor();	By default stop motor will lock motor
		-void lockMotor();	To lock the motor
		-void freeMotor();	Free the motor
		-void setMeanSpeed(int Speed);	Sets the mean speed with which motor moves when speed=100%
		-void setMotorSpeed(int Speed);	Positive for CW and negative for CCW. Speed in percentage of mean speed
		-void setMotorSpeed(int Dir1,int Dir2,int Speed);	dir1 and dir2 can be 1 or 0
		-void changePWM(int Pwm);	Just to change the PWM in whatever direction the motor was moving
		-void changeSpeed(int Speed);	Just to change the speed (In percentage) not the direction
		-int getDirection();	+1 for CW and -1 for CCW and 0 for free or locked
		-int isFree();	+1 for free and 0 for not free
		-int isLocked();	+1 for locked and 0 for not locked
		-int getSpeed();	Returns speed in % of mean speed
		-int getPWM();	Returns positive for CW and negative for CCW.
		-void startSmoothly(int Speed);	Positive for CW and negative for CCW.
		-void stopSmoothly();	
		
  NOTE: motor will be considered CW if dir1 is HIGH and DIR2 is LOW
 */

#include "Motor.h"

Motor::Motor()									//constructor
{
	attachMotor(-1, -1, -1);
}

Motor::Motor(uint8_t Dir1, uint8_t Dir2, uint8_t Pwm)		// parametrised constructor
{
	attachMotor(Dir1, Dir2, Pwm);
}

void Motor::attachMotor(uint8_t Dir1, uint8_t Dir2, uint8_t Pwm) {
	pwm_pin = Pwm;
	dir1_pin = Dir1;
	dir2_pin = Dir2;
	if (dir1 != -1 && dir2 != -1 && pwm_pin != -1) {
		pinMode(pwm_pin, OUTPUT);
		pinMode(dir1_pin, OUTPUT);
		pinMode(dir2_pin, OUTPUT);
	}
	pwm = 0;
	speed = 0;
	mean_speed = 255;
	//lockMotor();	//Lock the Motor initially
	damping = 10;
}

void Motor::moveMotor(int Pwm)			//+ve for CW and -ve for CCW.
{

	if (Pwm >= 0) {
		digitalWrite(dir1_pin, HIGH);
		digitalWrite(dir2_pin, LOW);
	} else {
		digitalWrite(dir1_pin, LOW);
		digitalWrite(dir2_pin, HIGH);
	}
	changePWM(Pwm);
#ifdef __DEBUG__
		Serial.println(F("PWM="));
		Serial.print(Pwm);
#endif
}

void Motor::moveMotor(bool Dir1, bool Dir2, int Pwm) {
	dir1 = Dir1;
	dir2 = Dir2;
	digitalWrite(dir1_pin, Dir1);
	digitalWrite(dir2_pin, Dir2);
	//	if(Dir1==1 && Dir2==0)
	//		moveMotor(Pwm);
	//	if(Dir1==0 && Dir2==1)
	//		moveMotor(-Pwm);
	changePWM(Pwm);
}

void Motor::stopMotor() 				//By default stop motor will lock motor
{
	lockMotor();
	//freeMotor()						//Uncomment freeMotor if required
}

void Motor::lockMotor() {
	digitalWrite(dir1_pin, HIGH);			//case of motor lock
	digitalWrite(dir2_pin, HIGH);
	analogWrite(pwm_pin, 255);
	pwm = 0;
}

void Motor::freeMotor() {
	digitalWrite(dir1_pin, LOW);			//case of motor free
	digitalWrite(dir2_pin, LOW);
	analogWrite(pwm_pin, 0);
	pwm = 0;
}

void Motor::setMeanSpeed(int Speed)	//Sets the meanspeed with which motor moves when speed=100%
{
	mean_speed = Speed;
}

void Motor::setMotorSpeed(int Speed)//+ve for CW and -ve for CCW. Speed in percentage of meanspeed
{
	if (Speed > 100)
		Speed = 100;
	if (Speed < -100)
		Speed = -100;
	speed = Speed;

	moveMotor(Speed * mean_speed / 100);
}

void Motor::setMotorSpeed(bool Dir1, bool Dir2, int Speed) {
	if (Speed > 100)
		Speed = 100;
	if (Speed < -100)
		Speed = -100;
	speed = Speed;
	moveMotor(Dir1, Dir2, Speed * mean_speed / 100);
}

void Motor::changePWM(int Pwm)					//Just to change the PWM
{
	pwm = Pwm > 255 ? 255 : (Pwm < -255 ? -255 : Pwm);
	analogWrite(pwm_pin, abs(pwm));
}

void Motor::changeSpeed(int Speed)		//Just to change the speed (In percentage)
{
	if (Speed > 100)
		Speed = 100;
	if (Speed < -100)
		Speed = -100;
	speed = Speed;
	changePWM(Speed * mean_speed / 100);
}

int Motor::getDirection() {
	dir1 = digitalRead(dir1_pin);
	dir2 = digitalRead(dir2_pin);
	if (dir1 == dir2)
		return 0;
	else
		return ((dir1 > dir2) ? 1 : -1);
}

int Motor::isFree() {
	return (getDirection() == 0 && dir1 == 0);
}

int Motor::isLocked() {
	return (getDirection() == 0 && dir1 == 1);
}

int Motor::getSpeed() {
	return (pwm * 100 / mean_speed);
}

int Motor::getPWM() {
	return pwm;
}

void Motor::startSmoothly(int Speed) {
	if (Speed > 100)
		Speed = 100;
	if (Speed < -100)
		Speed = -100;
	int i;
	if (Speed >= 0) {
		digitalWrite(dir1_pin, HIGH);
		digitalWrite(dir2_pin, LOW);
	} else {
		digitalWrite(dir1_pin, LOW);
		digitalWrite(dir2_pin, HIGH);
	}
	for (i = 0; i <= Speed; i = i + COUNT_CONST)
	{
		changeSpeed(i);
		delay(COUNT_CONST * damping);
		speed = i;
		pwm = speed * mean_speed / 100;
	}
}
void Motor::stopSmoothly() {
	int i;
	speed = getSpeed();
	for (i = speed; i >= 0; i = i - COUNT_CONST)
	{
		changeSpeed(i);
		delay(COUNT_CONST * damping);
		speed = i;
		pwm = speed * mean_speed / 100;
	}
	lockMotor();
}

bool _MOTOR1_EN = 0;
bool _MOTOR2_EN = 0;
Motor motor1, motor2;

void controlMotor() {
#ifdef __DEBUG__
	Serial.println(F("MotorCtrl"));
#endif
	if (_MOTOR1_EN) {
		motor1.moveMotor(slideSw1.readPin1(), slideSw1.readPin2(),
				pot1.getValue() / 4);
	}
	if (_MOTOR2_EN) {
		motor2.moveMotor(slideSw2.readPin1(), slideSw2.readPin2(),
				pot2.getValue() / 4);
	}
}

void addMotor1() {
	_MOTOR1_EN = 1;
	_SERVO1_EN = 0;
	_STEPPER_EN = 0;
	pinMode(SLIDESW1_D1, INPUT);
	pinMode(SLIDESW1_D2, INPUT);
	motor1.attachMotor(MOTOR1_D1, MOTOR1_D2, MOTOR1_EN);
	actionAdd(controlMotor, 1);
}

void addMotor2() {
	_MOTOR2_EN = 1;
	_SERVO2_EN = 0;
	_STEPPER_EN = 0;
	pinMode(SLIDESW2_D1, INPUT);
	pinMode(SLIDESW2_D2, INPUT);
	motor2.attachMotor(MOTOR2_D1, MOTOR2_D2, MOTOR2_EN);
	actionAdd(controlMotor, 1);
}
void addMotor12() {
	addMotor1();
	addMotor2();
}
