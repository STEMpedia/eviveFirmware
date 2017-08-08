//Derived from ultratft.cpp in Marlin-RC used in 3D printers
//Modified for http://evive.cc by Dhrupal R Shah and Akshat Agarwal
#include "Screen.h"

#if ENABLED(SCREEN)
//#include "language.h"
//#include "status.h"
#include "screenImplementation.h"

//#define TFT_UPDATE_INTERVAL 100
#define TFT_NUM_LINES  11
#define TFT_CLICKED (menuMove==2)

#ifndef ENCODER_STEPS_PER_MENU_ITEM
	#define ENCODER_STEPS_PER_MENU_ITEM 1
#endif

#ifndef ENCODER_PULSES_PER_STEP
	#define ENCODER_PULSES_PER_STEP 1
#endif

volatile bool DAC_ON_OFF = 0;
volatile bool OSCILLOSCOPE_ON_OFF = 0;

unsigned long lastStatusUpdateTime = 0;

typedef void (*menuFunc_t)();	// Function pointer to menu function.

static void tft_home_menu();
static void tft_control_menu();
static void tft_control_motors_menu();
static void tft_control_servos_menu();
//static void tft_control_pot_menu();
//static void tft_control_slidesw_menu();
//static void tft_control_tactilesw_menu();
static void tft_sensing_menu();
//static void tft_log_menu();
static void tft_pin_state();
static void tft_evive_oscilloscope();
static void tft_serial_select_menu();
static void tft_baud_menu();
static void tft_serial_monitor_setup();
static void tft_serial_monitor();
static void tft_pin_state_menu();
static void tft_dac_menu();
static void tft_user_def_menu();
static void tft_remove_function_menu();
static void tft_control_motor1();
static void tft_control_motor2();
static void tft_control_motor12();
static void tft_control_servo1();
static void tft_control_servo2();
static void tft_control_servo12();
static void tft_control_stepper();
static void tft_control_status();
static void tft_sensing_VV();
static void tft_sensing_VI();
static void tft_sensing_status_VV();
static void tft_sensing_status_VI();
static void tft_digital_pin_state_setup();
static void tft_analog_pin_state_setup();
static void tft_digital_pin_state();
static void tft_analog_pin_state();
static void tft_digi_ana_pin_state_setup();
static void tft_digi_ana_pin_state();
static void tft_dac_function_generator();
static void tft_touch_sensors_setup();
static void tft_touch_sensors();
static void add_user_def_fun_1();
static void add_user_def_fun_2();
static void add_user_def_fun_3();
static void add_user_def_fun_4();
static void add_user_def_fun_5();
static void actionRemove();

long baudrate[]={9600, 115200, 250000, 300,1200,2400,4800,19200,38400,57600,74880,230400};
uint8_t serialSelect;

#if ENABLED(SDSUPPORT)
	static void tft_sdcard_menu();
    static void menu_action_sdfile(const char* filename, char* longFilename);
    static void menu_action_sddirectory(const char* filename, char* longFilename);
#endif

static void menu_action_back(menuFunc_t data);
static void menu_action_submenu(menuFunc_t data);
static void menu_action_function(menuFunc_t data);
static void menu_action_setting_edit_bool(const char* pstr, bool* ptr);
static void menu_action_setting_edit_int(const char* pstr, int* ptr, int minValue, int maxValue);
static void menu_action_setting_edit_callback_int3(const char* pstr, int* ptr, int minValue, int maxValue, menuFunc_t callbackFunc);

uint8_t currentMenuViewOffset=0;              /* scroll offset in the current menu */
//moved menupress and menumove, lastKeyMoveTime to navkey.h. They are extern variables, so can be accessed.
int8_t encoderPosition;
uint8_t _menuItemNr;
menuFunc_t currentMenu = tft_home_menu; /* function pointer to the currently active menu, assgined to home menu. Default: home menu*/
uint8_t tftDrawUpdate = 2;                  /* Set to none-zero when the TFT needs to draw, decreased after every draw. 
Set to 2 in TFT routines so the TFT gets at least 1 full redraw (first redraw is partial) */
//prevMenu and prevEncoderPosition are used to store the previous menu location when editing settings.
menuFunc_t prevMenu = NULL;
uint8_t prevEncoderPosition;
//Variables used when editing values (There are more in ultratft, if ever edit menu is included)
menuFunc_t callbackFunc;

