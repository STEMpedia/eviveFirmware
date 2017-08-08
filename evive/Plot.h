#ifndef PLOT_H
#define PLOT_H
//#include <arduino.h>

//#include "TFT_ST7735.h"
//#include <Adafruit_GFX.h>    // Core graphics library
//#include <Adafruit_ST7735.h>

//#include <SPI.h>
#include "evive.h"
//#include "screenImplementation.h"

/*

*/




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