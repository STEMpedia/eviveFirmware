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

#ifndef addUserDefinedFunctions_H
#define addUserDefinedFunctions_H

//IMPORTANT: uncomment the required user defined function(s) and give desired name below. Then in AddUserDefinedFunctions.cpp, go to the corresponding "setup" and "loop" functions to write the program (defination).
#define USER_DEFINED_FUNCTION_1 	"Eg: Blink"
#define USER_DEFINED_FUNCTION_2 	"Eg: Blink Analog Input"
#define USER_DEFINED_FUNCTION_3 	"User Def fun name 3"
//#define USER_DEFINED_FUNCTION_4 	"User Def fun name 4"
//#define USER_DEFINED_FUNCTION_5 	"User Def fun name 5"

#include "evive.h"

void loop_user_def_fun_1();
void loop_user_def_fun_2();
void loop_user_def_fun_3();
void loop_user_def_fun_4();
void loop_user_def_fun_5();

void add_user_def_fun(uint8_t);
void remove_other_user_def_fun(uint8_t);

#endif
