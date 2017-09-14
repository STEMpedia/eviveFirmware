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
#ifndef TFT_HEIGHT
#define TFT_HEIGHT      128
#endif
#ifndef TFT_WIDTH
#define TFT_WIDTH       160
#endif
#ifndef TFT_WIDTH_BY_2
#define TFT_WIDTH_BY_2  80
#endif
//#define TFT_STR_UPLEVEL 	'^'
#define TFT_STR_ARROW_RIGHT ">"
#define TFT_STR_UPLEVEL     "\x03"
#define BATT_X							140
#define BATT_Y							4
#define BATT_WIDTH					17
#define BATT_HEIGHT					7
#define BATT_COLOR					ST7735_CYAN
#define VVR_MULTIPLIER			0.0381
uint16_t pre_vvr = 0, vvr = 0;

static void drawBattery();
void batteryUpdate();
void vvrUpdate();
static void printVvr();
static void drawStatusBar();
//Actual implementation of the TFT display routines
//Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

TFT_ST7735 tft = TFT_ST7735();
extern int8_t encoderPosition;

static void tft_implementation_init() {
	//tft.initR();
	//tft.initR(SCREEN_TAB);
	tft.init();
	tft.setRotation(1);
	//tft.setTextWrap(false);
	tft.fillScreen(ST7735_BLACK);
	tft.drawBitmap(45, 29, evive_logo, 71, 71, ST7735_BLUE);
	delay(MIN_TIME5);	//DELAY HERE. DO NOT CALL THIS MORE THAN ONCE EVER EVER EVER
	tft.fillScreen(ST7735_BLACK);
	tft.setTextSize(1);
	drawStatusBar();
	//SD.begin(34);
}

static void drawBattery() {
	tft.drawFastHLine(BATT_X, BATT_Y, BATT_WIDTH - 2, BATT_COLOR);
	tft.drawFastVLine(BATT_X + BATT_WIDTH - 2, BATT_Y, BATT_HEIGHT + 1,	BATT_COLOR);
	tft.drawFastVLine(BATT_X + BATT_WIDTH - 1, BATT_Y + 2, 4, ST7735_WHITE);
	tft.drawFastVLine(BATT_X + BATT_WIDTH, BATT_Y + 2, 4, ST7735_WHITE);
	tft.drawFastHLine(BATT_X, BATT_Y + BATT_HEIGHT, BATT_WIDTH - 2, BATT_COLOR);
	tft.drawFastVLine(BATT_X, BATT_Y, BATT_HEIGHT, BATT_COLOR);
}

void batteryUpdate() {
	int batt = analogRead(BATSUPPLYLEVEL);
	int widthMeter = 0;
	if (batt < 630)
		widthMeter = 0;
	else if (batt < 672)
		widthMeter = 5;
	else if (batt < 752)
		widthMeter = 10;
	else
		widthMeter = BATT_WIDTH - 3;
	tft.fillRect(BATT_X + 1, BATT_Y + 1, widthMeter, BATT_HEIGHT - 1, BATT_COLOR);
}

static void drawStatusBar() {
	tft.setTextColor(ST7735_CYAN);
	tft.setCursor(0, 3);
	tft.print(F("evive"));
	drawBattery();
	batteryUpdate();
	printVvr();
	vvrUpdate();
}

//static void statusBarUpdate(){
//}

static void printVvr() {
	tft.setCursor(70, 3);
	tft.print(F("VVR: "));
}
void vvrUpdate() {
	vvr = analogRead(VARSUPPLYLEVEL);
	if (pre_vvr - vvr > 4 || pre_vvr - vvr < -4) {
		tft.setTextColor(ST7735_RED);
		tft.setCursor(70 + 24, 3);
		tft.fillRect(70 + 24, 3, 35, 7, ST7735_BLACK);
		tft.print(vvr * VVR_MULTIPLIER);
		pre_vvr = vvr;
	}
}

static void tft_implementation_drawmenu_generic(uint8_t row, const char* pstr,
    char pre_char, char post_char) {
		tft.fillRect( LEFT_MARGIN ,
	TOP_MARGIN + ROW_HEIGHT * row, TFT_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1,
	ROW_HEIGHT, ST7735_BLACK);
	char c;
	uint8_t n = TFT_WIDTH / CHAR_WIDTH;
	tft.setCursor(LEFT_MARGIN, TOP_MARGIN + (row) * ROW_HEIGHT);
	tft.print(pre_char);
	while (((c = pgm_read_byte(pstr)) != '\0') && (n > 0)) {
		tft.print(c);
		pstr++;
		n--;
	}
	//tft.fillRect(2 + LEFT_MARGIN + TFT_WIDTH - n * CHAR_WIDTH,
	//TOP_MARGIN + ROW_HEIGHT * row, TFT_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1,
	//ROW_HEIGHT, ST7735_BLACK);
	tft.setCursor(TFT_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1,
	TOP_MARGIN + (row) * ROW_HEIGHT);
	tft.print(post_char);
}

