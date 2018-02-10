/*Plot.cpp is a library for plotting any variable on TFT ST7735 (in evive)
	
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
#include "Plot.h"

//#include "screenImplementation.h"

#define TFT_CS  48          // Chip select line for TFT display
#define TFT_DC   49          // Data/command line for TFT
#define TFT_RST  47   
//const int TFT_WIDTH = 160;
//const int TFT_HEIGHT = 128;
const int SAMPLES = 160;
const int DOTS_DIV = 20;

#ifndef LEFT_MARGIN
#define LEFT_MARGIN     2
#endif
#ifndef RIGHT_MARGIN
#define RIGHT_MARGIN    2
#endif
#ifndef TOP_MARGIN
#define TOP_MARGIN      14
#endif
#ifndef BOTTOM_MARGIN
#define BOTTOM_MARGIN   2
#endif
#ifndef TFT_HEIGHT
#define TFT_HEIGHT      128
#endif
#ifndef TFT_WIDTH
#define TFT_WIDTH       160
#endif
#define TFT_HEIGHT_TOP_MARGIN 119
#define GRIDCOLOR ST7735_WHITE
#define BGCOLOR ST7735_BLACK
#define CH1COLOR ST7735_GREEN


	Plotter :: Plotter()
	{
		tft = TFT_ST7735();
	}
//
	void Plotter :: begin(int range)
	{
		setRange(range);
		tft.init(INITR_GREENTAB);
		tft.setRotation(1);
		tft.fillScreen(BGCOLOR);
		for(int j=0;j<tft.width();j++)
		DrawGrid(i);
		i=0;
	}

	void Plotter :: DrawGrid(int x)
	{
		if ((x % 2) == 0)
		  for (int y=TOP_MARGIN; y<=TFT_HEIGHT; y += DOTS_DIV)
			tft.drawPixel(x, y, GRIDCOLOR);
		if ((x % DOTS_DIV) == 0)
		  for (int y=TOP_MARGIN; y<=TFT_HEIGHT; y += 2)
			tft.drawPixel(x, y, GRIDCOLOR);
	}
	
	void Plotter :: ClearAndDrawDot(int i)
	{
		tft.drawLine(i-1, -59+TFT_HEIGHT-values[1][i-1], i, -59+TFT_HEIGHT-values[1][i], BGCOLOR);
		tft.drawLine(i-1, -59+TFT_HEIGHT-values[0][i-1], i, -59+TFT_HEIGHT-values[0][i], CH1COLOR);
    
		DrawGrid(i);
	}
	
	void Plotter :: draw(int value)
	{
		value=value/factor;
		values[1][i]=values[0][i];
		values[0][i]=value;
		ClearAndDrawDot(i);
	  
		i++;
		if(i>=SAMPLES)
		i=0;
	}
	
	void Plotter :: setRange(int range)
	{
		factor=range/60;
	}
