#ifndef ACTION_H
#define ACTION_H
#include "evive.h"

typedef void (*actionFunc)();	// Function pointer to action functions.
extern actionFunc actionFuncList[20];
extern uint8_t actionFuncListNum;

void actionAdd(actionFunc, bool);
void actionAdd(actionFunc);
void actionRemove(actionFunc);	//Remove action (function) from action function list using the name of the function
void actionRemove(uint8_t);			//Remove action (function) from action function list using number in array
void action();

#endif