/* Helper macros for menu */
//_draw menu item is assigned values from 0 to (TFT_NUM_LINES -1), while _lineNr is the menu item numbers to be drawn
#define START_MENU() do { \
		/*Serial.print("Start encoder position: ");\
		Serial.println(encoderPosition);\
		Serial.print("Start Current menu view offset: ");\
		Serial.println(currentMenuViewOffset);*/\
    if (encoderPosition < currentMenuViewOffset) currentMenuViewOffset = encoderPosition;\
    uint8_t _lineNr = currentMenuViewOffset;\
    bool wasClicked = TFT_CLICKED; \
    for(uint8_t _drawLineNr = 0; _drawLineNr < TFT_NUM_LINES; _drawLineNr++, _lineNr++) { \
        _menuItemNr = 0;
		
#define MENU_ITEM(type, label, args...) do { \
    if (_menuItemNr == _lineNr) { \
        if (tftDrawUpdate) { \
          /*Serial.print("encoder position: ");\
          Serial.println(encoderPosition);\
          Serial.print("Current menu view offset: ");\
          Serial.println(currentMenuViewOffset);\
          Serial.print("menuItemNr: ");\
          Serial.println(_menuItemNr);\
          Serial.print("lineNr ");\
          Serial.println(_lineNr);\
          Serial.print("_drawLineNr ");\
          Serial.println(_drawLineNr);*/\
            const char* _label_pstr = PSTR(label); \
            if ((encoderPosition) == _menuItemNr) { \
            	/*Serial.print("Select Printed Menu item:");\
            	Serial.println(_menuItemNr);*/\
				      tft_implementation_text_and_background_color(ST7735_BLACK, ST7735_RED);\
				      tft_implementation_drawmenu_ ## type ## _selected (_drawLineNr, _label_pstr , ## args ); \
            }\
            else{\
            	/*Serial.print("Printed Menu item:");\
            	Serial.println(_menuItemNr);*/\
				      tft_implementation_text_and_background_color(ST7735_RED, ST7735_BLACK);\
              tft_implementation_drawmenu_ ## type (_drawLineNr, _label_pstr , ## args ); \
            }\
        }\
        if (wasClicked && (encoderPosition == _menuItemNr)) {\
					prevEncoderPosition = encoderPosition;\
          menu_action_ ## type ( args ); \
          return;\
        }\
    }\
    _menuItemNr++;\
} while(0)
#define MENU_ITEM_DUMMY() do { _menuItemNr++; } while(0)
#define MENU_ITEM_EDIT(type, label, args...) MENU_ITEM(setting_edit_ ## type, label, PSTR(label) , ## args )
#define MENU_ITEM_EDIT_CALLBACK(type, label, args...) MENU_ITEM(setting_edit_callback_ ## type, label, PSTR(label) , ## args )
#define END_MENU() \
		if (encoderPosition >= _menuItemNr) {\
      tftDrawUpdate=2; \
      encoderPosition = 0; \
      currentMenuViewOffset=0; \
      _lineNr=0;\
    }\
		else if (encoderPosition < 0) {\
    	/*Serial.print("End Else 0 encoder position: ");\
    	Serial.println(encoderPosition);*/\
      tftDrawUpdate=2; \
      encoderPosition=_menuItemNr-1; \
      currentMenuViewOffset=(encoderPosition-TFT_NUM_LINES+1>0)?encoderPosition-TFT_NUM_LINES+1:currentMenuViewOffset;\
      _lineNr=0;\
    }\
    else if (encoderPosition >= currentMenuViewOffset + TFT_NUM_LINES) { \
      currentMenuViewOffset = encoderPosition  - TFT_NUM_LINES + 1; \
      tftDrawUpdate = 2; \
      _lineNr = currentMenuViewOffset - 1; \
      _drawLineNr = -1; } \
		} } while(0)
    /*Serial.print("End encoder position: ");\
    Serial.println(encoderPosition);\
    Serial.print("End Current menu view offset: ");\
    Serial.println(currentMenuViewOffset)*/

#define	EXIT_MENU(args) back_menu_process(args)

void back_menu_process(menuFunc_t data)
{
	if(menuMove == 4)  
	{
//		tft_quick_feedback();
		menu_action_back(data);
		tft_implementation_clear_menu();
	}
}
		
/**
 * General function to go directly to a menu
 */
static void tft_goto_menu(menuFunc_t menu, const bool feedback = false, const uint32_t encoder = 0) {
  if (currentMenu != menu) {
    tft_implementation_clear_menu();
    tftDrawUpdate=2;
    currentMenu = menu;
    encoderPosition = encoder;
  }
}
//See function tft_status_screen() for examples of how to handle pages without any menus on them

