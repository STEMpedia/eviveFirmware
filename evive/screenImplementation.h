#ifndef SCREEN_IMPLEMENTATION_H
#define SCREEN_IMPLEMENTATION_H

#include "evive.h"

#ifndef ROW_HEIGHT
#define ROW_HEIGHT      10
#endif
#ifndef CHAR_HEIGHT
#define CHAR_HEIGHT     8
#endif
#ifndef CHAR_WIDTH
#define CHAR_WIDTH      6
#endif
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
#ifndef LCD_HEIGHT
#define LCD_HEIGHT      128
#endif
#ifndef LCD_WIDTH
#define LCD_WIDTH       160
#endif
#ifndef LCD_WIDTH_BY_2
#define LCD_WIDTH_BY_2  80
#endif
//#define LCD_STR_UPLEVEL 	'^'
#define LCD_STR_ARROW_RIGHT ">"
#define LCD_STR_UPLEVEL     "\x03"
#define BATT_X							140
#define BATT_Y							4
#define BATT_WIDTH					17
#define BATT_HEIGHT					7
#define BATT_COLOR					ST7735_CYAN
#define VVR_MULTIPLIER			0.03021
uint16_t pre_vvr = 0, vvr = 0;

static void drawBattery();
void batteryUpdate();
void vvrUpdate();
static void printVvr();
static void drawStatusBar();
//Actual implementation of the LCD display routines
Adafruit_ST7735 lcd = Adafruit_ST7735(LCD_CS, LCD_DC, LCD_RST);
extern int8_t encoderPosition;

static void lcd_implementation_init() {
	//lcd.initR();
	lcd.initR(SCREEN_TAB);
	lcd.setRotation(1);
	lcd.setTextWrap(true);
	lcd.fillScreen(ST7735_BLACK);
	lcd.drawBitmap(45, 29, evive_logo, 71, 71, ST7735_BLUE);
	delay(MIN_TIME5);	//DELAY HERE. DO NOT CALL THIS MORE THAN ONCE EVER EVER EVER
	lcd.fillScreen(ST7735_BLACK);
	lcd.setTextSize(1);
	drawStatusBar();
}

static void drawBattery() {
	lcd.drawFastHLine(BATT_X, BATT_Y, BATT_WIDTH - 2, BATT_COLOR);
	lcd.drawFastVLine(BATT_X + BATT_WIDTH - 2, BATT_Y, BATT_HEIGHT + 1,	BATT_COLOR);
	lcd.drawFastVLine(BATT_X + BATT_WIDTH - 1, BATT_Y + 2, 4, ST7735_WHITE);
	lcd.drawFastVLine(BATT_X + BATT_WIDTH, BATT_Y + 2, 4, ST7735_WHITE);
	lcd.drawFastHLine(BATT_X, BATT_Y + BATT_HEIGHT, BATT_WIDTH - 2, BATT_COLOR);
	lcd.drawFastVLine(BATT_X, BATT_Y, BATT_HEIGHT, BATT_COLOR);
}

void batteryUpdate() {
	int batt = analogRead(BATSUPPLYLEVEL);
	int widthMeter = 0;
	if (batt < 630)
		widthMeter = 0;
	else if (batt < 682)
		widthMeter = 5;
	else if (batt < 752)
		widthMeter = 10;
	else
		widthMeter = BATT_WIDTH - 3;
	lcd.fillRect(BATT_X + 1, BATT_Y + 1, widthMeter, BATT_HEIGHT - 1, BATT_COLOR);
}

static void drawStatusBar() {
	lcd.setTextColor(ST7735_CYAN);
	lcd.setCursor(0, 3);
	lcd.print("evive");
	drawBattery();
	batteryUpdate();
	printVvr();
	vvrUpdate();
}

//static void statusBarUpdate(){
//}

static void printVvr() {
	lcd.setCursor(70, 3);
	lcd.print("VVR: ");
}
void vvrUpdate() {
	vvr = analogRead(VARSUPPLYLEVEL);
	if (pre_vvr - vvr > 4 || pre_vvr - vvr < -4) {
		lcd.setTextColor(ST7735_RED);
		lcd.setCursor(70 + 24, 3);
		lcd.fillRect(70 + 24, 3, 35, 7, ST7735_BLACK);
		lcd.print(vvr * VVR_MULTIPLIER);
		pre_vvr = vvr;
	}
}

static void lcd_implementation_drawmenu_generic(uint8_t row, const char* pstr,
    char pre_char, char post_char) {
	char c;
	uint8_t n = LCD_WIDTH / CHAR_WIDTH;
	lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + (row) * ROW_HEIGHT);
	lcd.print(pre_char);
	while (((c = pgm_read_byte(pstr)) != '\0') && (n > 0)) {
		lcd.print(c);
		pstr++;
		n--;
	}
	lcd.fillRect(2 + LEFT_MARGIN + LCD_WIDTH - n * CHAR_WIDTH,
	TOP_MARGIN + ROW_HEIGHT * row, LCD_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1,
	ROW_HEIGHT, ST7735_BLACK);
	lcd.setCursor(LCD_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1,
	TOP_MARGIN + (row) * ROW_HEIGHT);
	lcd.print(post_char);
}

static void lcd_implementation_drawmenu_setting_edit_generic(uint8_t row,
    const char* pstr, char pre_char, char data) {
	lcd.setCursor(TOP_MARGIN + (row) * ROW_HEIGHT, LEFT_MARGIN);
	lcd.print(pre_char);
	lcd.print("  ");
	lcd.print(pstr);
	lcd.setCursor((row - 1) * ROW_HEIGHT,
	LCD_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1);
	lcd.print(data);
}

#define lcd_implementation_drawmenu_setting_edit_int3_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_int3(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float3_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float3(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float32_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float32(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float5_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float5(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float52_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float52(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float51_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_float51(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define lcd_implementation_drawmenu_setting_edit_long5_selected(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_long5(row, pstr, pstr2, data, minValue, maxValue) lcd_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define lcd_implementation_drawmenu_setting_edit_bool_selected(row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
#define lcd_implementation_drawmenu_setting_edit_bool(row, pstr, pstr2, data) lcd_implementation_drawmenu_setting_edit_generic_P(row, pstr, ' ', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))

