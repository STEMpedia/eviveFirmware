/*
 * This firmware is developed for evive v1 https://evive.cc
 * evive library includes all the sub libraries supplied with the firmware
 * and other pre-installed arduino libraries
 * Version 1.1.0
 *
 * This is licensed under GNU GPL V3 [http://www.gnu.org/licenses/gpl.txt].
 * Written by Dhrupal R Shah for evive platform, Agilo Research Pvt. Ltd.
 * Created on: March 1, 2016
 * Updated on: 20180209
 * Contact: support@evive.cc
 * Copyright (c) 2018 Agilo Research Pvt. Ltd.  All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef EVIVE_H
#define EVIVE_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <inttypes.h>

#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include "Fastio.h"
void eviveFirmware();
void drawStatusBar();
bool isTouched(int touchpin);

#include <Arduino.h>
#include "TFT_ST7735.h" 			//Library for evive TFT Display type (1.8" SPI communication based TFT with ST7735R driver
#include <SPI.h>
#include <Wire.h>

#include "Configuration.h"		//Set configuration for including/excluding evive features. (Pin Configuration are defined in "EvivePins.h".)
#include "EvivePins.h"				//Pin Configuration of evive

#include "Language.h"					//Language based menu interface
#include "Language_en.h"			//English Language messages
#include "Bitmaps.h"					//Saved Bitmaps like evive logo
#include "Screen.h"						//Handles the functioning of menu based visual interface
#include "Navkey.h"						//Functions for Joystick/5way navigation key
#include "Button.h"						//Library for buttons (predefined variables
#include "Potentiometer.h"		//Library for potentiometer
#include "SlideSwitch.h"			//Library for SlideSwitch
#include "Motor.h"						//Library for motors
#include "SerialMonitor.h"		//Library reads data from the selected serial ports in menu and displays on TFT screen
#include "Servo.h"						//Arduino Servo Library with change in primary use of Timer1, in place of Timer5 for Mega
#include "ServoControl.h"			//Library for motors
#include "Stepper.h"					//Arduino Stepper Library
#include "Action.h"						//Framework to add multiple functions in Arduino loop via callback functions of menu (including user defined programs) and running multiple function in background
#include "Ade7912_Adc.h"			//Library with functions to use ADE7912 (ADC IC) for sensing probes in evive, namely Probe V and Probe I/V
#include "Dac_MCP4725.h"			//Library for DAC IC MCP4725 and Beta function generator (Based on AdaFruit lib)
#include "MPR121_Touch.h"			//Library for Capacitive Touch Sensing MPR121 (Based on AdaFruit lib)
#include "AddUserDefinedFunctions.h"	//Functions and template for users to add multiple user defined functions to be selected from menu
//#include "Examples.h"					//Functions, sample codes and template for users to add multiple examples to be selected from menu
//#include "TftMonitor.h"				//Library implements similar view of serial monitor of Arduino desktop IDE
#include "Plot.h"							//Library to plot any variable on TFT screen

int freeRam ();

// Added to fix Arduino 1.0 compile issues 12/11/11 - TVHeadedRobots
//#if defined(ARDUINO) && ARDUINO < 100
//#include <WProgram.h>
//#else
//#include <Arduino.h>
//#endif

#endif
