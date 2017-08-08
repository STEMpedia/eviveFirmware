#ifndef addUserDefinedFunctions_H
#define addUserDefinedFunctions_H

//IMPORTANT: uncomment the desired user defined functions and give desired name
#define USER_DEFINED_FUNCTION_1 	"Eg: Blink"
#define USER_DEFINED_FUNCTION_2 	"Eg: Blink Analog Input"
#define USER_DEFINED_FUNCTION_3 	"Eg: TftSerial on A9"
#define USER_DEFINED_FUNCTION_4 	"Eg: Plot A9"
#define USER_DEFINED_FUNCTION_5 	"User Def fun name 5"


#include "evive.h"

void loop_user_def_fun_1();
void loop_user_def_fun_2();
void loop_user_def_fun_3();
void loop_user_def_fun_4();
void loop_user_def_fun_5();

void add_user_def_fun(uint8_t);
void remove_other_user_def_fun(uint8_t);

#endif
