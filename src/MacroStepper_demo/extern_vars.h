#ifndef VARIABLEDECLARATIONS_H
#define VARIABLEDECLARATIONS_H

#include "Arduino.h"
#include "TouchScreen.h"
#include "MCUFRIEND_kbv.h"
#include "gfxButton.h"
#include "Wire.h"
#include "fonts/Arimo_Regular_30.h"
#include "fonts/Arimo_Bold_30.h"
#include "icons/ArrowDown.h"
#include "icons/ArrowUp.h"
#include "icons/BackArrow.h"
#include "icons/Cancel.h"
#include "icons/FlashOff.h"
#include "icons/FlashOn.h"

#define	BLACK   						0x0000
#define	BLUE    						0x001F
#define	RED     						0xF800
#define	GREEN   						0x07E0
#define CYAN    						0x07FF
#define MAGENTA 						0xF81F
#define YELLOW  						0xFFE0
#define WHITE   						0xFFFF
#define GRAY    						0xE73C
#define DARKGRAY						0x39E8
#define CUSTOM_GREEN_LITE		        0x9736
#define CUSTOM_GREEN				    0x4ECC
#define CUSTOM_RED					    0xFBCC
#define CUSTOM_RED_LITE			        0xFCD1
#define CUSTOM_BLUE					    0x4EDE
#define CUSTOM_GREY					    0xCE7A
#define CUSTOM_GREY_LITE		        0xDEFB
#define CUSTOM_YELLOW                   0xFF46

// grand central M4 + 3.5" TFT
#define TS_MINX 					760
#define TS_MAXX 					315
#define TS_MINY 					852
#define TS_MAXY 					220

// grand central M4 + 2.8" TFT
// #define TS_MINX 					320
// #define TS_MAXX 					760
// #define TS_MINY 					235
// #define TS_MAXY 					810

// pin definitions for touch inputs
#define YP 			A3              // must be an analog pin, use "An" notation!
#define XM 			A2              // must be an analog pin, use "An" notation!
#define YM 			9               // can be a digital pin
#define XP 			8               // can be a digital pin
#define LCD_CS      A3              // Chip Select goes to Analog 3
#define LCD_CD      A2              // Command/Data goes to Analog 2
#define LCD_WR      A1              // LCD Write goes to Analog 1
#define LCD_RD      A0              // LCD Read goes to Analog 0
#define LCD_RESET   A4              // Can alternately just connect to Arduino's reset pin

#define microstepLength 0.3125 // distance travelled per microstep in um = 2 / 400 / 16


extern gfxButton       gfxB;
extern gfxTouch        gfxT;
extern MCUFRIEND_kbv   tft;
extern TouchScreen	    ts;

extern int xDirection;
extern int yDirection;
extern bool zState;
extern unsigned long lastNavUpdate;
#define navDelay 200
#define joystickX A14
#define joystickY A15
#define joystickZ 31

#endif
