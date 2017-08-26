/*
 * addFunction.cpp
 *
 *  Created on: Jul 30, 2016
 *      Author: dhrups
 */
#include "Examples.h"

/////////////////Setup and loop functions for user defined functions/////////////////

#ifdef EXAMPLE_1
// the setup function runs once when you select the user defined function
void setup_example_1(){
	// initialize digital pin LED_BUILTIN as an output.
	pinMode(LED_BUILTIN, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_example_1(){
	// Remove this example code and put your user defined (custom) code here, to run repeatedly:
	digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
	delay(100);                       // wait for a second
	digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
	delay(100);                       // wait for a second
}
#endif
#ifdef EXAMPLE_2
// the setup function runs once when you select the user defined function
void setup_example_2(){
	// initialize digital pin LED_BUILTIN as an output.
	pinMode(LED_BUILTIN, OUTPUT);
}
// the loop function runs continuously when you select the user defined function
void loop_example_2(){
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
#endif

#ifdef EXAMPLE_3
// the setup function runs once when you select the user defined function
void setup_example_3(){
	tft.setCursor(20,80);
	tft.fillRect(20, 80, 150, 8, ST7735_BLACK);
	tft.setTextColor(ST7735_RED, ST7735_BLACK);
	tft.print(F("Analog Value: "));
}

// the loop function runs continuously when you select the user defined function
void loop_example_3(){
	tft.setCursor(100,80);
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.print(analogRead(A9));
	tft.print(F("   "));			//to remove the remaining digits of any bigger number (in terms of number of digits) printed last time
}
#endif

#ifdef EXAMPLE_4
// the setup function runs once when you select the user defined function
void setup_example_4(){
	ade791x_init(); //Starts the precision sensing IC
	delay(500);
	tft.setTextColor(ST7735_RED);
	tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 8);
	tft.println(F("   Probe V"));
	tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 10);
	tft.println(F("   V"));
	Serial.println(F("Setup 4 ends"));
}
// the loop function runs continuously when you select the user defined function
void loop_example_4(){
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.setCursor(LEFT_MARGIN + 19, TOP_MARGIN + ROW_HEIGHT * 9);
	tft.print(ade791x_read_v1() / 1000.0);
	//tft.print(ade791x_read_vim() / 1000.0);
	tft.println("    ");
	delay(100);
}
#endif

#ifdef EXAMPLE_5
// the setup function runs once when you select the user defined function
TftSerial TftMonitor;
void setup_example_5(){
	TftMonitor.begin();
	pinMode(A9,INPUT);
}

// the loop function runs continuously when you select the user defined function
void loop_example_5(){
	//TftMonitor.print("Pot 1 value: ");
	TftMonitor.println(analogRead(A9)); 		//Pot1 Value is Printed on TFT Monitor
	delay(50);
}
#endif
///////////////////// Write other functions below this ////////////////////
//Same as  Arduino <XXX.ino> file








//DO NOT EDIT FOLLOWING FUNCTION
void add_example(uint8_t funNum){
	if(funNum==1){
#ifdef EXAMPLE_1
		setup_example_1();
		actionAdd(loop_example_1, 1);
#endif
	}
#ifdef EXAMPLE_2
	else if(funNum==2){
		setup_example_2();
		actionAdd(loop_example_2, 1);
	}
#endif
#ifdef EXAMPLE_3
	else if(funNum==3){
		setup_example_3();
		actionAdd(loop_example_3, 1);
	}
#endif
#ifdef EXAMPLE_4
	else if(funNum==4){
		setup_example_4();
		actionAdd(loop_example_4, 1);
	}
#endif
#ifdef EXAMPLE_5
	else if(funNum==5){
		setup_example_5();
		actionAdd(loop_example_5, 1);
	}
#endif
}

void remove_other_example(uint8_t funNum){
#ifdef EXAMPLE_1
	if(funNum!=1){
		actionRemove(loop_example_1);
	}
#endif
#ifdef EXAMPLE_2
	if(funNum!=2){
		actionRemove(loop_example_2);
	}
#endif
#ifdef EXAMPLE_3
	if(funNum!=3){
		actionRemove(loop_example_3);
	}
#endif
#ifdef EXAMPLE_4
	if(funNum!=4){
		actionRemove(loop_example_4);
	}
#endif
#ifdef EXAMPLE_5
	if(funNum!=5){
		actionRemove(loop_example_5);
	}
#endif
}