/*static void tft_implementation_drawmenu_setting_edit_generic(uint8_t row,
    const char* pstr, char pre_char, char data) {
	tft.setCursor(TOP_MARGIN + (row) * ROW_HEIGHT, LEFT_MARGIN);
	tft.print(pre_char);
	tft.print("  ");
	tft.print(pstr);
	tft.setCursor((row - 1) * ROW_HEIGHT,
	TFT_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1);
	tft.print(data);
}*/

#define tft_implementation_drawmenu_setting_edit_int3_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', itostr3(*(data)))
#define tft_implementation_drawmenu_setting_edit_int3(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', itostr3(*(data)))
#define tft_implementation_drawmenu_setting_edit_float3_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr3(*(data)))
#define tft_implementation_drawmenu_setting_edit_float3(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr3(*(data)))
#define tft_implementation_drawmenu_setting_edit_float32_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr32(*(data)))
#define tft_implementation_drawmenu_setting_edit_float32(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr32(*(data)))
#define tft_implementation_drawmenu_setting_edit_float5_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define tft_implementation_drawmenu_setting_edit_float5(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define tft_implementation_drawmenu_setting_edit_float52_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr52(*(data)))
#define tft_implementation_drawmenu_setting_edit_float52(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr52(*(data)))
#define tft_implementation_drawmenu_setting_edit_float51_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr51(*(data)))
#define tft_implementation_drawmenu_setting_edit_float51(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr51(*(data)))
#define tft_implementation_drawmenu_setting_edit_long5_selected(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, '>', ftostr5(*(data)))
#define tft_implementation_drawmenu_setting_edit_long5(row, pstr, pstr2, data, minValue, maxValue) tft_implementation_drawmenu_setting_edit_generic(row, pstr, ' ', ftostr5(*(data)))
#define tft_implementation_drawmenu_setting_edit_bool_selected(row, pstr, pstr2, data) tft_implementation_drawmenu_setting_edit_generic_P(row, pstr, '>', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))
#define tft_implementation_drawmenu_setting_edit_bool(row, pstr, pstr2, data) tft_implementation_drawmenu_setting_edit_generic_P(row, pstr, ' ', (*(data))?PSTR(MSG_ON):PSTR(MSG_OFF))

void tft_implementation_drawedit(const char* pstr, char* value) {
	tft.setCursor(TOP_MARGIN, LEFT_MARGIN);
	tft.print(pstr);
	tft.print(':');
	tft.setCursor(TOP_MARGIN, TFT_WIDTH - RIGHT_MARGIN - CHAR_WIDTH * 1);
	tft.print(value);
}
#define tft_implementation_drawmenu_back_selected(row, pstr, data) tft_implementation_drawmenu_generic(row, pstr, TFT_STR_UPLEVEL[0], TFT_STR_UPLEVEL[0])
#define tft_implementation_drawmenu_back(row, pstr, data) tft_implementation_drawmenu_generic(row, pstr, ' ', TFT_STR_UPLEVEL[0])
#define tft_implementation_drawmenu_submenu_selected(row, pstr, data) tft_implementation_drawmenu_generic(row, pstr, '>', char(175));
#define tft_implementation_drawmenu_submenu(row, pstr, data) tft_implementation_drawmenu_generic(row, pstr, ' ', char(175));//TFT_STR_ARROW_RIGHT[0])
#define tft_implementation_drawmenu_function_selected(row, pstr, data) tft_implementation_drawmenu_generic(row, pstr, '>', ' ')
#define tft_implementation_drawmenu_function(row, pstr, data) tft_implementation_drawmenu_generic(row, pstr, ' ', ' ')

void tft_implementation_clear_full() {
	tft.fillScreen(ST7735_BLACK);
}

void tft_implementation_clear_menu() {
	tft.fillRect(0, TOP_MARGIN, TFT_WIDTH,
	TFT_HEIGHT - TOP_MARGIN - BOTTOM_MARGIN, ST7735_BLACK);
}

void tft_implementation_text_and_background_color(uint16_t text_clr,
    uint16_t text_background_clr) {
	tft.setTextColor(text_clr, text_background_clr);
}