void lcd_implementation_drawedit(const char* pstr, char* value) {
	lcd.setCursor(TOP_MARGIN, LEFT_MARGIN);
	lcd.print(pstr);
	lcd.print(':');
	lcd.setCursor(TOP_MARGIN, LCD_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1);
	lcd.print(value);
}
#define lcd_implementation_drawmenu_back_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, LCD_STR_UPLEVEL[0], LCD_STR_UPLEVEL[0])
#define lcd_implementation_drawmenu_back(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', LCD_STR_UPLEVEL[0])
#define lcd_implementation_drawmenu_submenu_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, '>', char(175));
#define lcd_implementation_drawmenu_submenu(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', char(175));//LCD_STR_ARROW_RIGHT[0])
#define lcd_implementation_drawmenu_function_selected(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, '>', ' ')
#define lcd_implementation_drawmenu_function(row, pstr, data) lcd_implementation_drawmenu_generic(row, pstr, ' ', ' ')

void lcd_implementation_clear_full() {
	lcd.fillScreen(ST7735_BLACK);
}

void lcd_implementation_clear_menu() {
	lcd.fillRect(0, TOP_MARGIN, LCD_WIDTH,
	LCD_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN, ST7735_BLACK);
}

void lcd_implementation_text_and_background_color(uint16_t text_clr,
    uint16_t text_background_clr) {
	lcd.setTextColor(text_clr, text_background_clr);
}

//control status functions

void lcd_implementation_control_status_motor(bool sec) {
	lcd.setTextColor(ST7735_RED, ST7735_BLACK);
	if (sec) {
		//lcd.fillRect(LCD_WIDTH_BY_2+45,TOP_MARGIN+ROW_HEIGHT*3, 39, ROW_HEIGHT*4, ST7735_BLACK);
		lcd.setCursor(LCD_WIDTH_BY_2 + 45, TOP_MARGIN + ROW_HEIGHT * 3);
		lcd.print(motor2.getPWM());
		lcd.print("  ");
		lcd.setCursor(LCD_WIDTH_BY_2 + 45, TOP_MARGIN + ROW_HEIGHT * 5);
		lcd.print(motor2.dir1);
		lcd.setCursor(LCD_WIDTH_BY_2 + 45, TOP_MARGIN + ROW_HEIGHT * 6);
		lcd.print(motor2.dir2);
	} else {
		//lcd.fillRect(45,TOP_MARGIN+ROW_HEIGHT*3, 39, ROW_HEIGHT*4, ST7735_BLACK);
		lcd.setCursor(45, TOP_MARGIN + ROW_HEIGHT * 3);
		lcd.print(motor1.getPWM());
		lcd.print("  ");
		lcd.setCursor(45, TOP_MARGIN + ROW_HEIGHT * 5);
		lcd.print(motor1.dir1);
		lcd.setCursor(45, TOP_MARGIN + ROW_HEIGHT * 6);
		lcd.print(motor1.dir2);
	}
}

unsigned long lastServoImplement = 0;

void lcd_implementation_control_status_servo(bool sec) {
	lcd.setTextColor(ST7735_RED, ST7735_BLACK);

	if (sec
	    && prevValueServo2()
	        != servo2.read() && (millis()-lastServoImplement)> MIN_TIME1) {
		//lcd.drawLine(LCD_WIDTH_BY_2+40,105,LCD_WIDTH_BY_2+40+20*sin((-prevValueServo2()-90)*3.14/180),75+20*cos((-prevValueServo2()-90)*3.14/180),ST7735_BLACK);
		//lcd.drawLine(LCD_WIDTH_BY_2+40,105,LCD_WIDTH_BY_2+40+20*sin((-servo2.read()-90)*3.14/180),75+20*cos((-servo2.read()-90)*3.14/180),ST7735_GREEN);
		lcd.setCursor(LCD_WIDTH_BY_2 + 50, TOP_MARGIN + ROW_HEIGHT * 3);
		lcd.print(servo2.read());
		lcd.print("  ");
		//Serial.println("went in 2");
		lastServoImplement = millis();
	}
	if (~sec
	    && prevValueServo1()
	        != servo1.read() && (millis()-lastServoImplement)> MIN_TIME1) {
		//lcd.drawLine(40,105,40+20*sin((-prevValueServo1()-90)*3.14/180),75+20*cos((-prevValueServo1()-90)*3.14/180),ST7735_BLACK);
		//lcd.drawLine(40,105,40+20*sin((-servo1.read()-90)*3.14/180),75+20*cos((-servo1.read()-90)*3.14/180),ST7735_GREEN);
		lcd.setCursor(50, TOP_MARGIN + ROW_HEIGHT * 3);
		lcd.print(servo1.read());
		lcd.print("  ");
		//Serial.println("went in 1");
		lastServoImplement = millis();
	}
}

/*****variables for motor function*****/
bool stps;
bool dir1;
bool dir2;

void lcd_implementation_control_status_stepper() {
	if (stps != digitalRead(TACTILESW1) || dir1 != digitalRead(SLIDESW1_D2)
	    || dir2 != digitalRead(SLIDESW1_D1))//change the screen only if a variable is changed
	        {
		lcd.setTextColor(ST7735_RED, ST7735_BLACK);
		lcd.setCursor(50, TOP_MARGIN + ROW_HEIGHT * 7);
		lcd.print("\n Stepper Direction : ");
		dir1 = digitalRead(SLIDESW1_D2);
		dir2 = digitalRead(SLIDESW1_D1);
		if (dir1) {
			lcd.print("Dir 1");
		} else if (dir2)
			lcd.print("Dir 2");
		else
			lcd.print("0   ");
		lcd.print("\n Speed :");
		stps = digitalRead(TACTILESW1);
		if (stps) {
			lcd.print("10x");
		} else
			lcd.print("x  ");
	}
}

