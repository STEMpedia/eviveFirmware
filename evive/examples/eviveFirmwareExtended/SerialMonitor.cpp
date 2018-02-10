/*Serial Monitor library reads data from the selected serial ports in menu and displays on TFT screen.
	Menu gives the user a choice to select the baud rate and displays it on the TFT. It can read from multiple
	serial ports simultaneously. In the function tft_implementation_serial_monitor [in screenImplementation.h],
	serial ports are checked for any new/available data while the class object serialObject takes care of printing the
	data on screen corresponding to the selected serial port(s).
	
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

 * Written by Bhanu & Sandeep
 * Tested with evive v1
 * Date: Jan 2017
 * Updated by Dhrupal on Aug 2, 2017
 
  How to use this library:
  A well explained tutorial can be found at:
	https://evive.cc/evive-documentation/menu-interface/serial-monitor/
*/

#include "SerialMonitor.h"

SerialMonitor::SerialMonitor() {
}

void SerialMonitor::Initalise(long baudRateSelect, uint8_t serialNum) {
	tft.setCursor(15, TOP_MARGIN);
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.print(F("Serial Monitor  "));
	serialObject.lineNumCurrent =3;
	tft.print(baudRateSelect);
	switch (serialNum) {
		case 0:
			Serial.begin(baudRateSelect);
			Serial.setTimeout(SERIAL_TIME_OUT);
			break;
		case 1:
			Serial2.begin(baudRateSelect);
			Serial2.setTimeout(SERIAL_TIME_OUT);
			break;
		case 2:
			Serial3.begin(baudRateSelect);
			Serial3.setTimeout(SERIAL_TIME_OUT);
			break;
		default:
			break;
	}
}

void SerialMonitor::serial0PrintMsg() {
	if (Serial.available() > 0) {
		msg = Serial.readString();
		linesMsg = linesCount(msg.length());
		if (lineNumCurrent + linesMsg > 16) {
			tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * (16-lineNumCurrent) + CHAR_HEIGHT, ST7735_BLACK);
			tft.fillRect(0, 3 * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
			tft.setCursor(0, CHAR_HEIGHT * 3);
			tft.print(F("> "));
			tft.print(msg);
			lineNumCurrent = 3;
		}
		tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
		tft.setTextColor(ST7735_WHITE);
		tft.setCursor(0, CHAR_HEIGHT * lineNumCurrent);
		tft.print(F("> "));
		tft.print(msg);
		lineNumCurrent = lineNumCurrent + linesMsg;
		msg = "";
	}
}

void SerialMonitor::serial2PrintMsg() {
	if (Serial2.available() > 0) {
		msg2 = Serial2.readString();
		linesMsg = linesCount(msg2.length());
		if (lineNumCurrent + linesMsg > 16) {
			tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * (16-lineNumCurrent) + CHAR_HEIGHT, ST7735_BLACK);	
			tft.fillRect(0, 3 * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
			tft.setCursor(0, CHAR_HEIGHT * 3);
			tft.print(F("> "));
			tft.print(msg2);
			lineNumCurrent = 3;
		}
		tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
		tft.setTextColor(ST7735_MAGENTA);
		tft.setCursor(0, CHAR_HEIGHT * lineNumCurrent);
		tft.print(F("> "));
		tft.print(msg2);
		lineNumCurrent = lineNumCurrent + linesMsg;
		msg2 = "";
	}
}

void SerialMonitor::serial3PrintMsg() {
	if (Serial3.available() > 0) {
		msg3 = Serial3.readString();
		linesMsg = linesCount(msg3.length());
		if (lineNumCurrent + linesMsg > 16) {
			tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * (16-lineNumCurrent) + CHAR_HEIGHT, ST7735_BLACK);
			tft.fillRect(0, 3 * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
			tft.setCursor(0, CHAR_HEIGHT * 3);
			tft.print(F("> "));
			tft.print(msg3);
			lineNumCurrent = 3;
		}
		tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
		tft.setCursor(0, CHAR_HEIGHT * lineNumCurrent);
		tft.print(F("> "));
		tft.print(msg3);
		lineNumCurrent = lineNumCurrent + linesMsg;
		msg3 = "";
	}
}

uint8_t SerialMonitor::linesCount(int lengthMsg) {
	if(lengthMsg>=390) return 16;
	return (uint8_t(1+lengthMsg/25));
}

SerialMonitor serialObject;