//control status functions

void tft_implementation_control_status_motor(bool sec) {
	tft.setTextColor(ST7735_RED, ST7735_BLACK);
	if (sec) {
		//tft.fillRect(TFT_WIDTH_BY_2+45,TOP_MARGIN+ROW_HEIGHT*3, 39, ROW_HEIGHT*4, ST7735_BLACK);
		tft.setCursor(TFT_WIDTH_BY_2 + 45, TOP_MARGIN + ROW_HEIGHT * 3);
		tft.print(motor2.getPWM());
		tft.print("  ");
		tft.setCursor(TFT_WIDTH_BY_2 + 45, TOP_MARGIN + ROW_HEIGHT * 5);
		tft.print(motor2.dir1);
		tft.setCursor(TFT_WIDTH_BY_2 + 45, TOP_MARGIN + ROW_HEIGHT * 6);
		tft.print(motor2.dir2);
	} else {
		//tft.fillRect(45,TOP_MARGIN+ROW_HEIGHT*3, 39, ROW_HEIGHT*4, ST7735_BLACK);
		tft.setCursor(45, TOP_MARGIN + ROW_HEIGHT * 3);
		tft.print(motor1.getPWM());
		tft.print("  ");
		tft.setCursor(45, TOP_MARGIN + ROW_HEIGHT * 5);
		tft.print(motor1.dir1);
		tft.setCursor(45, TOP_MARGIN + ROW_HEIGHT * 6);
		tft.print(motor1.dir2);
	}
}

unsigned long lastServoImplement = 0;

void tft_implementation_control_status_servo(bool sec) {
	tft.setTextColor(ST7735_RED, ST7735_BLACK);

	if (sec && prevValueServo2()!= servo2.read() && (millis()-lastServoImplement)> MIN_TIME1) {
		//tft.drawLine(TFT_WIDTH_BY_2+40,105,TFT_WIDTH_BY_2+40+20*sin((-prevValueServo2()-90)*3.14/180),75+20*cos((-prevValueServo2()-90)*3.14/180),ST7735_BLACK);
		//tft.drawLine(TFT_WIDTH_BY_2+40,105,TFT_WIDTH_BY_2+40+20*sin((-servo2.read()-90)*3.14/180),75+20*cos((-servo2.read()-90)*3.14/180),ST7735_GREEN);
		tft.setCursor(TFT_WIDTH_BY_2 + 50, TOP_MARGIN + ROW_HEIGHT * 3);
		tft.print(servo2.read());
		tft.print("  ");
		//Serial.println("went in 2");
		lastServoImplement = millis();
	}
	if (~sec && prevValueServo1() != servo1.read() && (millis()-lastServoImplement)> MIN_TIME1) {
		//tft.drawLine(40,105,40+20*sin((-prevValueServo1()-90)*3.14/180),75+20*cos((-prevValueServo1()-90)*3.14/180),ST7735_BLACK);
		//tft.drawLine(40,105,40+20*sin((-servo1.read()-90)*3.14/180),75+20*cos((-servo1.read()-90)*3.14/180),ST7735_GREEN);
		tft.setCursor(50, TOP_MARGIN + ROW_HEIGHT * 3);
		tft.print(servo1.read());
		tft.print("  ");
		//Serial.println("went in 1");
		lastServoImplement = millis();
	}
}

/*****variables for motor function*****/
bool stps;
bool dir1;
bool dir2;

void tft_implementation_control_status_stepper() {
	if (stps != digitalRead(TACTILESW1) || dir1 != digitalRead(SLIDESW1_D2)
	    || dir2 != digitalRead(SLIDESW1_D1))//change the screen only if a variable is changed
	        {
		tft.setTextColor(ST7735_RED, ST7735_BLACK);
		tft.setCursor(50, TOP_MARGIN + ROW_HEIGHT * 7);
		tft.print(F("\n Stepper Direction : "));
		dir1 = digitalRead(SLIDESW1_D2);
		dir2 = digitalRead(SLIDESW1_D1);
		if (dir1) {
			tft.print(F("Dir 1"));
		} else if (dir2)
			tft.print(F("Dir 2"));
		else
			tft.print(F("0   "));
		tft.print(F("\n Speed :"));
		stps = digitalRead(TACTILESW1);
		if (stps) {
			tft.print(F("10x"));
		} else
			tft.print(F("x  "));
	}
}

