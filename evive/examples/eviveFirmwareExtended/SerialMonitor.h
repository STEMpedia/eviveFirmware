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

#ifndef SERIAL_MONITOR_H
#define SERIAL_MONITOR_H

#include "evive.h"

class SerialMonitor {
	public:
		SerialMonitor();
		void serial0PrintMsg();
		void serial2PrintMsg();
		void serial3PrintMsg();
		void Initalise(long, uint8_t);
		String msg = "";
		String msg2 = "";
		String msg3 = "";
		uint8_t linesMsg = 1, lineNumCurrent = 3;
		uint8_t linesCount(int);
};

extern SerialMonitor serialObject;

#endif
