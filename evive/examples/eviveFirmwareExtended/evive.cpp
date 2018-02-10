/*
 * This firmware is developed for evive v1 https://evive.cc
 * evive library includes all the sub libraries supplied with the firmware
 * and other pre-installed arduino libraries
 * Version 1.1.0
 *
 * This is licensed under GNU GPL V3 [http://www.gnu.org/licenses/gpl.txt].
 * Written by Dhrupal R Shah for evive platform, Agilo Research Pvt. Ltd.
 * Created on: April 16, 2016
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

#include "evive.h"

int freeRam ()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}

//To load evive firmware in setup, loop or any function
void eviveFirmware(void)
{
  exitmenu = 1;
  Serial.begin(250000);
  tft_init(INITR_BLACKTAB);
  while (1)
  {
    tft_update();            //Updates the TFT on any action in menu
    action();                 //Runs the function in array actionFuncList. All functions/user defined programs are added in action FuncList array upon selection.
    if (exitmenu == 0)
      break;
  }
  tft.fillScreen(ST7735_BLACK);
  tft.drawBitmap(45, 29, evive_logo, 71, 71, ST7735_BLUE);
}

//Shit! remove this function from here and add this inside MRP library
bool isTouched(int touchPin)
{
  return touchPins.touched()& _BV(touchPin-1) ;
}