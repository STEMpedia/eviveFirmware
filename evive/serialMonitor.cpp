#include "serialMonitor.h"

SerialMonitor::SerialMonitor() {
}

void SerialMonitor::Initalise(long baudRateSelect, uint8_t serialNum) {
	tft.setCursor(15, TOP_MARGIN);
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.print("Serial Monitor  ");
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
			tft.print("> ");
			tft.print(msg);
			lineNumCurrent = 3;
		}
		tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
		tft.setTextColor(ST7735_WHITE);
		tft.setCursor(0, CHAR_HEIGHT * lineNumCurrent);
		tft.print("> ");
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
			tft.print("> ");
			tft.print(msg2);
			lineNumCurrent = 3;
		}
		tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
		tft.setTextColor(ST7735_MAGENTA);
		tft.setCursor(0, CHAR_HEIGHT * lineNumCurrent);
		tft.print("> ");
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
			tft.print("> ");
			tft.print(msg3);
			lineNumCurrent = 3;
		}
		tft.fillRect(0, lineNumCurrent * CHAR_HEIGHT, TFT_WIDTH, CHAR_HEIGHT * linesMsg + CHAR_HEIGHT, ST7735_BLACK);
		tft.setCursor(0, CHAR_HEIGHT * lineNumCurrent);
		tft.print("> ");
		tft.print(msg3);
		lineNumCurrent = lineNumCurrent + linesMsg;
		msg3 = "";
	}
}

uint8_t SerialMonitor::linesCount(int lengthMsg) {
	if(lengthMsg>=390) return 16;
	return (uint8_t(1+lengthMsg/25));
	
	// if (lineNumCurrent == 0 || lineNumCurrent < 25)
		// return 1;
	// else if (lineNumCurrent == 25 || lineNumCurrent < 51)
		// return 2;
	// else if (lineNumCurrent == 51 || lineNumCurrent < 77)
		// return 3;
	// else if (lineNumCurrent == 77 || lineNumCurrent < 103)
		// return 4;
	// else if (lineNumCurrent == 103 || lineNumCurrent < 129)
		// return 5;
	// else if (lineNumCurrent == 129 || lineNumCurrent < 155)
		// return 6;
	// else if (lineNumCurrent == 155 || lineNumCurrent < 181)
		// return 7;
	// else if (lineNumCurrent == 181 || lineNumCurrent < 207)
		// return 8;
	// else if (lineNumCurrent == 207 || lineNumCurrent < 233)
		// return 9;
	// else if (lineNumCurrent == 233 || lineNumCurrent < 259)
		// return 10;
	// else if (lineNumCurrent == 259 || lineNumCurrent < 285)
		// return 11;
	// else if (lineNumCurrent == 285 || lineNumCurrent < 311)
		// return 12;
	// else if (lineNumCurrent == 311 || lineNumCurrent < 337)
		// return 13;
	// else if (lineNumCurrent == 337 || lineNumCurrent < 363)
		// return 14;
	// else if (lineNumCurrent == 363 || lineNumCurrent < 390)
		// return 15;
	// else
		// return 16;
}

SerialMonitor serialObject;
