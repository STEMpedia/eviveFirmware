/**************************************************************************/
/*! 
    @file     Adafruit_MCP4725.h
    @author   K. Townsend (Adafruit Industries)
	@license  BSD (see license.txt)
	
	This is a library for the Adafruit MCP4725 breakout board
	----> http://www.adafruit.com/products/935
	
	Adafruit invests time and resources providing this open source code, 
	please support Adafruit and open-source hardware by purchasing 
	products from Adafruit!

	@section  HISTORY

    v1.0  - First release
	Edited by: Dhrupal R Shah
	http://evive.cc
	Date: 2016/08/01	
*/
/**************************************************************************/
#ifndef DAC_MCP4725_H
#define DAC_MCP4725_H
//#ifndef MCP4725_ADDR
#define MCP4725_ADDR 0x62
//#endif

#include "evive.h"

#define MCP4726_CMD_WRITEDAC            (0x40)  // Writes data to the DAC
#define MCP4726_CMD_WRITEDACEEPROM      (0x60)  // Writes data to the DAC and the EEPROM (persisting the assigned value after reset)

class dac_MCP4725{
 public:
  dac_MCP4725();
  void begin(uint8_t a);  
  void setVoltage( uint16_t output, bool writeEEPROM );

 private:
  uint8_t _i2caddr;
};

////////////////Modified Library////////////////
extern dac_MCP4725 dac;

extern uint16_t increment, oldIncrement;
extern float amplitude, oldAmplitude;

void setFrequencyAmplitude();
void generateSineWave();
void generateSquareWave();
void generateTraingularWave();
void generateSawtoothWaveUp();
void generateSawtoothWaveDown();
void generateAnalogOutput();

#endif