void tft_control_status_template() {
	tft.setTextColor(ST7735_RED);
	tft_implementation_clear_menu();
	if (_MOTOR1_EN) {
		tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
		tft.println(F("   Motor 1"));
		tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
		tft.println(F(" PWM:"));
		tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 4);
		tft.println(F(" States:"));
		tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 5);
		tft.println(F("  Dir1:"));
		tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 6);
		tft.print(F("  Dir2:"));
	} else {
		if (_SERVO1_EN) {
			tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
			tft.println(F("   Servo 1"));
			//tft.drawBitmap(15, 50, semiCircle, 80, 25, ST7735_YELLOW);
			tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
			tft.println(F("  Angle:"));
		}
	}
	if (_MOTOR2_EN) {
		tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
		tft.println(F("   Motor 2"));
		tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
		tft.println(F(" PWM:"));
		tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 4);
		tft.println(F(" States:"));
		tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 5);
		tft.print(F("  Dir1:"));
		tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 6);
		tft.print(F("  Dir2:"));
	} else {
		if (_SERVO2_EN) {
			tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
			tft.println(F("   Servo 2"));
			//tft.drawBitmap(TFT_WIDTH_BY_2+15, 80, semiCircle, 50, 25, ST7735_YELLOW);
			tft.setCursor(TFT_WIDTH_BY_2 + LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
			tft.println(F("  Angle:"));
		}
	}
}

void tft_sensing_status_template(bool probeVIConfig) {
	ade791x_init();
	tft.setTextColor(ST7735_RED);
	tft_implementation_clear_menu();
	tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 1);
	tft.println(F("   Probe V"));
	tft.setCursor(LEFT_MARGIN, TOP_MARGIN + ROW_HEIGHT * 3);
	tft.println(F("   V"));
	tft.setCursor(TFT_WIDTH_BY_2, TOP_MARGIN + ROW_HEIGHT * 1);
	tft.println(F("  Probe I/V"));
	tft.setCursor(TFT_WIDTH_BY_2, TOP_MARGIN + ROW_HEIGHT * 3);
	if (probeVIConfig)
		tft.print(F("  A"));
	else
		tft.print(F("  V"));
}

void tft_implementation_sensing_status(bool probeVIConfig) {
	//Add code here
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.setCursor(LEFT_MARGIN + 19, TOP_MARGIN + ROW_HEIGHT * 2);
	tft.print(ade791x_read_v1() / 1000.0, 2);
	tft.print("    ");
	tft.setCursor(TFT_WIDTH_BY_2 + 12, TOP_MARGIN + ROW_HEIGHT * 2);

	if (probeVIConfig)
		tft.print(ade791x_read_im() / 1000.0, 2);
	else
		tft.print(ade791x_read_vim() / 1000.0, 2);
	tft.print("    ");

	// long V1 = ade791x_read_v1()/1000.0;
	// if(V1<0)	tft.setCursor(LEFT_MARGIN-CHAR_WIDTH+19, TOP_MARGIN+ROW_HEIGHT*2);
	// else tft.setCursor(LEFT_MARGIN+19, TOP_MARGIN+ROW_HEIGHT*2);
	// tft.print(V1,2);
	// tft.print("    ");

	// if(probeVIConfig){
	// long IM = ade791x_read_im()/1000.0;
	// if(V1<0)	tft.setCursor(TFT_WIDTH_BY_2+12-CHAR_WIDTH, TOP_MARGIN+ROW_HEIGHT*2);
	// else tft.setCursor(TFT_WIDTH_BY_2+12, TOP_MARGIN+ROW_HEIGHT*2);
	// tft.print(IM,2);
	// }

	// else {
	// long VIM = ade791x_read_vim()/1000.0;
	// if(VIM<0)	tft.setCursor(TFT_WIDTH_BY_2+12-CHAR_WIDTH, TOP_MARGIN+ROW_HEIGHT*2);
	// else tft.setCursor(TFT_WIDTH_BY_2+12, TOP_MARGIN+ROW_HEIGHT*2);
	// tft.print(VIM,2);
	// }
	// tft.print("    ");
}

//-------------mini oscilloscope/start--------------//
#define txtLINE0   0
#define txtLINE1   40
#define txtLINE2   80
#define txtLINE3   120

const int SAMPLES = 160;
const int DOTS_DIV = 20;
//range0, range1, rate, TRIG_Modes, TRIG_E_DN/UP ch0_off, ch1_off, trig_lv, Send, log
const int MENU_TOTAL_ITEMS = 11;

