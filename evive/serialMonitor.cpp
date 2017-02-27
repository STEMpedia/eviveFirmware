/* Written by Bhanu & Sandeep
 It reads data form the serial and prints on tft screen.
 It also gives the user choice to select the baud rate and print on tft screen.
 Initalise sets the baud rate according to choice of user
 There are various types of print messages whicht takes data from the serial and prints on tft.
 lcd_implementation_serial_monitor decides which selects which serial print message is run in loop
 Serialprint runs lcd_implementation_serial_monitor in loop
 */
#include "serialMonitor.h"

SerialMonitor::SerialMonitor() {
}

void SerialMonitor::Initalise(long baudRateSelect, uint8_t serialNum) {
	lcd.setCursor(15, TOP_MARGIN);
	lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	lcd.print("Serial Monitor  ");
	serialObject.ln =3;
	lcd.print(baudRateSelect);
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
		l = lnCount(msg.length());
		if (ln + l > 16) {
			lcd.fillRect(0, 3 * CHAR_HEIGHT, LCD_WIDTH, CHAR_HEIGHT * l + CHAR_HEIGHT, ST7735_BLACK);
			lcd.setCursor(0, CHAR_HEIGHT * 3);
			lcd.print("> ");
			lcd.print(msg);
			ln = 3;
		}
		lcd.fillRect(0, ln * CHAR_HEIGHT, LCD_WIDTH, CHAR_HEIGHT * l + CHAR_HEIGHT, ST7735_BLACK);
		lcd.setTextColor(ST7735_WHITE);
		lcd.setCursor(0, CHAR_HEIGHT * ln);
		lcd.print("> ");
		lcd.print(msg);
		ln = ln + l;
		msg = "";
	}
}

void SerialMonitor::serial2PrintMsg() {
	if (Serial2.available() > 0) {
		msg2 = Serial2.readString();
		l = lnCount(msg2.length());
		if (ln + l > 16) {
			lcd.fillRect(0, 3 * CHAR_HEIGHT, LCD_WIDTH, CHAR_HEIGHT * l + CHAR_HEIGHT, ST7735_BLACK);
			lcd.setCursor(0, CHAR_HEIGHT * 3);
			lcd.print("> ");
			lcd.print(msg2);
			ln = 3;
		}
		lcd.fillRect(0, ln * CHAR_HEIGHT, LCD_WIDTH, CHAR_HEIGHT * l + CHAR_HEIGHT, ST7735_BLACK);
		lcd.setTextColor(ST7735_MAGENTA);
		lcd.setCursor(0, CHAR_HEIGHT * ln);
		lcd.print("> ");
		lcd.print(msg2);
		ln = ln + l;
		msg2 = "";
	}
}

void SerialMonitor::serial3PrintMsg() {
	if (Serial3.available() > 0) {
		msg3 = Serial3.readString();
		l = lnCount(msg3.length());
		if (ln + l > 16) {
			lcd.fillRect(0, 3 * CHAR_HEIGHT, LCD_WIDTH, CHAR_HEIGHT * l + CHAR_HEIGHT, ST7735_BLACK);
			lcd.setCursor(0, CHAR_HEIGHT * 3);
			lcd.print("> ");
			lcd.print(msg3);
			ln = 3;
		}
		lcd.fillRect(0, ln * CHAR_HEIGHT, LCD_WIDTH, CHAR_HEIGHT * l + CHAR_HEIGHT, ST7735_BLACK);
		lcd.setCursor(0, CHAR_HEIGHT * ln);
		lcd.print("> ");
		lcd.print(msg3);
		ln = ln + l;
		msg3 = "";
	}
}

int SerialMonitor::lnCount(int ln) {
	if (ln == 0 || ln < 25)
		return 1;
	else if (ln == 25 || ln < 51)
		return 2;
	else if (ln == 51 || ln < 77)
		return 3;
	else if (ln == 77 || ln < 103)
		return 4;
	else if (ln == 103 || ln < 129)
		return 5;
	else if (ln == 129 || ln < 155)
		return 6;
	else if (ln == 155 || ln < 181)
		return 7;
	else if (ln == 181 || ln < 207)
		return 8;
	else if (ln == 207 || ln < 233)
		return 9;
	else if (ln == 233 || ln < 259)
		return 10;
	else if (ln == 259 || ln < 285)
		return 11;
	else if (ln == 285 || ln < 311)
		return 12;
	else if (ln == 311 || ln < 337)
		return 13;
	else if (ln == 337 || ln < 363)
		return 14;
	else if (ln == 363 || ln < 390)
		return 15;
	else
		return 16;
}

// Linear interpolation
/* void SerialMonitor::serialSetup(){
 int i = serialSelect();
 if(i == 0) Serial.begin(baudSelect());
 else if(i == 1) serialObject.begin(baudSelect());
 else if (i == 2) Serial2.begin(baudSelect());
 else Serial3.begin(baudSelect());

 } */
SerialMonitor serialObject;