static void tft_returnto_home()	{tft_goto_menu(tft_home_menu);}
	
void tft_update(){			//will be called always in loop
	navKeyUpdate();       //Return values as per navigation key is pressed/move or not (This will update menuMove and menuPress)
	if (menuMove != 0 || menuPress != 0){
		tftDrawUpdate = 1;
		
		if (menuPress == 1)
		{	tft_implementation_clear_menu();
			currentMenu = tft_home_menu;
			encoderPosition = 0;
			actionRemoveAll();
		}
		else if(menuMove == 3)
			encoderPosition++;
		else if(menuMove == 1){
			if(encoderPosition >= 0)
				encoderPosition--;
			if(encoderPosition < 0)
				encoderPosition=_menuItemNr-1;
		}

		
	}
    (*currentMenu)();	
    //if (tftDrawUpdate == 2)
    //    tft_implementation_clear_menu();					//implement in tft implementation
    if (tftDrawUpdate)
        tftDrawUpdate--;
    if (millis()>lastStatusUpdateTime+MIN_TIME2)
    {
    	batteryUpdate();
    	vvrUpdate();
    	lastStatusUpdateTime =millis();
    }
}

/*
*"Home" menu
*/
static void tft_home_menu(){
	START_MENU();
	MENU_ITEM(submenu, MSG_CONTROL, tft_control_menu);
	MENU_ITEM(submenu, MSG_SENSING, tft_sensing_menu);
	MENU_ITEM(function, MSG_OSCILLOSCOPE, tft_evive_oscilloscope);
	MENU_ITEM(submenu, MSG_SERIAL_MONITOR, tft_serial_select_menu);
  MENU_ITEM(submenu, MSG_PIN_STATE, tft_pin_state_menu);
  MENU_ITEM(submenu, MSG_DAC, tft_dac_menu);
  MENU_ITEM(function, MSG_CAP_TOUCH, tft_touch_sensors_setup);
  MENU_ITEM(submenu, MSG_USER_DEF, tft_user_def_menu);
//  MENU_ITEM(submenu, MSG_REMOVE_FUNCTION, tft_remove_function_menu);
	//add menu
  END_MENU();
}
	
static void tft_control_menu(){
	START_MENU();
	MENU_ITEM(submenu, MSG_CONTROL_MOTOR, tft_control_motors_menu);
	MENU_ITEM(submenu, MSG_CONTROL_SERVO, tft_control_servos_menu);
	MENU_ITEM(function, MSG_CONTROL_STEPPER_MOTOR, tft_control_stepper);
    END_MENU();	
	EXIT_MENU(tft_home_menu);
}

static void tft_control_motors_menu(){
	START_MENU();
	MENU_ITEM(function, MSG_CONTROL_MOTOR1, tft_control_motor1 );
	MENU_ITEM(function, MSG_CONTROL_MOTOR2, tft_control_motor2 );
	MENU_ITEM(function, MSG_CONTROL_MOTOR12, tft_control_motor12 );
	END_MENU();
	EXIT_MENU(tft_control_menu);
}

static void tft_control_motor1(){
	addMotor1();
	tft_control_status_template();
	currentMenu = tft_control_status;
		//add this function to list of active functions
	//tft_implementation_ ..... ()				//display motors and servo	
}

static void tft_control_motor2(){
	addMotor2();
	tft_control_status_template();
	currentMenu = tft_control_status;
	//add this function to list of active functions
	//tft_implementation_ ..... ()				//display motors and servo
}

static void tft_control_motor12(){
	addMotor12();
	tft_control_status_template();
	currentMenu = tft_control_status;
	//add this function to list of active functions
	//tft_implementation_ ..... ()				//display motors and servo	
}

static void tft_control_servos_menu(){
	START_MENU();
	MENU_ITEM(function, MSG_CONTROL_SERVO1, tft_control_servo1 );
	MENU_ITEM(function, MSG_CONTROL_SERVO2, tft_control_servo2 );
	MENU_ITEM(function, MSG_CONTROL_SERVO12, tft_control_servo12 );
	END_MENU();
	EXIT_MENU(tft_control_menu);
}

static void tft_control_servo1(){
	addServo1();
	tft_control_status_template();
	currentMenu = tft_control_status;
	//add this function to list of active functions
	//tft_implementation_ ..... ()				//display motors and servo
}

