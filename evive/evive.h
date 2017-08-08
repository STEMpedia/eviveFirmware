/*
 * This firmware is developed for evive v1
 * evive library includes all the sub libraries supplied with the firmware
 * and other pre-installed arduino libraries
 * Version 1.0.2
 *
 * This is licensed under GNU GPL V3 [http://www.gnu.org/licenses/gpl.txt].
 * Written by Dhrupal R Shah for evive platform, Agilo Research Pvt. Ltd.
 * Created on: March 1, 2016
 * Updated on: 2017, May 31
 * Contact: support@evive.cc
 * Copyright (c) 2017 Agilo Research Pvt. Ltd.  All rights reserved.
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
#include "fastio.h"

// Added to fix Arduino 1.0 compile issues 12/11/11 - TVHeadedRobots
//#if defined(ARDUINO) && ARDUINO < 100
//#include <WProgram.h>
//#else
//#include <Arduino.h>
//#endif

#include <Arduino.h>
//#include "Adafruit_GFX.h"
//#include "Adafruit_ST7735.h"
#include "TFT_ST7735.h" 
#include <SPI.h>
#include <Wire.h>



#include "Configuration.h"

#include "EvivePins.h"
#include "Language.h"
#include "Language_en.h"
#include "Bitmaps.h"
#include "Screen.h"
#include "Navkey.h"
#include "Button.h"
#include "Potentiometer.h"
#include "SlideSwitch.h"
#include "Motor.h"
#include "SerialMonitor.h"
#include "Servo.h"
#include "ServoControl.h"
#include "Stepper.h"
#include "Action.h"
#include "Ade7912_Adc.h"
#include "Dac_MCP4725.h"
#include "MPR121_Touch.h"
#include "AddUserDefinedFunctions.h"
#include "TftSerial.h"
#include "Plot.h"
//#include "screenImplementation.h"

#endif