void lcd_control_status_template() {
	lcd.setTextColor(ST7735_RED);
	lcd_implementation_clear_menu();
	if (_MOTOR1_EN) {
		lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
		lcd.println("   Motor 1");
		lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
		lcd.println(" PWM:");
		lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 4);
		lcd.println(" States:");
		lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 5);
		lcd.println("  Dir1:");
		lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 6);
		lcd.print("  Dir2:");
	} else {
		if (_SERVO1_EN) {
			lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
			lcd.println("   Servo 1");
			//lcd.drawBitmap(15, 50, semiCircle, 80, 25, ST7735_YELLOW);
			lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
			lcd.println("  Angle:");
		}
	}
	if (_MOTOR2_EN) {
		lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
		lcd.println("   Motor 2");
		lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
		lcd.println(" PWM:");
		lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 4);
		lcd.println(" States:");
		lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 5);
		lcd.print("  Dir1:");
		lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 6);
		lcd.print("  Dir2:");
	} else {
		if (_SERVO2_EN) {
			lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
			lcd.println("   Servo 2");
			//lcd.drawBitmap(LCD_WIDTH_BY_2+15, 80, semiCircle, 50, 25, ST7735_YELLOW);
			lcd.setCursor(LCD_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
			lcd.println("  Angle:");
		}
	}
}

void lcd_sensing_status_template(bool probeVIConfig) {
	ade791x_init();
	lcd.setTextColor(ST7735_RED);
	lcd_implementation_clear_menu();
	lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
	lcd.println("   Probe V");
	lcd.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
	lcd.println("   V");
	lcd.setCursor(LCD_WIDTH_BY_2, TOP_MARGIN + ROW_HEIGHT * 1);
	lcd.println("  Probe I/V");
	lcd.setCursor(LCD_WIDTH_BY_2, TOP_MARGIN + ROW_HEIGHT * 3);
	if (probeVIConfig)
		lcd.print("  A");
	else
		lcd.print("  V");
}

void lcd_implementation_sensing_status(bool probeVIConfig) {
	//Add code here
	lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	lcd.setCursor(LEFT_MARGIN + 19, TOP_MARGIN + ROW_HEIGHT * 2);
	lcd.print(ade791x_read_v1() / 1000.0, 2);
	lcd.print("    ");
	lcd.setCursor(LCD_WIDTH_BY_2 + 12, TOP_MARGIN + ROW_HEIGHT * 2);

	if (probeVIConfig)
		lcd.print(ade791x_read_im() / 1000.0, 2);
	else
		lcd.print(ade791x_read_vim() / 1000.0, 2);
	lcd.print("    ");

	// long V1 = ade791x_read_v1()/1000.0;
	// if(V1<0)	lcd.setCursor(LEFT_MARGIN-CHAR_WIDTH+19, TOP_MARGIN+ROW_HEIGHT*2);
	// else lcd.setCursor(LEFT_MARGIN+19, TOP_MARGIN+ROW_HEIGHT*2);
	// lcd.print(V1,2);
	// lcd.print("    ");

	// if(probeVIConfig){
	// long IM = ade791x_read_im()/1000.0;
	// if(V1<0)	lcd.setCursor(LCD_WIDTH_BY_2+12-CHAR_WIDTH, TOP_MARGIN+ROW_HEIGHT*2);
	// else lcd.setCursor(LCD_WIDTH_BY_2+12, TOP_MARGIN+ROW_HEIGHT*2);
	// lcd.print(IM,2);
	// }

	// else {
	// long VIM = ade791x_read_vim()/1000.0;
	// if(VIM<0)	lcd.setCursor(LCD_WIDTH_BY_2+12-CHAR_WIDTH, TOP_MARGIN+ROW_HEIGHT*2);
	// else lcd.setCursor(LCD_WIDTH_BY_2+12, TOP_MARGIN+ROW_HEIGHT*2);
	// lcd.print(VIM,2);
	// }
	// lcd.print("    ");
}

//-------------mini oscilloscope/start--------------//
#define txtLINE0   0
#define txtLINE1   40
#define txtLINE2   80
#define txtLINE3   120

const int SAMPLES = 160;
const int DOTS_DIV = 20;
//range0, range1, rate, TRIG_Modes, TRIG_E_DN/UP ch0_off, ch1_off, trig_lv, Send, log
const int MENU_TOTAL_ITEMS = 10;

#define GRAPH_TOP_MARGIN			9
#define GRAPH_LEFT_MARGIN			0
#define LCD_HEIGHT_TOP_MARGIN 119
#define LCD_GRAPH_MID					69
#define LCD_GRPAH_MID_TOP_MARGIN 60

//const int ad_sw = A11;                    // Analog 3 pin for switches
//const int ad_ch0 = A5;                   // Analog 4 pin for channel 0
//const int ad_ch1 = A10;                   // Analog 5 pin for channel 1
const int ad_ch0 = 0;                   		//ADE_CH_V1WV
const int ad_ch1 = 1;                   	//ADE_CH_IWV
const unsigned long VREF[] = { 10, 20, 50, 100, 200, 500, 1000, 2000, 5000 }; // reference voltage 5.0V ->  100 :   1V/div range (100mV/dot)
// It means 5.0 * DOTS_DIV = 100 : 1V/div   (Use 4.9 if reference voltage is 4.9[V])
//                        -> 200 : 0.5V/div
//                        -> 750 : 0.2V/div
//                        ->1500 : 100mV/div
//                       -> 3000 :  50mV/div
const float MILLIVOL_per_dot[] = { 500, 250, 100, 50, 25, 10, 5, 2.5, 1, 0, 1,
    2.5, 5, 10, 25, 50 }; // mV/dot
const int MODE_ON = 0;
const int MODE_INV = 1;
const int MODE_OFF = 2;
const char *Modes[] = { "NORM", "INV", "OFF" };

const int TRIG_AUTO = 0;
const int TRIG_NORM = 1;
const int TRIG_SCAN = 2;
const int TRIG_ONE = 3;
const char *TRIG_Modes[] = { "Auto", "Norm", "Scan", "One" };
const int TRIG_E_UP = 0;
const int TRIG_E_DN = 1;