static void tft_control_servo2(){
	addServo2();
	tft_control_status_template();
	currentMenu = tft_control_status;
	//add this function to list of active functions
	//tft_implementation_ ..... ()				//display motors and servo
}

static void tft_control_servo12(){
	addServo12();
	tft_control_status_template();
	currentMenu = tft_control_status;
	//add this function to list of active functions
	//tft_implementation_ ..... ()				//display motors and servo
}

static void tft_control_stepper(){
	addStepper();
	tft_control_status_template();
	currentMenu = tft_control_status;
	//tft_implementation_ ..... ()				//display motors and servo
}

static void tft_control_status(){
	if(_MOTOR1_EN)	tft_implementation_control_status_motor(0);
	else if(_SERVO1_EN)	tft_implementation_control_status_servo(0);
	if(_MOTOR2_EN)	tft_implementation_control_status_motor(1);
	else if(_SERVO2_EN)	tft_implementation_control_status_servo(1);
	if(_STEPPER_EN)	tft_implementation_control_status_stepper();
	back_menu_process(tft_control_menu);
}

static void tft_sensing_menu(){
	START_MENU();
	MENU_ITEM(function, MSG_SENSING_PROBE_VV, tft_sensing_VV );
	MENU_ITEM(function, MSG_SENSING_PROBE_VI, tft_sensing_VI );
	END_MENU();
	EXIT_MENU(tft_control_menu);
}

static void tft_sensing_VV(){
	tft_sensing_status_template(0);
	currentMenu=tft_sensing_status_VV;
}

static void tft_sensing_status_VV(){
	tft_implementation_sensing_status(0);
}

static void tft_sensing_VI(){
	tft_sensing_status_template(1);
	currentMenu=tft_sensing_status_VI;
}

static void tft_sensing_status_VI(){
	tft_implementation_sensing_status(1);
}

static void tft_evive_oscilloscope(){
  evive_oscilloscope();
  navKeyDettachInterruptMenuPress();
  tft_implementation_clear_full();
  delay(MIN_TIME2);
  drawStatusBar();
  tftDrawUpdate = 2;
}

static void tft_serial_select_menu(){
  START_MENU();
  MENU_ITEM(submenu, MSG_SERIAL0, tft_baud_menu);
  MENU_ITEM(submenu, MSG_SERIAL2, tft_baud_menu);
  MENU_ITEM(submenu, MSG_SERIAL3, tft_baud_menu);
  END_MENU();
  EXIT_MENU(tft_home_menu);
}

static void tft_baud_menu(){
  serialSelect = prevEncoderPosition;
#ifdef __DEBUG__
	Serial.println(serialSelect);
#endif
	START_MENU();
  MENU_ITEM(function, MSG_BAUD_9600, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_115200, tft_serial_monitor_setup);
	MENU_ITEM(function, MSG_BAUD_250000, tft_serial_monitor_setup);
	MENU_ITEM(function, MSG_BAUD_300, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_1200, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_2400, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_4800, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_19200, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_38400, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_57600, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_74880, tft_serial_monitor_setup);
  MENU_ITEM(function, MSG_BAUD_230400, tft_serial_monitor_setup);
  END_MENU();
  EXIT_MENU(tft_serial_monitor);
}

static void tft_serial_monitor_setup(){
//  currentMenu = tft_baud_menu;
#ifdef __DEBUG__
	Serial.println(encoderPosition);
#endif
	tft_implementation_clear_menu();
  serialObject.Initalise(baudrate[encoderPosition], serialSelect);
  currentMenu = tft_serial_monitor;
}

static void tft_serial_monitor(){
	tft_implementation_serial_monitor();
	back_menu_process(tft_serial_select_menu);
}

//static void tft_log_menu(){
//	//add code here
//}

/*Logic analyser */
static void tft_pin_state_menu(){
  START_MENU();
  MENU_ITEM(function, MSG_DIGITAL_PIN_STATE, tft_digital_pin_state_setup);
  MENU_ITEM(function, MSG_ANALOG_PIN_STATE, tft_analog_pin_state_setup);
  MENU_ITEM(function, MSG_DIGI_ANA_PIN_STATE, tft_digi_ana_pin_state_setup);
  END_MENU();
  EXIT_MENU(tft_home_menu);
}

static void tft_digital_pin_state_setup(){
	tft_implementation_clear_menu();
  tft_digital_pin_state_monitor_template();
  currentMenu = tft_digital_pin_state;
}

