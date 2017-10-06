/*To Control any motor with evive default M1 & M2 or motor driver on any pin
  Made by Deep Goel and Kartik Gupta

  NOTE: motor will be considered cw if dir1 is HIGH and DIR2 is LOW
 */
#ifndef  MOTOR_H
#define  MOTOR_H
#include "evive.h"

#ifndef COUNT_CONST 
#define COUNT_CONST 3
#endif //for COUNT_CONST

class Motor 
{
	//    private:


public:
	// Variables

	uint8_t dir1_pin;					//stores pin no of direction1
	uint8_t dir2_pin;					//stores pin no of direction2
	uint8_t pwm_pin;					//stores pin no of pwm pin
	bool dir1;		                //stores value of DIR1PIN as 1 or 0
	bool dir2;                      //stores value of DIR2PIN as 1 or 0
	int pwm;						//pwm: Stores the pwm value given to the motor
	int mean_speed;					//mean_speed : The value to which motor moves when speed=100%
	float speed;					//speed		: Speed of the motor in percentage of meanspeed
	int damping;                 	//to be changed later by trial

	// Functions
public:
	Motor();						//constructor
	Motor(uint8_t Dir1, uint8_t Dir2, uint8_t Pwm);	//constructor with attachments of pins
	void attachMotor(uint8_t Dir1, uint8_t Dir2, uint8_t Pwm); //attachments of pins
	void moveMotor(int Pwm);			//+ve for CW and -ve for CCW.
	void moveMotor(bool Dir1,bool Dir2,int Pwm); // dir1 and dir2 can be 1 or 0,pwm can only be +ve for CW
	void stopMotor();				//By default stop motor will lock motor
	void lockMotor();				//To lock the motor (HIGH-HIGH)
	void freeMotor();				//Free the motor (LOW-LOW)
	void setMeanSpeed(int Speed);	//Sets the meanspeed with which motor moves when speed=100%
	void setMotorSpeed(int Speed);		//+ve for CW and -ve for CCW. Speed in percentage of meanspeed (-100%<=Range<=100%)
	void setMotorSpeed(bool Dir1,bool Dir2,int Speed); // dir1 and dir2 can be 1 or 0 (-100%<=Range<=100%)
	void changePWM(int Pwm);		//Just to change the PWM in whatever direction the motor was moving (-255<=Range<=255)
	void changeSpeed(int Speed);	//Just to change the speed (In percentage) not the direction (-100%<=Range<=100%)
	int getDirection();             //+1 for cw and -1 for ccw and 0 for free or locked
	int isFree();                  //+1 for free and 0 for not free
	int isLocked();                //+1 for locked and 0 for not locked
	int getSpeed();                // returns speed in % of mean speed
	int getPWM();                  // returns +ve for CW and -ve for CCW.
	void startSmoothly(int Speed);   //+ve for CW and -ve for CCW.
	void stopSmoothly();
};		

//No varible can be assigned any value here as variables are actually declared in motor.cpp
//Using extern, variables can be used in other libraries without declaration.
extern bool _MOTOR1_EN;
extern bool _MOTOR2_EN;
extern  Motor motor1, motor2;

//void controlMotor();			//auto motor control from pots and slide switches
void addMotor1();
void addMotor2();
void addMotor12();

#endif