#define GRAPH_TOP_MARGIN			9
#define GRAPH_LEFT_MARGIN			0
#define TFT_HEIGHT_TOP_MARGIN 119
#define TFT_GRAPH_MID					69
#define TFT_GRPAH_MID_TOP_MARGIN 60

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

bool updateData = true;
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
	Serial.println(menu);
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
					tft.fillRect(0, GRAPH_LEFT_MARGIN, TFT_WIDTH, TFT_HEIGHT_TOP_MARGIN,
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
					tft.fillRect(0, GRAPH_LEFT_MARGIN, TFT_WIDTH, TFT_HEIGHT_TOP_MARGIN,
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
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch0_off - 3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch0_off--;
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch0_off - 3);
				tft.setTextColor(CH1COLOR);
				tft.print(char(174));
			} else {
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch0_off - 3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch0_off++;
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch0_off - 3);
				tft.setTextColor(CH1COLOR);
				tft.print(char(174));

			}
			break;
		case 7:
			if (menuMove == 3) {
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch1_off - 3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch1_off--;
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch1_off - 3);
				tft.setTextColor(CH2COLOR);
				tft.print(char(174));
			} else {
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch1_off - 3);
				tft.setTextColor(BGCOLOR);
				tft.print(char(174));
				ch1_off++;
				tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch1_off - 3);
				tft.setTextColor(CH2COLOR);
				tft.print(char(174));
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
			if (menuMove == 3) {/*
				File myFile= SD.open("evive_file.csv",FILE_WRITE);
				 if(myFile) Serial.println("file successfully opened");
				 for(int j=0;j<SAMPLES;j++)
				 {
				 myFile.print(data[0][j]);
				 myFile.print(",");
				 myFile.print(data[2][j]);
				 }
				 myFile.close();*/
			}
			//ADD DATA LOGGING FUNCTION WITH SD CARD
			break;
		case 11: 
			if (menuMove==3)
			{
				updateData=!updateData;
			}
			break;
		default:
			break;
	}
}

static void SendData() {
	Serial.print(Rates[rate]);
	Serial.println(F("/div (20 samples)"));
	for (int i = 0; i < SAMPLES; i++) {
		Serial.print(data[sample + 0][i] * MILLIVOL_per_dot[range0]);
		Serial.print(" ");
		Serial.println(data[sample + 1][i] * MILLIVOL_per_dot[range1]);
	}
}

static void DrawGrid() {
	for (int x = 0; x <= SAMPLES; x += 2) { // Horizontal Line
		for (int y = GRAPH_TOP_MARGIN; y <= TFT_HEIGHT; y += DOTS_DIV) {
			tft.drawPixel(x, y, GRIDCOLOR);
			CheckSW();
		}
		if (TFT_HEIGHT == 128)
			tft.drawPixel(x, TFT_HEIGHT - 1, GRIDCOLOR);
	}
	for (int x = 0; x <= SAMPLES; x += DOTS_DIV) { // Vertical Line
		for (int y = GRAPH_TOP_MARGIN; y <= TFT_HEIGHT; y += 2) {
			tft.drawPixel(x, y, GRIDCOLOR);
			CheckSW();
		}
	}

	tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch0_off - 3);
	tft.setTextColor(CH1COLOR);
	tft.print(char(174));
	tft.setCursor(TFT_WIDTH - 7, TFT_GRAPH_MID - ch1_off - 3);
	tft.setTextColor(CH2COLOR);
	tft.print(char(174));
}

static void DrawText() {
	int itr;
	tft.fillRect(GRAPH_LEFT_MARGIN, 0, 160, 9, ST7735_WHITE);
	tft.setTextSize(1);
	tft.fillRect(GRAPH_LEFT_MARGIN, 0, 40, 9, ST7735_RED);
	tft.setTextColor(ST7735_WHITE);

	for (itr = 0; itr < 4; itr++) {
		tft.setCursor((itr) * 41, 1);
		if (itr + menu > MENU_TOTAL_ITEMS)
			PrintMenuItem(itr + menu - MENU_TOTAL_ITEMS);
		else
			PrintMenuItem(itr + menu);
		tft.setTextColor(ST7735_RED);
	}
}