static void tft_analog_pin_state_setup(){
	tft_implementation_clear_menu();
  tft_analog_pin_state_monitor_template();
  currentMenu = tft_analog_pin_state;
}

static void tft_digi_ana_pin_state_setup(){
	tft_implementation_clear_menu();
	tft_digital_pin_state_monitor_template();
	tft_analog_pin_state_monitor_template();
	currentMenu = tft_digi_ana_pin_state;
}

static void tft_digital_pin_state(){
	tft_implementation_digital_pin_state();
	back_menu_process(tft_pin_state_menu);
}

static void tft_analog_pin_state(){
	tft_implementation_analog_pin_state();
	back_menu_process(tft_pin_state_menu);
}

static void tft_digi_ana_pin_state(){
	tft_implementation_digital_pin_state();
	tft_implementation_analog_pin_state();
	back_menu_process(tft_pin_state_menu);
}

static void tft_dac_menu(){
	START_MENU();
	MENU_ITEM(function, MSG_SINE, tft_dac_function_generator );
	MENU_ITEM(function, MSG_SQUARE, tft_dac_function_generator );
	MENU_ITEM(function, MSG_TRIANGULAR, tft_dac_function_generator );
	MENU_ITEM(function, MSG_SAWTOOTH_UP, tft_dac_function_generator );
	MENU_ITEM(function, MSG_SAWTOOTH_DOWN, tft_dac_function_generator );
	MENU_ITEM(function, MSG_ANALOG_OUT, tft_dac_function_generator );
	END_MENU();
	EXIT_MENU(tft_home_menu);
}

static void tft_dac_function_generator(){
	currentMenu = tft_dac_menu;
	Serial.println(encoderPosition);
	navKeyAttachInterruptMenuPress();

	dac.begin(MCP4725_ADDR);
  /*Speed up ADC*/
  // set up the ADC
  ADCSRA &= ~PS_128;  // remove bits set by Arduino library
  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_32;    // set our own prescaler to 64

	setFrequencyAmplitude();
	tft_implementation_dac_template();

  DAC_ON_OFF = 1;

	while(DAC_ON_OFF){
		setFrequencyAmplitude();
		displayFrequenccyAmplitude();
		switch(encoderPosition+1){
			case 1:
				generateSineWave();
				break;
			case 2:
				generateSquareWave();
				break;
			case 3:
				generateTraingularWave();
				break;
			case 4:
				generateSawtoothWaveUp();
				break;
			case 5:
				generateSawtoothWaveDown();
				break;
			case 6:
				generateAnalogOutput();
				break;
		}
	}
	navKeyDettachInterruptMenuPress();
	tft_implementation_clear_full();
  /*Normal Speed ADC*/
  // set up the ADC
  ADCSRA &= ~PS_32;  // remove bits set to speed up ADC
  // you can choose a prescaler from above.
  // PS_16, PS_32, PS_64 or PS_128
  ADCSRA |= PS_128;    // set prescaler to 128 as set by Arduino library
  delay(MIN_TIME5);
  drawStatusBar();
  tftDrawUpdate = 2;
}

void navKeyInterruptCenterPress(){
	DAC_ON_OFF = 0;
	OSCILLOSCOPE_ON_OFF = 0;
//	Serial.println("Dettached Interrupt");
}

// Keeps track of the last pins touched
// so we know when buttons are 'released'
uint16_t lasttouched = 0;
uint16_t currtouched = 0;

static void tft_touch_sensors_setup(){
	tft_implementation_clear_menu();
	tft.setCursor(40, TOP_MARGIN);
	tft.setTextColor(ST7735_CYAN, ST7735_BLACK);
	tft.println("Touch Sensors");
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  // Default address is 0x5A, if tied to 3.3V its 0x5B
  // If tied to SDA its 0x5C and if SCL then 0x5D
  if (!cap.begin(0x5A)) {
  	tft.print("ERROR");
    Serial.println("MPR121 not found, check wiring?");
    return;
  }
  Serial.println("MPR121 found!");
  currentMenu = tft_touch_sensors;
}