#define RATE_MIN 0
#define RATE_MAX 13
///////////////////////0 (single)/1///////2///////3///////4///////5///////6////////7//////8//////9///////10////11////12////13
//const char *Rates[] = {"F1-1", "F1-2 ", "F2  ", "5ms", "10ms", "20ms", "50ms", "0.1s", "0.2s", "0.5s", "1s", "2s", "5s", "10s"};
const char *Rates[] = { "1-2.5", "2-2.5", "F2  ", "5ms", "10ms", "20ms", "50ms",
    "0.1s", "0.2s", "0.5s", "1s", "2s", "5s", "10s" };

#define RANGE_MIN 0
#define RANGE_MAX_CH0 9
#define RANGE_MAX_CH1 15
const char *Ranges[] = { " 10V/D", "  5V/D", "  2V/D", "  1V/D", "0.5V/D",
    "0.2V/D", "0.1V/D", "50mV/D", "20mV/D", " OFF", "20mA/D", "50mA/D",
    "0.1A/D", "0.2A/D", "0.5A/D", "1A/D" };

unsigned long startMillis;
int data[4][SAMPLES]; // keep twice of the number of channels to make it a double buffer
byte sample = 0;                           // index for double buffer

///////////////////////////////////////////////////////////////////////////////////////////////

// Define colors here
#define	BGCOLOR   0x0000
#define GRIDCOLOR 0xFFFF
#define CH1COLOR  ST7735_GREEN
#define CH2COLOR  0xFFE0

// Declare variables and set defaults here
byte range0 = RANGE_MIN + 2, ch0_mode = MODE_ON;  // CH0
short ch0_off = 0; //614+15;                 //offset
byte range1 = RANGE_MIN + 2, ch1_mode = MODE_ON;  // CH1
short ch1_off = 0; //614+15;                 //offset
byte rate = 7;                                // sampling rate
byte trig_mode = TRIG_AUTO, trig_lv = 50, trig_edge = TRIG_E_UP, trig_ch = 1; // trigger settings

byte Start = 1;  // Start sampling
byte menu = 1;  // Default menu
///////////////////////////////////////////////////////////////////////////////////////////////

static void CheckSW();
static void menuUpdate();
static void SendData();
static void DrawGrid();
static void DrawText();
static void PrintMenuItem();
static void DrawGrid(int);
static void PrintMenuItem(int);
static void ClearAndDrawGraph();
static void ClearAndDrawDot(int);
static void DrawGraph();
static void ClearGraph();
static void evive_oscilloscope_loop();
void evive_oscilloscope();

static void CheckSW() {
	navKeyUpdate();
	if (menuMove == 0)
		return;
	else if (menuMove == 2) {
		if (menu + 1 > MENU_TOTAL_ITEMS)
			menu = 1;
		else
			menu++;
		DrawText();
	} else if (menuMove == 4) {
		if (menu < 2)
			menu = MENU_TOTAL_ITEMS;
		else
			menu--;
		DrawText();
	} else if (menuMove == 3 || menuMove == 1) {
		menuUpdate();
		DrawText();
	}
}

static void menuUpdate() {
	switch (menu) {
		case 1:
			if (menuMove == 3) {
				// CH0 RANGE +
				ch0_mode = MODE_ON;
				if (range0 > 0)
					range0--;
			} else {
				// CH0 RANGE -
				if (range0 < RANGE_MAX_CH0)
					range0++;
				if (range0 == RANGE_MAX_CH0) {
					ch0_mode = MODE_OFF;
					lcd.fillRect(0, GRAPH_LEFT_MARGIN, LCD_WIDTH, LCD_HEIGHT_TOP_MARGIN,
					BGCOLOR);
					//DrawGrid;
				}
			}
			break;
		case 2:
			if (menuMove == 3) {
				// CH1 RANGE +
				ch1_mode = MODE_ON;
				if (range1 > 0)
					range1--;
			} else {
				// CH1 RANGE -
				if (range1 < RANGE_MAX_CH1)
					range1++;
				if (range1 == RANGE_MAX_CH1) {
					ch1_mode = MODE_OFF;
					lcd.fillRect(0, GRAPH_LEFT_MARGIN, LCD_WIDTH, LCD_HEIGHT_TOP_MARGIN,
					BGCOLOR);
				}
			}
			break;
		case 3:
			if (menuMove == 3) {
				// RATE SLOW
				if (rate < RATE_MAX)
					rate++;
			} else {
				// RATE FAST
				if (rate > 0)
					rate--;
			}
			break;
		case 4:
			if (menuMove == 3) {  // TRIG MODE
				if (trig_mode > TRIG_AUTO)
					trig_mode--;
			} else {
				if (trig_mode < TRIG_ONE)
					trig_mode++;
			}
			break;
		case 5:
			if (trig_edge == TRIG_E_DN)
				trig_edge = TRIG_E_UP;
			else
				trig_edge = TRIG_E_DN;
			break;
		case 6:
			if (menuMove == 3) {
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch0_off - 3);
				lcd.setTextColor(BGCOLOR);
				lcd.print(char(174));
				ch0_off--;
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch0_off - 3);
				lcd.setTextColor(CH1COLOR);
				lcd.print(char(174));
			} else {
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch0_off - 3);
				lcd.setTextColor(BGCOLOR);
				lcd.print(char(174));
				ch0_off++;
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch0_off - 3);
				lcd.setTextColor(CH1COLOR);
				lcd.print(char(174));

			}
			break;
		case 7:
			if (menuMove == 3) {
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch1_off - 3);
				lcd.setTextColor(BGCOLOR);
				lcd.print(char(174));
				ch1_off--;
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch1_off - 3);
				lcd.setTextColor(CH2COLOR);
				lcd.print(char(174));
			} else {
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch1_off - 3);
				lcd.setTextColor(BGCOLOR);
				lcd.print(char(174));
				ch1_off++;
				lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch1_off - 3);
				lcd.setTextColor(CH2COLOR);
				lcd.print(char(174));
			}
			break;
		case 8:
			if (menuMove == 3)
				trig_lv--;
			else
				trig_lv++;
			break;
		case 9:
			SendData();
			break;
		case 10:
			if (menuMove == 3) {
				/*File myFile= SD.open("evive_file.csv",FILE_WRITE);
				 if(myFile) Serial.println("file successfully opened");
				 for(int j=0;j<SAMPLES;j++)
				 {
				 myFile.print(data[0][j]);
				 myFile.print(",");
				 myFile.print(data[2][j]);
				 }*/
			}
			//ADD DATA LOGGING FUNCTION WITH SD CARD
			break;
		default:
			break;
	}
}