static void PrintMenuItem(int item) {
	switch (item) {
		case 1:
			tft.print(Ranges[range0]);
//			tft.println("/D");
			break;
		case 2:
			tft.print(Ranges[range1]);
//			tft.println("/D");
			break;
		case 3:
			tft.print(Rates[rate]);
			tft.println(F("/D"));
			break;
		case 4:
			tft.println(TRIG_Modes[trig_mode]);
			break;
		case 5:
			tft.println(trig_edge == TRIG_E_UP ? "UP" : "DN");
			break;
		case 6:
			tft.print(F("01:"));
			tft.println(
			    (ch0_off * MILLIVOL_per_dot[range0] > 1000) ?
			        ch0_off * MILLIVOL_per_dot[range0] / 1000.0 :
			        ch0_off * MILLIVOL_per_dot[range0]);
			break;
		case 7:
			tft.print(F("02:"));
			tft.println(
			    (ch1_off * MILLIVOL_per_dot[range1] > 1000) ?
			        ch1_off * MILLIVOL_per_dot[range1] / 1000.0 :
			        ch1_off * MILLIVOL_per_dot[range1]);
			break;
		case 8:
			tft.print(F("TLV:"));
			tft.println(trig_lv);
			break;
		case 9:
			tft.println(F("Send"));
			break;
		case 10:
			tft.println(F("---"));     //save to SD card
			break;
		case 11:
			if(updateData)
				tft.print(F("stop"));
			else
				tft.print(F("start"));
			break;
		default:
			break;
	}
}

//To draw grid at given x. Will be used while ploting
static void DrawGrid(int x) {
	if ((x % 2) == 0)
		for (int y = GRAPH_TOP_MARGIN; y <= TFT_HEIGHT; y += DOTS_DIV)
			tft.drawPixel(x, y, GRIDCOLOR);
	if ((x % DOTS_DIV) == 0)
		for (int y = GRAPH_TOP_MARGIN; y <= TFT_HEIGHT; y += 2)
			tft.drawPixel(x, y, GRIDCOLOR);
}