static void tft_touch_sensors(){
    // put your user defined (custom) code here, to run repeatedly:
    currtouched = cap.touched();

    for (uint8_t i=0; i<12; i++) {
      // it if *is* touched and *wasnt* touched before, alert!
      if ((currtouched & _BV(i)) && !(lasttouched & _BV(i)) ) {
        Serial.print(i); Serial.println(" touched");
        tft.setCursor(i*7+(i/10)*8,50);
        tft.print(i+1);
        tone(BUZZER,200+100*i,200);
      }
      // if it *was* touched and now *isnt*, alert!
      if (!(currtouched & _BV(i)) && (lasttouched & _BV(i)) ) {
        Serial.print(i); Serial.println(" released");
        //tft.setCursor(i*10,100);
        tft.fillRect(i*7+(i/10)*7,50, 7+((i+1)/10)*7, 7, ST7735_BLACK);
      }
    }

    // reset our state
    lasttouched = currtouched;

    // comment out this line for detailed data from the sensor!
    //return;

    // debugging info, what
#ifdef __DEBUG__
    Serial.print("\t\t\t\t\t\t\t\t\t\t\t\t\t 0x"); Serial.println(cap.touched(), HEX);
    Serial.print("Filt: ");
    for (uint8_t i=0; i<12; i++) {
      Serial.print(cap.filteredData(i)); Serial.print("\t");
    }
    Serial.println();
    Serial.print("Base: ");
    for (uint8_t i=0; i<12; i++) {
      Serial.print(cap.baselineData(i)); Serial.print("\t");
    }
    Serial.println();
#endif
    // put a delay so it isn't overwhelming
    delay(100);
    back_menu_process(tft_home_menu);
}

static void tft_user_def_menu(){
	if(tftDrawUpdate){
		actionRemoveAll();
		//tft_implementation_clear_menu();
	}
	START_MENU();
	#ifdef USER_DEFINED_FUNCTION_1
		MENU_ITEM(function, USER_DEFINED_FUNCTION_1, add_user_def_fun_1 );
	#endif
	#ifdef USER_DEFINED_FUNCTION_2
		MENU_ITEM(function, USER_DEFINED_FUNCTION_2, add_user_def_fun_2 );
	#endif
	#ifdef USER_DEFINED_FUNCTION_3
		MENU_ITEM(function, USER_DEFINED_FUNCTION_3, add_user_def_fun_3 );
	#endif
	#ifdef USER_DEFINED_FUNCTION_4
		MENU_ITEM(function, USER_DEFINED_FUNCTION_4, add_user_def_fun_4 );
	#endif
	#ifdef USER_DEFINED_FUNCTION_5
		MENU_ITEM(function, USER_DEFINED_FUNCTION_5, add_user_def_fun_5 );
	#endif	

	END_MENU();
	EXIT_MENU(tft_home_menu);
}

static void add_user_def_fun_1(){
	add_user_def_fun(1);
	remove_other_user_def_fun(1);
}

static void add_user_def_fun_2(){
	add_user_def_fun(2);
	remove_other_user_def_fun(2);
}

static void add_user_def_fun_3(){
	add_user_def_fun(3);
	remove_other_user_def_fun(3);
}

static void add_user_def_fun_4(){
	add_user_def_fun(4);
	remove_other_user_def_fun(4);
}

static void add_user_def_fun_5(){
	add_user_def_fun(5);
	remove_other_user_def_fun(5);
}

/* static void tft_remove_function_menu(){
//	START_MENU();
//	for(uint8_t i = 0; i < actionFuncListNum; i++)
//		MENU_ITEM(function, actionFuncList[i], actionRemove);
//	END_MENU();
//	EXIT_MENU(tft_home_menu);
}

static void actionRemove(){
	actionRemove(encoderPosition+1);
} */


/**
There are certain #defines for menu_edit type entries, if we end up including those in our code, include the #defines near line 1326
*/
/**
*Menu actions
*/
static void menu_action_back(menuFunc_t func) { tft_goto_menu(func); }
static void menu_action_submenu(menuFunc_t func) { tft_goto_menu(func); }
static void menu_action_function(menuFunc_t func) { (*func)(); }

#if ENABLED(SDSUPPORT)

  static void menu_action_sdfile(const char* filename, char* longFilename) {
    char cmd[30];
    char* c;
    sprintf_P(cmd, PSTR("M23 %s"), filename);
    for (c = &cmd[4]; *c; c++) *c = tolower(*c);
    enqueuecommand(cmd);
    enqueuecommands_P(PSTR("M24"));
    tft_return_to_status();
  }

  static void menu_action_sddirectory(const char* filename, char* longFilename) {
    card.chdir(filename);
    encoderPosition = 0;
  }

#endif //SDSUPPORT

static void menu_action_setting_edit_bool(const char* pstr, bool* ptr) { *ptr = !(*ptr); }
static void menu_action_setting_edit_callback_bool(const char* pstr, bool* ptr, menuFunc_t callback) {
  menu_action_setting_edit_bool(pstr, ptr);
  (*callback)();
}

