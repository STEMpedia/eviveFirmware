/*
 * evive.cpp
 * Created on: April 16, 2016
 * Author: dhrups
 * Last update: May 10, 2016
 * Version: 1.0
 */
#include "evive.h"

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
