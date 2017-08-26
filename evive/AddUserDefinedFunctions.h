#ifndef addUserDefinedFunctions_H
#define addUserDefinedFunctions_H

//IMPORTANT: uncomment the required user defined function(s) and give desired name below. Then in AddUserDefinedFunctions.cpp, go to the corresponding "setup" and "loop" functions to write the program (defination).
#define USER_DEFINED_FUNCTION_1 	"Eg: Blink"
#define USER_DEFINED_FUNCTION_2 	"User Def fun name 2"
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
