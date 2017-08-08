/*
 * addFunction.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: dhrups
 */
 #include "AddUserDefinedFunctions.h"

/////////////////Setup and loop functions for user defined functions/////////////////

// the setup function runs once when you select the user defined function
void setup_user_def_fun_1(){
  // Remove this example code and put your setup code here:
	// initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_1(){
	// Remove this example code and put your user defined (custom) code here, to run repeatedly:
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_2(){
  // Remove this example code and put your setup code here:
	// initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_2(){
	// Remove this example code and put your user defined (custom) code here, to run repeatedly:
  // read the value from the sensor:
  uint16_t sensorValue = analogRead(A9);
  // turn the ledPin on
  digitalWrite(LED_BUILTIN, HIGH);
  // stop the program for <sensorValue> milliseconds:
  delay(sensorValue);
  // turn the ledPin off:
  digitalWrite(LED_BUILTIN, LOW);
  // stop the program for for <sensorValue> milliseconds:
  delay(sensorValue);
}

// the setup function runs once when you select the user defined function
TftSerial serialMonitorTFT = TftSerial();
void setup_user_def_fun_3(){
	// put your setup code here:
  serialMonitorTFT.begin();
  pinMode(A9,INPUT);
}

// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_3(){
	// put your user defined (custom) code here, to run repeatedly:
  //serialMonitorTFT.println(123.123);
  serialMonitorTFT.println("Value of potentiometer number 1 is ");
	serialMonitorTFT.println(1.0333253232);
	serialMonitorTFT.print(1.0333253232);
	serialMonitorTFT.print(analogRead(A9));
	serialMonitorTFT.print('A');
		//serialMonitorTFT.print(12.123);
			//serialMonitorTFT.println(425);
	delay(200);
	//serialMonitorTFT.println();
	//serialMonitorTFT.println("");
	// delay(200);
  /*
	serialMonitorTFT.print(analogRead(A10));
	serialMonitorTFT.print(analogRead(A9));
	serialMonitorTFT.print(analogRead(A8));
	serialMonitorTFT.print(analogRead(A7));
	serialMonitorTFT.print(analogRead(A10));
	serialMonitorTFT.print(analogRead(A9));
	serialMonitorTFT.print(analogRead(A8));
	serialMonitorTFT.print(analogRead(A7));	
	serialMonitorTFT.println();*/
	delay(200);
	//serialMonitorTFT.println();
	delay(1000);
}

// the setup function runs once when you select the user defined function

Plotter pl = Plotter();
void setup_user_def_fun_4(){
  // put your setup code here:
  pl.begin(1024);
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_4(){
	// put your user defined (custom) code here, to run repeatedly:
  pl.draw(analogRead(A9));
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_5(){
  // put your setup code here:
}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_5(){
	// put your user defined (custom) code here, to run repeatedly:
}

///////////////////// Write other functions below this ////////////////////
//Same as  Arduino <XXX.ino> file




//DO NOT EDIT FOLLOWING FUNCTION
void add_user_def_fun(uint8_t funNum){
  if(funNum==1){
    setup_user_def_fun_1();
    actionAdd(loop_user_def_fun_1, 1);
  }
  else if(funNum==2){
    setup_user_def_fun_2();
    actionAdd(loop_user_def_fun_2, 1);
  }
  else if(funNum==3){
    setup_user_def_fun_3();
    actionAdd(loop_user_def_fun_3, 1);
  }
  else if(funNum==4){
    setup_user_def_fun_4();
    actionAdd(loop_user_def_fun_4, 1);
  }
  else if(funNum==5){
    setup_user_def_fun_5();
    actionAdd(loop_user_def_fun_5, 1); 
  }
}

void remove_other_user_def_fun(uint8_t funNum){
	if(funNum!=1){
    actionRemove(loop_user_def_fun_1);
  }
  if(funNum!=2){
    actionRemove(loop_user_def_fun_2);
  }
  if(funNum!=3){
    actionRemove(loop_user_def_fun_3);
  }
  if(funNum!=4){
    actionRemove(loop_user_def_fun_4);
  }
  if(funNum!=5){
    actionRemove(loop_user_def_fun_5); 
  }
}
