#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define SENSING

#define SCREEN

/* DEBUG MODE: comment this line to disable debugging messages over serial console*/
//#define __DEBUG__

#define BAUDRATE 250000
#define SERIAL_TIME_OUT 10

//Comment (uncomment) based on the Screen Tab type of TFT Display, ie BLACKTAB or GREENTAB
//Identify TFT, if you get Red color in place of Blue or vice versa.
#define SCREEN_TAB INITR_GREENTAB
//#define SCREEN_TAB INITR_BLACKTAB


//////////macros////////////////
// Macros to support option testing
#define _CAT(a, ...) a ## __VA_ARGS__
#define SWITCH	_ENABLED_0 0
#define SWITCH_ENABLED_1 1
#define SWITCH_ENABLED_  1
#define ENABLED(b) _CAT(SWITCH_ENABLED_, b)
#define DISABLED(b) (!_CAT(SWITCH_ENABLED_, b))

//Min time between simultaneous process
#define MIN_TIME1 	100
#define MIN_TIME1_5 150
#define MIN_TIME2 	200
#define MIN_TIME3 	300
#define MIN_TIME5 	500

// Macros for bit masks
#define BIT(b) (1<<(b))
#define TEST(n,b) (((n)&BIT(b))!=0)
#define SET_BIT(n,b,value) (n) ^= ((-value)^(n)) & (BIT(b))

// Macros for maths shortcuts
#define RADIANS(d) ((d)*M_PI/180.0)
#define DEGREES(r) ((r)*180.0/M_PI)

#define COUNT(a) (sizeof(a)/sizeof(*a))

// Define various ADC prescaler (Used to speed up ADC read action)
const unsigned char PS_16 = (1 << ADPS2);
const unsigned char PS_32 = (1 << ADPS2) | (1 << ADPS0);
const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

#endif