//Put a #define SCREENOFF which turns off all screen initialisations and everything for like a battery saver application
bool tft_clicked() { return TFT_CLICKED; }

void tft_init(){
//#ifdef __DEEBUG__
	Serial.println("Setup loop ends");
//#endif
	pinMode(TFT_CS,OUTPUT);
	tft_implementation_init();
}
/*********************************/
/** Number to string conversion **/
/*********************************/

char conv[8];

// Convert float to rj string with 123 or -12 format
char *ftostr3(const float& x) { return itostr3((int)x); }

// Convert float to rj string with _123, -123, _-12, or __-1 format
char *ftostr4sign(const float& x) { return itostr4sign((int)x); }

// Convert int to string with 12 format
char* itostr2(const uint8_t& x) {
  //sprintf(conv,"%5.1f",x);
  int xx = x;
  conv[0] = (xx / 10) % 10 + '0';
  conv[1] = xx % 10 + '0';
  conv[2] = 0;
  return conv;
}

// Convert float to string with +123.4 format
char* ftostr31(const float& x) {
  int xx = abs(x * 10);
  conv[0] = (x >= 0) ? '+' : '-';
  conv[1] = (xx / 1000) % 10 + '0';
  conv[2] = (xx / 100) % 10 + '0';
  conv[3] = (xx / 10) % 10 + '0';
  conv[4] = '.';
  conv[5] = xx % 10 + '0';
  conv[6] = 0;
  return conv;
}

// Convert float to string with 123.4 format, dropping sign
char* ftostr31ns(const float& x) {
  int xx = abs(x * 10);
  conv[0] = (xx / 1000) % 10 + '0';
  conv[1] = (xx / 100) % 10 + '0';
  conv[2] = (xx / 10) % 10 + '0';
  conv[3] = '.';
  conv[4] = xx % 10 + '0';
  conv[5] = 0;
  return conv;
}

// Convert float to string with 123.45 format
char *ftostr32(const float& x) {
  long xx = abs(x * 100);
  conv[0] = x >= 0 ? (xx / 10000) % 10 + '0' : '-';
  conv[1] = (xx / 1000) % 10 + '0';
  conv[2] = (xx / 100) % 10 + '0';
  conv[3] = '.';
  conv[4] = (xx / 10) % 10 + '0';
  conv[5] = xx % 10 + '0';
  conv[6] = 0;
  return conv;
}

// Convert float to string with 1.234 format
char* ftostr43(const float& x) {
  long xx = x * 1000;
  if (xx >= 0)
    conv[0] = (xx / 1000) % 10 + '0';
  else
    conv[0] = '-';
  xx = abs(xx);
  conv[1] = '.';
  conv[2] = (xx / 100) % 10 + '0';
  conv[3] = (xx / 10) % 10 + '0';
  conv[4] = (xx) % 10 + '0';
  conv[5] = 0;
  return conv;
}

// Convert float to string with 1.23 format
char* ftostr12ns(const float& x) {
  long xx = x * 100;
  xx = abs(xx);
  conv[0] = (xx / 100) % 10 + '0';
  conv[1] = '.';
  conv[2] = (xx / 10) % 10 + '0';
  conv[3] = (xx) % 10 + '0';
  conv[4] = 0;
  return conv;
}

// Convert float to space-padded string with -_23.4_ format
char* ftostr32sp(const float& x) {
  long xx = abs(x * 100);
  uint8_t dig;
  if (x < 0) { // negative val = -_0
    conv[0] = '-';
    dig = (xx / 1000) % 10;
    conv[1] = dig ? '0' + dig : ' ';
  }
  else { // positive val = __0
    dig = (xx / 10000) % 10;
    if (dig) {
      conv[0] = '0' + dig;
      conv[1] = '0' + (xx / 1000) % 10;
    }
    else {
      conv[0] = ' ';
      dig = (xx / 1000) % 10;
      conv[1] = dig ? '0' + dig : ' ';
    }
  }

  conv[2] = '0' + (xx / 100) % 10; // lsd always

  dig = xx % 10;
  if (dig) { // 2 decimal places
    conv[5] = '0' + dig;
    conv[4] = '0' + (xx / 10) % 10;
    conv[3] = '.';
  }
  else { // 1 or 0 decimal place
    dig = (xx / 10) % 10;
    if (dig) {
      conv[4] = '0' + dig;
      conv[3] = '.';
    }
    else {
      conv[3] = conv[4] = ' ';
    }
    conv[5] = ' ';
  }
  conv[6] = '\0';
  return conv;
}

