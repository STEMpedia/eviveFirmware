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
		int b = 14;
		int l = 1, ln = 3;
		int lnCount(int ln);
};

extern SerialMonitor serialObject;

#endif