static void SendData() {
	Serial.print(Rates[rate]);
	Serial.println("/div (20 samples)");
	for (int i = 0; i < SAMPLES; i++) {
		Serial.print(data[sample + 0][i] * MILLIVOL_per_dot[range0]);
		Serial.print(" ");
		Serial.println(data[sample + 1][i] * MILLIVOL_per_dot[range1]);
	}
}

static void DrawGrid() {
	for (int x = 0; x <= SAMPLES; x += 2) { // Horizontal Line
		for (int y = GRAPH_TOP_MARGIN; y <= LCD_HEIGHT; y += DOTS_DIV) {
			lcd.drawPixel(x, y, GRIDCOLOR);
			CheckSW();
		}
		if (LCD_HEIGHT == 128)
			lcd.drawPixel(x, LCD_HEIGHT - 1, GRIDCOLOR);
	}
	for (int x = 0; x <= SAMPLES; x += DOTS_DIV) { // Vertical Line
		for (int y = GRAPH_TOP_MARGIN; y <= LCD_HEIGHT; y += 2) {
			lcd.drawPixel(x, y, GRIDCOLOR);
			CheckSW();
		}
	}

	lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch0_off - 3);
	lcd.setTextColor(CH1COLOR);
	lcd.print(char(174));
	lcd.setCursor(LCD_WIDTH - 7, LCD_GRAPH_MID - ch1_off - 3);
	lcd.setTextColor(CH2COLOR);
	lcd.print(char(174));
}

static void DrawText() {
	int itr;
	lcd.fillRect(GRAPH_LEFT_MARGIN, 0, 160, 9, ST7735_WHITE);
	lcd.setTextSize(1);
	lcd.fillRect(GRAPH_LEFT_MARGIN, 0, 40, 9, ST7735_RED);
	lcd.setTextColor(ST7735_WHITE);

	for (itr = 0; itr < 4; itr++) {
		lcd.setCursor((itr) * 41, 1);
		if (itr + menu > MENU_TOTAL_ITEMS)
			PrintMenuItem(itr + menu - MENU_TOTAL_ITEMS);
		else
			PrintMenuItem(itr + menu);
		lcd.setTextColor(ST7735_RED);
	}
}

static void PrintMenuItem(int item) {
	switch (item) {
		case 1:
			lcd.print(Ranges[range0]);
//			lcd.println("/D");
			break;
		case 2:
			lcd.print(Ranges[range1]);
//			lcd.println("/D");
			break;
		case 3:
			lcd.print(Rates[rate]);
			lcd.println("/D");
			break;
		case 4:
			lcd.println(TRIG_Modes[trig_mode]);
			break;
		case 5:
			lcd.println(trig_edge == TRIG_E_UP ? "UP" : "DN");
			break;
		case 6:
			lcd.print("01:");
			lcd.println(
			    (ch0_off * MILLIVOL_per_dot[range0] > 1000) ?
			        ch0_off * MILLIVOL_per_dot[range0] / 1000.0 :
			        ch0_off * MILLIVOL_per_dot[range0]);
			break;
		case 7:
			lcd.print("02:");
			lcd.println(
			    (ch1_off * MILLIVOL_per_dot[range1] > 1000) ?
			        ch1_off * MILLIVOL_per_dot[range1] / 1000.0 :
			        ch1_off * MILLIVOL_per_dot[range1]);
			break;
		case 8:
			lcd.print("TLV:");
			lcd.println(trig_lv);
			break;
		case 9:
			lcd.println("Send");
			break;
		case 10:
			lcd.println("Save");
			break;
		default:
			break;
	}
}

//To draw grid at given x. Will be used while ploting
static void DrawGrid(int x) {
	if ((x % 2) == 0)
		for (int y = GRAPH_TOP_MARGIN; y <= LCD_HEIGHT; y += DOTS_DIV)
			lcd.drawPixel(x, y, GRIDCOLOR);
	if ((x % DOTS_DIV) == 0)
		for (int y = GRAPH_TOP_MARGIN; y <= LCD_HEIGHT; y += 2)
			lcd.drawPixel(x, y, GRIDCOLOR);
}

