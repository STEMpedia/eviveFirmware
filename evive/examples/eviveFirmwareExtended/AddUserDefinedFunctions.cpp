/*AddUserDefinedFunctions.cpp defines the User Defined Functions to be
  displayed on the evive's menu based visual interface.
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
  
  Steps:
  1) Mention the name of user defined function name in AddUserDefinedFunctions.h
     in macro #define USER_DEFINED_FUNCTION_X 	"<Fucntion name to be dispalyed>"
  2) Write the corresponding code in AddUserDefinedFunctions.cpp as follows:
			-setup (runs one time)
			-loop (runs continuosly)
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
	digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
  delay(100);                       // wait for a second
}

// The setup function runs once when you select the user defined function
void setup_user_def_fun_2(){
  // Remove this example code and put your setup code here:
  pinMode(LED_BUILTIN, OUTPUT);				// initialize digital pin LED_BUILTIN as an output.
}
// The loop function runs continuously when you select the user defined function
void loop_user_def_fun_2(){
	// Remove this example code and put your user defined (custom) code here, to run repeatedly:
	uint16_t sensorValue = analogRead(A9);	// read the value from the sensor
    digitalWrite(LED_BUILTIN, HIGH);		// turn the ledPin on
    delay(sensorValue);						// stop the program for <sensorValue> milliseconds
  	digitalWrite(LED_BUILTIN, LOW);			// turn the ledPin off
    delay(sensorValue);						// stop the program for for <sensorValue> milliseconds
}

// the setup function runs once when you select the user defined function
void setup_user_def_fun_3(){
	// put your setup code here:
}

// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_3(){
	// put your user defined (custom) code here, to run repeatedly:
}

// the setup function runs once when you select the user defined function

void setup_user_def_fun_4(){
  // put your setup code here:

}
// the loop function runs continuously when you select the user defined function
void loop_user_def_fun_4(){
	// put your user defined (custom) code here, to run repeatedly:

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