static void ClearAndDrawGraph() {
	int clear = 0;
	if (sample == 0)
		clear = 2;
//      unsigned long st = micros();
	for (int x = 0; x < (SAMPLES - 1); x++) {
		if (ch0_mode != MODE_OFF) {
			//remove previous data
			if (data[clear][x + 1] <= (TFT_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
				tft.drawLine(x, TFT_GRAPH_MID - data[clear][x], x + 1,
				TFT_GRAPH_MID - data[clear][x + 1], BGCOLOR);
			//display new data
			if (data[sample][x + 1] <= (TFT_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
				tft.drawLine(x, TFT_GRAPH_MID - data[sample][x], x + 1,
				TFT_GRAPH_MID - data[sample][x + 1], CH1COLOR);
		}
		if (ch1_mode != MODE_OFF) {
			//remove previous data
			if (data[clear + 1][x + 1] <= (TFT_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
				tft.drawLine(x, TFT_GRAPH_MID - data[clear + 1][x], x + 1,
				TFT_GRAPH_MID - data[clear + 1][x + 1], BGCOLOR);
			//display new data
			if (data[sample + 1][x + 1] <= (TFT_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
				tft.drawLine(x, TFT_GRAPH_MID - data[sample + 1][x], x + 1,
				TFT_GRAPH_MID - data[sample + 1][x + 1], CH2COLOR);
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
		if (data[clear][i] <= (TFT_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
			tft.drawLine(i - 1, TFT_GRAPH_MID - data[clear][i - 1], i,
			TFT_GRAPH_MID - data[clear][i], BGCOLOR);
		if (data[sample + 0][i] <= (TFT_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
			tft.drawLine(i - 1, TFT_GRAPH_MID - data[sample][i - 1], i,
			TFT_GRAPH_MID - data[sample][i], CH1COLOR);
	}
	if (ch1_mode != MODE_OFF) {
		if (data[clear + 1][i] <= (TFT_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
			tft.drawLine(i - 1, TFT_GRAPH_MID - data[clear + 1][i - 1], i,
			TFT_GRAPH_MID - data[clear + 1][i], BGCOLOR);
		if (data[sample + 1][i] <= (TFT_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
			tft.drawLine(i - 1, TFT_GRAPH_MID - data[sample + 1][i - 1], i,
			TFT_GRAPH_MID - data[sample + 1][i], CH2COLOR);
	}

	DrawGrid(i);
}

/*
static void DrawGraph() {
	for (int x = 0; x < SAMPLES; x++) {
		if (data[sample + 0][x] <= (TFT_GRPAH_MID_TOP_MARGIN - ch0_off + 1))
			tft.drawPixel(x, TFT_GRAPH_MID - data[sample + 0][x], CH1COLOR);
		if (data[sample + 1][x] <= (TFT_GRPAH_MID_TOP_MARGIN - ch1_off + 1))
			tft.drawPixel(x, TFT_GRAPH_MID - data[sample + 1][x], CH2COLOR);
	}
}

static void ClearGraph() {
	int clear = 0;

	if (sample == 0)
		clear = 2;
	for (int x = 0; x < SAMPLES; x++) {
		tft.drawPixel(x, TFT_GRAPH_MID - data[clear + 0][x], BGCOLOR);
		tft.drawPixel(x, TFT_GRAPH_MID - data[clear + 1][x], BGCOLOR);
	}
}
*/

int ConvertMilliVoltToPixel(long value, byte range, int off) {
	//Serial.println(value);
	value = value / (MILLIVOL_per_dot[range]) + off;
	// Serial.println(value);
	value = value >= (TFT_HEIGHT_TOP_MARGIN - off + 1) ?
	TFT_HEIGHT_TOP_MARGIN - off :
	                                                     value;
														 
	//Serial.println(value);
	return int(value);
}


int ConvertMilliVoltToPixel1(long value, byte range, int off) {
	//Serial.println(value);
	value = value / (MILLIVOL_per_dot[range]) + off;
	// Serial.println(value);
	value = value >= (TFT_HEIGHT_TOP_MARGIN - off + 1) ?
	TFT_HEIGHT_TOP_MARGIN - off :
	                                                     value;
														 
	//Serial.println(value);
	return int(value);
}

int ConvertMilliVoltToPixel2(long value, byte range, int off) {
	//Serial.println(value);
	value = value / (MILLIVOL_per_dot[range]) + off;
	// Serial.println(value);
	value = value >= (TFT_HEIGHT_TOP_MARGIN - off + 1) ?
	TFT_HEIGHT_TOP_MARGIN - off :
	                                                     value;
														 
	//Serial.println(value);
	return int(value);
}

int v;
void evive_oscilloscope() {
	tft.fillScreen(BGCOLOR);
	tft.setTextColor(ST7735_RED);
	tft.setTextWrap(0);
	tft.setTextSize(3);
	tft.setCursor(15, 20);
	tft.print("evive's");
	tft.setCursor(10, 70);
	tft.setTextSize(2);
	tft.print("Oscilloscope");
	ade791x_init();
	delay(500);
	tft.fillScreen(BGCOLOR);
	tft.setTextSize(1);
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
	//unsigned long t= micros();
	
	//Serial.println();
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
if(updateData){// sample and draw depending on the sampling rate
	if (rate <= 5 && Start) {
		// change the index for the double buffer
		if (sample == 0)
			sample = 2;
		else
			sample = 0;

		if (rate == 0) { // full speed, channel 0 only
//			unsigned long st = millis();
			for (int i = 0; i < SAMPLES; i++) {
				data[sample + 0][i] = ConvertMilliVoltToPixel(ade791x_read_v1(), range0,
				    ch0_off);
				;
			}
			for (int i = 0; i < SAMPLES; i++)
				data[sample + 1][i] = 0;
//       Serial.println(millis()-st);
		} else if (rate == 1) { // full speed, channel 1 only
//			unsigned long st = millis();
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
//			unsigned long st = millis();
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
//			unsigned long st0 = millis();
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
				tft_implementation_clear_menu();
				break;
			}
			st += r_[rate - 6];
			if (st - micros() > r_[rate - 6])
				st = micros(); // sampling rate has been changed to shorter interval
			if (!Start) {
				i--;
				continue;
			}
			//v=ade791x_read_v1();
			//Serial.println(v);
			//Serial.println(ade791x_read_v1());
			ade791x_read_v1();
			data[sample + 0][i] = ConvertMilliVoltToPixel1(ade791x_read_v1(), range0,
			    ch0_off);
			;
			if (range1 < 9)
				data[sample + 1][i] = ConvertMilliVoltToPixel2(ade791x_read_vim(),
				    range1, ch1_off);
			else
				data[sample + 1][i] = ConvertMilliVoltToPixel(ade791x_read_im(), range1,
				    ch1_off);
					
			
			//Serial.println(data[sample+0][i]);
			
			ClearAndDrawDot(i);
		}
		// Serial.println(millis()-st0);
		DrawGrid();
		//DrawText();
	} else {
		CheckSW();
	}
}
	
	if (trig_mode == TRIG_ONE)
		Start = 0;
	else
		Start = 1;
	//Serial.println(micros()-t);
	//Serial.println(updateData);
}

//-------------mini oscilloscope/end--------------//

//-------------Serial Monitor/Start---------------//
void tft_implementation_serial_monitor() {

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

bool ligitalRead(uint8_t pin) {

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
void tft_digital_pin_state_monitor_template() {
	tft.setCursor(0, 16);
	tft.setTextColor(ST7735_RED);
	tft.print(F("DIGITAL PINS"));
	tft.setCursor(0, 24);
	uint8_t pinNumber;
	tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
	for (pinNumber = 0; pinNumber < 40; pinNumber++) {   // printing digital pins

		tft.setCursor((pinNumber % 6) * 3 + (pinNumber % 6) * 24,
		    24 + (pinNumber / 6) * 8);
		if (pinNumber <= 17)
			tft.print(pinNumber + 2);
		else
			tft.print(pinNumber + 4);
		tft.print(":");
	}
}

void tft_analog_pin_state_monitor_template() {
	uint8_t pinNumber;
	tft.setCursor(0, 80);
	tft.setTextColor(ST7735_RED);
	tft.setTextWrap(0);
	tft.print(F("ANALOG PINS"));
	tft.setTextColor(ST7735_GREEN, ST7735_BLACK);
	tft.setCursor(118, 80);
	tft.print(0);
	for (pinNumber = 0; pinNumber < 16; pinNumber++) {  //printing analog pins
		tft.setCursor((pinNumber % 3) * 3 + (pinNumber % 3) * 56,
		    88 + (pinNumber / 3) * 8);
		tft.print(pinNumber + 1);
	}
}

/*Logic Analyser */
static void tft_implementation_digital_pin_state() {
	uint8_t pinNumber;
	bool j;
	tft.setTextColor(ST7735_WHITE, ST7735_BLACK);
	for (pinNumber = 0; pinNumber < 40; pinNumber++) {   // printing digital pins
		tft.setCursor(CHAR_WIDTH * 3 + (pinNumber % 6) * 3 + (pinNumber % 6) * 24,
		    24 + (pinNumber / 6) * 8);
		j = ligitalRead(digitalpinno[pinNumber]);
		tft.print(j);
	}
}

static void tft_implementation_analog_pin_state() {
	uint8_t pinNumber = 0;
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.setCursor(134, 80);
	tft.print(analogRead(pinNumber));
	tft.print("   ");
	for (pinNumber = 0; pinNumber < 16; pinNumber++) {  //printing analog pins
		tft.setCursor(14 + (pinNumber % 3) * 3 + (pinNumber % 3) * 56,
		    88 + (pinNumber / 3) * 8);
		tft.print(analogRead(pinNumber + 1));
		tft.print("   ");
	}
}

//-------------dac or function generator/start--------------//
void displayFrequenccyAmplitude() {
	//Only update on screen, if values are changed
	if (oldIncrement != increment) {
		tft.setCursor(10, 60);
		if (encoderPosition == 5)
			tft.print(F("-"));
		else
			tft.print(8.5 + 8.3 * (increment - 1));
		tft.print(F("  "));
		//   Serial.println(increment);
	}
	if (oldAmplitude != amplitude) {
		tft.setCursor(10, 90);
		if (encoderPosition == 5)
			tft.print(amplitude * 5.0);
		else
			tft.print(amplitude * 2.5);
		//   Serial.println(amplitude);
	}
}

void tft_implementation_dac_template() {
	tft.fillScreen(ST7735_BLACK);
	tft.setTextColor(ST7735_GREEN);
	tft.setCursor(10, 30);
	switch (encoderPosition + 1) {
		case 1:
			tft.print(MSG_SINE);
			break;
		case 2:
			tft.print(MSG_SQUARE);
			break;
		case 3:
			tft.print(MSG_TRIANGULAR);
			break;
		case 4:
			tft.print(MSG_SAWTOOTH_UP);
			break;
		case 5:
			tft.print(MSG_SAWTOOTH_DOWN);
			break;
		case 6:
			tft.print(MSG_ANALOG_OUT);
			break;
	}

	tft.setTextColor(ST7735_WHITE);
	tft.setCursor(10, 50);
	tft.print(F("Frequency (Hz):"));
	tft.setCursor(10, 80);
	tft.print(F("Amplitude (V):"));
	tft.setTextColor(ST7735_YELLOW, ST7735_BLACK);
	tft.setCursor(10, 60);
	if (encoderPosition + 1 == 6)
		tft.print(F("-"));
	else
		tft.print(8.5 + 8.3 * (increment - 1));
	tft.print(F("  "));
	tft.setCursor(10, 90);
	tft.print(amplitude * 2.5);
}

#endif