// Convert int to lj string with +123.0 format
char* itostr31(const int& x) {
  conv[0] = x >= 0 ? '+' : '-';
  int xx = abs(x);
  conv[1] = (xx / 100) % 10 + '0';
  conv[2] = (xx / 10) % 10 + '0';
  conv[3] = xx % 10 + '0';
  conv[4] = '.';
  conv[5] = '0';
  conv[6] = 0;
  return conv;
}

// Convert int to rj string with 123 or -12 format
char* itostr3(const int& x) {
  int xx = x;
  if (xx < 0) {
    conv[0] = '-';
    xx = -xx;
  }
  else
    conv[0] = xx >= 100 ? (xx / 100) % 10 + '0' : ' ';

  conv[1] = xx >= 10 ? (xx / 10) % 10 + '0' : ' ';
  conv[2] = xx % 10 + '0';
  conv[3] = 0;
  return conv;
}

// Convert int to lj string with 123 format
char* itostr3left(const int& xx) {
  if (xx >= 100) {
    conv[0] = (xx / 100) % 10 + '0';
    conv[1] = (xx / 10) % 10 + '0';
    conv[2] = xx % 10 + '0';
    conv[3] = 0;
  }
  else if (xx >= 10) {
    conv[0] = (xx / 10) % 10 + '0';
    conv[1] = xx % 10 + '0';
    conv[2] = 0;
  }
  else {
    conv[0] = xx % 10 + '0';
    conv[1] = 0;
  }
  return conv;
}

// Convert int to rj string with 1234 format
char* itostr4(const int& xx) {
  conv[0] = xx >= 1000 ? (xx / 1000) % 10 + '0' : ' ';
  conv[1] = xx >= 100 ? (xx / 100) % 10 + '0' : ' ';
  conv[2] = xx >= 10 ? (xx / 10) % 10 + '0' : ' ';
  conv[3] = xx % 10 + '0';
  conv[4] = 0;
  return conv;
}

// Convert int to rj string with _123, -123, _-12, or __-1 format
char *itostr4sign(const int& x) {
  int xx = abs(x);
  int sign = 0;
  if (xx >= 100) {
    conv[1] = (xx / 100) % 10 + '0';
    conv[2] = (xx / 10) % 10 + '0';
  }
  else if (xx >= 10) {
    conv[0] = ' ';
    sign = 1;
    conv[2] = (xx / 10) % 10 + '0';
  }
  else {
    conv[0] = ' ';
    conv[1] = ' ';
    sign = 2;
  }
  conv[sign] = x < 0 ? '-' : ' ';
  conv[3] = xx % 10 + '0';
  conv[4] = 0;
  return conv;
}

// Convert float to rj string with 12345 format
char* ftostr5(const float& x) {
  long xx = abs(x);
  conv[0] = xx >= 10000 ? (xx / 10000) % 10 + '0' : ' ';
  conv[1] = xx >= 1000 ? (xx / 1000) % 10 + '0' : ' ';
  conv[2] = xx >= 100 ? (xx / 100) % 10 + '0' : ' ';
  conv[3] = xx >= 10 ? (xx / 10) % 10 + '0' : ' ';
  conv[4] = xx % 10 + '0';
  conv[5] = 0;
  return conv;
}

// Convert float to string with +1234.5 format
char* ftostr51(const float& x) {
  long xx = abs(x * 10);
  conv[0] = (x >= 0) ? '+' : '-';
  conv[1] = (xx / 10000) % 10 + '0';
  conv[2] = (xx / 1000) % 10 + '0';
  conv[3] = (xx / 100) % 10 + '0';
  conv[4] = (xx / 10) % 10 + '0';
  conv[5] = '.';
  conv[6] = xx % 10 + '0';
  conv[7] = 0;
  return conv;
}

// Convert float to string with +123.45 format
char* ftostr52(const float& x) {
  conv[0] = (x >= 0) ? '+' : '-';
  long xx = abs(x * 100);
  conv[1] = (xx / 10000) % 10 + '0';
  conv[2] = (xx / 1000) % 10 + '0';
  conv[3] = (xx / 100) % 10 + '0';
  conv[4] = '.';
  conv[5] = (xx / 10) % 10 + '0';
  conv[6] = xx % 10 + '0';
  conv[7] = 0;
  return conv;
}

#endif	//SCREEN
