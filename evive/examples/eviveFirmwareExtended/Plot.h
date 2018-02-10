/*Plot.h is a library for plotting any variable on TFT ST7735 (in evive)
	
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

  Created on: Jul , 2017
  Last Edit: 20180208
  Developed by: Harsh Chittora
	
  How to use this library:
  A well explained tutorial can be found at:

*/

#ifndef PLOT_H
#define PLOT_H
//#include <arduino.h>

//#include "TFT_ST7735.h"
//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_ST7735.h>

//#include <SPI.h>
#include "evive.h"
//#include "screenImplementation.h"

class Plotter
{
	public:
		int value;
		
	public:
		Plotter();
		void 	begin(int range);
		void 	draw(int value);
		
	private:
		void 	ClearAndDrawDot(int i);
		void 	DrawGrid(int i);
		void	setRange(int range);
		
		
	private:
		int i;
		//TFT_ST7735 tft;
		int values[2][160];
		int range;
		int factor;
		
};

#endif
