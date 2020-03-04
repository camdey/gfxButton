#include "gfxButton.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define	BLACK   						0x0000
#define CUSTOM_GREEN_LITE		0x9736
#define CUSTOM_GREEN				0x4ECC
#define CUSTOM_RED					0xFBCC
#define CUSTOM_RED_LITE			0xFCD1
#define CUSTOM_BLUE					0x4EDE
#define CUSTOM_GREY					0xCE7A
#define CUSTOM_GREY_LITE		0xDEFB

#define TS_MINX 					839
#define TS_MAXX 					148
#define TS_MINY 					935
#define TS_MAXY 					144

// pin definitions for touch inputs
#define YP 								A3 						// must be an analog pin, use "An" notation!
#define XM 								A2            // must be an analog pin, use "An" notation!
#define YM 								9             // can be a digital pin
#define XP 								8             // can be a digital pin

// TouchDisplay td = TouchDisplay();
gfxButton gfxB;
gfxTouch gfxT;
MCUFRIEND_kbv tft;
TouchScreen	ts = TouchScreen(XP, YP, XM, YM, 200);

void addButtons();
void drawButtons();
void buttonCheck(String screen);
void testFunction(bool btnActive);
void testFunction2(bool btnActive);
#define arrayElements 2
gfxButton buttonArray[arrayElements];
gfxTouch touchArray[arrayElements];

long timer = 0;
bool buttonState = false;

gfxButton newButton = gfxB.addButton("testPage", "drawRoundRect", 100, 110, 50, 40, 5, CUSTOM_RED);
gfxButton newButton2 = gfxB.addButton("testPage", "fillRoundRect", 200, 110, 50, 40, 5, CUSTOM_RED);
gfxTouch newTouch = gfxT.addToggle(newButton, testFunction, "newButton", 20);
gfxTouch newTouch2 = gfxT.addMomentary(newButton2, testFunction2, "newButton2", 20);


void setup(void) {
  Serial.begin(9600);
  tft.reset();
  uint16_t ID = tft.readID(); //
  tft.begin(ID);
  tft.fillScreen(0x0000);
  tft.setRotation(1);

  gfxT.setToggleDebounce(250);
  gfxT.setMomentaryDebounce(100);

  addButtons();
  drawButtons();
}


void loop() {
  if (millis() - timer >= 10) {
    buttonCheck("testPage");
    timer = millis();
  }
}


void addButtons() {
  buttonArray[0] = newButton;
  buttonArray[1] = newButton2;

  touchArray[0] = newTouch;
  touchArray[1] = newTouch2;
}


void drawButtons() {
  for(int i=0; i < arrayElements; i++) {
    if (buttonArray[i].screen == "testPage") {
      buttonArray[i].drawButtons(tft);
    }
  }
}


void buttonCheck(String currentScreen) {
  TSPoint point = ts.getPoint();

  // reset pinmodes for tft
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  int touch_x = map(point.y, 937, 140, 0, 480);
  int touch_y = map(point.x, 846, 148, 0, 320);
  int touch_z = point.z;

  if (touch_z >= 100 && touch_z <= 1000) {
    for (int i=0; i < arrayElements; i++) {
      touchArray[i].checkButton(currentScreen, touch_x, touch_y);
    }
  }
  // allow toggling button again once touch pressure zeroed
  if (touch_z == 0) {
    for (int i=0; i < arrayElements; i++) {
      if (touchArray[i].btnType == "toggle") {
        touchArray[i].toggleCoolOff();
      }
    }
  }
}

void testFunction(bool btnActive) {
  Serial.println("test function");

  // buttonState = newTouch.getState();

  if (btnActive == true) {
    newButton.drawButton(tft, CUSTOM_GREEN);
  }
  else {newButton.drawButton(tft, CUSTOM_RED);}
}

void testFunction2(bool btnActive) {
  Serial.println("test function 2");
  // bool btnActive = newTouch2.getState();
  // Serial.println(newTouch2._btnActive);

  if (btnActive == true) {
    newButton2.drawButton(tft, CUSTOM_GREEN);
  }
  else {newButton2.drawButton(tft, CUSTOM_RED);}
}
