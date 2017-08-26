#ifndef example_H
#define example_H

//IMPORTANT: uncomment the required Example(s). Then in Examples.cpp, go to the corresponding "setup" and "loop" functions to write the program (definition).
#define EXAMPLE_1 	"Blink"
#define EXAMPLE_2 	"Blink Analog Input"
#define EXAMPLE_3 	"TFT Display (Pot1)"
#define EXAMPLE_4 	"Probe V Sense"
#define EXAMPLE_5 	"TFT Serial Monitor (Pot1)"


#include "evive.h"

#ifdef EXAMPLE_1
void loop_example_1();
#endif
#ifdef EXAMPLE_2
void loop_example_2();
#endif
#ifdef EXAMPLE_3
void loop_example_3();
#endif
#ifdef EXAMPLE_4
void loop_example_4();
#endif
#ifdef EXAMPLE_5
void loop_example_5();
#endif

void add_example(uint8_t);
void remove_other_example(uint8_t);

#endif