static void ClearAndDrawGraph() {
	int clear = 0;
	if (sample == 0)
		clear = 2;
//      unsigned long st = micros();
	for (int x = 0; x < (SAMPLES - 1); x++) {
		if (ch0_mode != MODE_OFF) {
			//remove previous data
			if (data[clear][x + 1] <= (LCD_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
				lcd.drawLine(x, LCD_GRAPH_MID - data[clear][x], x + 1,
				LCD_GRAPH_MID - data[clear][x + 1], BGCOLOR);
			//display new data
			if (data[sample][x + 1] <= (LCD_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
				lcd.drawLine(x, LCD_GRAPH_MID - data[sample][x], x + 1,
				LCD_GRAPH_MID - data[sample][x + 1], CH1COLOR);
		}
		if (ch1_mode != MODE_OFF) {
			//remove previous data
			if (data[clear + 1][x + 1] <= (LCD_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
				lcd.drawLine(x, LCD_GRAPH_MID - data[clear + 1][x], x + 1,
				LCD_GRAPH_MID - data[clear + 1][x + 1], BGCOLOR);
			//display new data
			if (data[sample + 1][x + 1] <= (LCD_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
				lcd.drawLine(x, LCD_GRAPH_MID - data[sample + 1][x], x + 1,
				LCD_GRAPH_MID - data[sample + 1][x + 1], CH2COLOR);
		}
		CheckSW();
	}
//Serial.println(micros()-st);
}

static void ClearAndDrawDot(int i) {
	int clear = 0;
	if (i <= 1)
		return;
	if (sample == 0)
		clear = 2;

	if (ch0_mode != MODE_OFF) {
		if (data[clear][i] <= (LCD_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
			lcd.drawLine(i - 1, LCD_GRAPH_MID - data[clear][i - 1], i,
			LCD_GRAPH_MID - data[clear][i], BGCOLOR);
		if (data[sample + 0][i] <= (LCD_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
			lcd.drawLine(i - 1, LCD_GRAPH_MID - data[sample][i - 1], i,
			LCD_GRAPH_MID - data[sample][i], CH1COLOR);
	}
	if (ch1_mode != MODE_OFF) {
		if (data[clear + 1][i] <= (LCD_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
			lcd.drawLine(i - 1, LCD_GRAPH_MID - data[clear + 1][i - 1], i,
			LCD_GRAPH_MID - data[clear + 1][i], BGCOLOR);
		if (data[sample + 1][i] <= (LCD_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
			lcd.drawLine(i - 1, LCD_GRAPH_MID - data[sample + 1][i - 1], i,
			LCD_GRAPH_MID - data[sample + 1][i], CH2COLOR);
	}

	DrawGrid(i);
}

static void DrawGraph() {
	for (int x = 0; x < SAMPLES; x++) {
		if (data[sample + 0][x] <= (LCD_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
			lcd.drawPixel(x, LCD_GRAPH_MID - data[sample + 0][x], CH1COLOR);
		if (data[sample + 1][x] <= (LCD_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
			lcd.drawPixel(x, LCD_GRAPH_MID - data[sample + 1][x], CH2COLOR);
	}
}

static void ClearGraph() {
	int clear = 0;

	if (sample == 0)
		clear = 2;
	for (int x = 0; x < SAMPLES; x++) {
		lcd.drawPixel(x, LCD_GRAPH_MID - data[clear + 0][x], BGCOLOR);
		lcd.drawPixel(x, LCD_GRAPH_MID - data[clear + 1][x], BGCOLOR);
	}
}

int ConvertMilliVoltToPixel(long value, byte range, int off) {
	value = value / (MILLIVOL_per_dot[range]) + off;
	// Serial.println(value);
	value = value >= (LCD_HEIGHT_TOP_MARGIN - off + 1) ?
	LCD_HEIGHT_TOP_MARGIN - off :
	                                                     value;
	return int(value);
}

void evive_oscilloscope() {
	lcd.fillScreen(BGCOLOR);
	lcd.setTextColor(ST7735_RED);
	lcd.setTextWrap(0);
	lcd.setTextSize(3);
	lcd.setCursor(15, 20);
	lcd.print("evive's");
	lcd.setCursor(10, 70);
	lcd.setTextSize(2);
	lcd.print("Oscilloscope");
	ade791x_init();
	delay(500);
	lcd.fillScreen(BGCOLOR);
	lcd.setTextSize(1);
	DrawGrid();
	DrawText();
	//pinMode(5, OUTPUT);
	//  analogWrite(5,0);
	navKeyAttachInterruptMenuPress();
	OSCILLOSCOPE_ON_OFF = 1;

	while (OSCILLOSCOPE_ON_OFF) {
		//unsigned long t=micros();
		evive_oscilloscope_loop();
		//Serial.println(micros()-t);
	}
}

static void evive_oscilloscope_loop() {
	//int value =  ade791x_read_v1 ();
	// value =  ade791x_read_vim ();
	// ade791x_read_i();
	//analogWrite(5,analogRead(A9)/4);
	if (trig_mode != TRIG_SCAN) {
		unsigned long st = millis();
		int oad;
		if (trig_ch == 0)
			oad = ConvertMilliVoltToPixel(ade791x_read_v1(), range0, ch0_off);
		//        oad = ade791x_read_v1();
		else {
			if (range1 < 9)
				oad = ConvertMilliVoltToPixel(ade791x_read_vim(), range1, ch1_off);
			else
				oad = ConvertMilliVoltToPixel(ade791x_read_im(), range1, ch1_off);
		}
		//Wait till trigger detected
		for (;;) {
			int ad;
			if (trig_ch == 0)
				ad = ConvertMilliVoltToPixel(ade791x_read_v1(), range0, ch0_off);
			else {
				if (range1 < 9)
					ad = ConvertMilliVoltToPixel(ade791x_read_vim(), range1, ch1_off);
				else
					ad = ConvertMilliVoltToPixel(ade791x_read_im(), range1, ch1_off);
			}
			//Detect trigger
			if (trig_edge == TRIG_E_UP) {
				if (ad >= trig_lv && ad > oad + 4)
					break;
			} else {
				if (ad <= trig_lv && ad < oad - 4)
					break;
			}
			oad = ad;

			CheckSW();
			if (trig_mode == TRIG_SCAN)
				break;
			if (trig_mode == TRIG_AUTO && (millis() - st) > 100)
				break;
		}
	}

	// sample and draw depending on the sampling rate
	if (rate <= 5 && Start) {
		// change the index for the double buffer
		if (sample == 0)
			sample = 2;
		else
			sample = 0;

		if (rate == 0) { // full speed, channel 0 only
			unsigned long st = millis();
			for (int i = 0; i < SAMPLES; i++) {
				data[sample + 0][i] = ConvertMilliVoltToPixel(ade791x_read_v1(), range0,
				    ch0_off);
				;
			}
			for (int i = 0; i < SAMPLES; i++)
				data[sample + 1][i] = 0;
//       Serial.println(millis()-st);
		} else if (rate == 1) { // full speed, channel 1 only
			unsigned long st = millis();
			for (int i = 0; i < SAMPLES; i++) {
				if (range1 < 9)
					data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_vim(),
					    range1, ch1_off);
				else
					data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_im(),
					    range1, ch1_off);
			}
			for (int i = 0; i < SAMPLES; i++)
				data[sample + 0][i] = 0;
//      Serial.println(millis()-st);
		} else if (rate == 2) { // full speed, dual channel
			unsigned long st = millis();
			for (int i = 0; i < SAMPLES; i++) {
				data[sample + 0][i] = ConvertMilliVoltToPixel(ade791x_read_v1(), range0,
				    ch0_off);
				;
				if (range1 < 9)
					data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_vim(),
					    range1, ch1_off);
				else
					data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_im(),
					    range1, ch1_off);
			}
			// Serial.println(millis()-st);
		} else if (rate >= 3 && rate <= 5) { // .5ms, 1ms or 2ms sampling
			const unsigned long r_[] = { 5000 / DOTS_DIV, 10000 / DOTS_DIV, 20000
			    / DOTS_DIV };
			unsigned long st0 = millis();
			unsigned long st = micros();
			unsigned long r = r_[rate - 3];
			//DO NOT ADD ANY STATEMENT INSIDE FOR LOOP
			for (int i = 0; i < SAMPLES; i++) {
				while ((st - micros()) < r)
					;
				st += r;
				data[sample + 0][i] = ConvertMilliVoltToPixel(ade791x_read_v1(), range0,
				    ch0_off);
				;
				if (range1 < 9)
					data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_vim(),
					    range1, ch1_off);
				else
					data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_im(),
					    range1, ch1_off);
			}
			// Serial.println(millis()-st0);
		}
		ClearAndDrawGraph();
		CheckSW();
		DrawGrid();
		//DrawText();
	} else if (Start) { // 5ms - 500ms sampling
		// copy currently showing data to another
		if (sample == 0) {
			for (int i = 0; i < SAMPLES; i++) {
				data[2][i] = data[0][i];
				data[3][i] = data[1][i];
			}
		} else {
			for (int i = 0; i < SAMPLES; i++) {
				data[0][i] = data[2][i];
				data[1][i] = data[3][i];
			}
		}

		const unsigned long r_[] = { 50000 / DOTS_DIV, 100000 / DOTS_DIV, 200000
		    / DOTS_DIV, 500000 / DOTS_DIV, 1000000 / DOTS_DIV, 2000000 / DOTS_DIV,
		    5000000 / DOTS_DIV, 10000000 / DOTS_DIV };
		//   unsigned long st0 = millis();
		unsigned long st = micros();
		for (int i = 0; i < SAMPLES; i++) {
			while ((st - micros()) < r_[rate - 6]) {
				CheckSW();
				if (rate < 6)
					break;
			}
			if (rate < 6) { // sampling rate has been changed
				lcd_implementation_clear_menu();
				break;
			}
			st += r_[rate - 6];
			if (st - micros() > r_[rate - 6])
				st = micros(); // sampling rate has been changed to shorter interval
			if (!Start) {
				i--;
				continue;
			}
			data[sample + 0][i] = ConvertMilliVoltToPixel(ade791x_read_v1(), range0,
			    ch0_off);
			;
			if (range1 < 9)
				data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_vim(),
				    range1, ch1_off);
			else
				data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_im(), range1,
				    ch1_off);
			ClearAndDrawDot(i);
		}
		// Serial.println(millis()-st0);
		DrawGrid();
		//DrawText();
	} else {
		CheckSW();
	}
	if (trig_mode == TRIG_ONE)
		Start = 0;
	else
		Start = 1;
}

//-------------mini oscilloscope/end--------------//

//-------------Serial Monitor/Start---------------//
void lcd_implementation_serial_monitor() {

	if (Serial.available()) {
		serialObject.serial0PrintMsg();
	} else if (Serial2.available()) {
		serialObject.serial2PrintMsg();
	} else
		(Serial3.available());
	{
		serialObject.serial3PrintMsg();
	}
}

//-------------pin state monitor-/*LOGIC ANALYSER */--------//

/*LigitalRead fn*/
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))

//uint8_t digitalpinno[43] = { 6, 7, 1, 5, 15, 16, 17, 18, 23, 24, 25, 26, 64,
//    63, 13, 12, 46, 45, 78, 77, 76, 75, 74, 73, 72, 71, 60, 59, 58, 57, 56,
//    55, 54, 53, 50, 70, 52, 51, 42, 41, 40, 39, 38 };

uint8_t digitalpinno[40] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37,
    38, 39, 40, 41, 42, 43 };

static void turnOffPWM(uint8_t timer) {
	switch (timer) {
#if defined(TCCR1A) && defined(COM1A1)
		case TIMER1A:
			cbi(TCCR1A, COM1A1);
			break;
#endif
#if defined(TCCR1A) && defined(COM1B1)
		case TIMER1B:
			cbi(TCCR1A, COM1B1);
			break;
#endif
#if defined(TCCR1A) && defined(COM1C1)
		case TIMER1C:
			cbi(TCCR1A, COM1C1);
			break;
#endif

#if defined(TCCR2) && defined(COM21)
			case TIMER2: cbi(TCCR2, COM21); break;
#endif

#if defined(TCCR0A) && defined(COM0A1)
		case TIMER0A:
			cbi(TCCR0A, COM0A1);
			break;
#endif

#if defined(TCCR0A) && defined(COM0B1)
		case TIMER0B:
			cbi(TCCR0A, COM0B1);
			break;
#endif
#if defined(TCCR2A) && defined(COM2A1)
		case TIMER2A:
			cbi(TCCR2A, COM2A1);
			break;
#endif
#if defined(TCCR2A) && defined(COM2B1)
		case TIMER2B:
			cbi(TCCR2A, COM2B1);
			break;
#endif

#if defined(TCCR3A) && defined(COM3A1)
		case TIMER3A:
			cbi(TCCR3A, COM3A1);
			break;
#endif
#if defined(TCCR3A) && defined(COM3B1)
		case TIMER3B:
			cbi(TCCR3A, COM3B1);
			break;
#endif
#if defined(TCCR3A) && defined(COM3C1)
		case TIMER3C:
			cbi(TCCR3A, COM3C1);
			break;
#endif

#if defined(TCCR4A) && defined(COM4A1)
		case TIMER4A:
			cbi(TCCR4A, COM4A1);
			break;
#endif
#if defined(TCCR4A) && defined(COM4B1)
		case TIMER4B:
			cbi(TCCR4A, COM4B1);
			break;
#endif
#if defined(TCCR4A) && defined(COM4C1)
		case TIMER4C:
			cbi(TCCR4A, COM4C1);
			break;
#endif
#if defined(TCCR4C) && defined(COM4D1)
			case TIMER4D: cbi(TCCR4C, COM4D1); break;
#endif

#if defined(TCCR5A)
		case TIMER5A:
			cbi(TCCR5A, COM5A1);
			break;
		case TIMER5B:
			cbi(TCCR5A, COM5B1);
			break;
		case TIMER5C:
			cbi(TCCR5A, COM5C1);
			break;
#endif
	}
}

int ligitalRead(uint8_t pin) {

	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	if (port == NOT_A_PIN)
		return LOW;

	// If the pin that support PWM output, we need to turn it off
	// before getting a digital reading.
	if (timer != NOT_ON_TIMER)
		turnOffPWM(timer);

	if (*portInputRegister(port) & bit)
		return HIGH;
	return LOW;
}

/*LigitalRead fn*/

//Logic analyser Template
void lcd_digital_pin_state_monitor_template() {
	lcd.setCursor(0, 16);
	lcd.setTextColor(ST7735_RED);
	lcd.print("DIGITAL PINS");
	lcd.setCursor(0, 24);
	uint8_t pinNumber;
	lcd.setTextColor(ST7735_GREEN, ST7735_BLACK);
	for (pinNumber = 0; pinNumber < 40; pinNumber++) {   // printing digital pins

		lcd.setCursor((pinNumber % 6) * 3 + (pinNumber % 6) * 24,
		    24 + (pinNumber / 6) * 8);
		if (pinNumber <= 17)
			lcd.print(pinNumber + 2);
		else
			lcd.print(pinNumber + 4);
		lcd.print(":");
	}
}

void lcd_analog_pin_state_monitor_template() {
	uint8_t pinNumber;
	lcd.setCursor(0, 80);
	lcd.setTextColor(ST7735_RED);
	lcd.setTextWrap(0);
	lcd.print("ANALOG PINS");
	lcd.setTextColor(ST7735_GREEN, ST7735_BLACK);
	lcd.setCursor(118, 80);
	lcd.print(0);
	for (pinNumber = 0; pinNumber < 16; pinNumber++) {  //printing analog pins
		lcd.setCursor((pinNumber % 3) * 3 + (pinNumber % 3) * 56,
		    88 + (pinNumber / 3) * 8);
		lcd.print(pinNumber + 1);
	}
}

/*Logic Analyser */
static void lcd_implementation_digital_pin_state() {
	uint8_t pinNumber;
	bool j;
	lcd.setTextColor(ST7735_WHITE, ST7735_BLACK);
	for (pinNumber = 0; pinNumber < 40; pinNumber++) {   // printing digital pins
		lcd.setCursor(CHAR_WIDTH * 3 + (pinNumber % 6) * 3 + (pinNumber % 6) * 24,
		    24 + (pinNumber / 6) * 8);
		j = ligitalRead(digitalpinno[pinNumber]);
		lcd.print(j);
	}
}

static void lcd_implementation_analog_pin_state() {
	uint8_t pinNumber = 0;
	lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	lcd.setCursor(134, 80);
	lcd.print(analogRead(pinNumber));
	lcd.print("   ");
	for (pinNumber = 0; pinNumber < 16; pinNumber++) {  //printing analog pins
		lcd.setCursor(14 + (pinNumber % 3) * 3 + (pinNumber % 3) * 56,
		    88 + (pinNumber / 3) * 8);
		lcd.print(analogRead(pinNumber + 1));
		lcd.print("   ");
	}
}

//-------------dac or function generator/start--------------//
void displayFrequenccyAmplitude() {
	//Only update on screen, if values are changed
	if (oldIncrement != increment) {
		lcd.setCursor(10, 60);
		if (encoderPosition == 5)
			lcd.print("-");
		else
			lcd.print(8.5 + 8.3 * (increment - 1));
		lcd.print("  ");
		//   Serial.println(increment);
	}
	if (oldAmplitude != amplitude) {
		lcd.setCursor(10, 90);
		if (encoderPosition == 5)
			lcd.print(amplitude * 5.0);
		else
			lcd.print(amplitude * 2.5);
		//   Serial.println(amplitude);
	}
}

void lcd_implementation_dac_template() {
	lcd.fillScreen(ST7735_BLACK);
	lcd.setTextColor(ST7735_GREEN);
	lcd.setCursor(10, 30);
	switch (encoderPosition + 1) {
		case 1:
			lcd.print(MSG_SINE);
			break;
		case 2:
			lcd.print(MSG_SQUARE);
			break;
		case 3:
			lcd.print(MSG_TRIANGULAR);
			break;
		case 4:
			lcd.print(MSG_SAWTOOTH_UP);
			break;
		case 5:
			lcd.print(MSG_SAWTOOTH_DOWN);
			break;
		case 6:
			lcd.print(MSG_ANALOG_OUT);
			break;
	}

	lcd.setTextColor(ST7735_WHITE);
	lcd.setCursor(10, 50);
	lcd.print("Frequency (Hz):");
	lcd.setCursor(10, 80);
	lcd.print("Amplitude (V):");
	lcd.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	lcd.setCursor(10, 60);
	if (encoderPosition + 1 == 6)
		lcd.print("-");
	else
		lcd.print(8.5 + 8.3 * (increment - 1));
	lcd.print("  ");
	lcd.setCursor(10, 90);
	lcd.print(amplitude * 2.5);
}

#endif
