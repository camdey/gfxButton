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
void testFunction();
void testFunction2();
#define arrayElements 10
gfxButton buttonArray[arrayElements];
gfxTouch touchArray[arrayElements];

long timer = 0;
bool buttonState = false;

gfxButton newButton = gfxB.addButton("testPage", "drawRoundRect", 100, 110, 50, 40, 5, CUSTOM_RED);
gfxButton newButton2 = gfxB.addButton("testPage", "fillRoundRect", 200, 110, 50, 40, 5, CUSTOM_RED);
gfxTouch newTouch = gfxT.addTouch(newButton, testFunction, "newButton", 20);
gfxTouch newTouch2 = gfxT.addTouch(newButton2, testFunction2, "newButton2", 20);

void setup(void) {
  Serial.begin(9600);
  tft.reset();
  uint32_t when = millis();
  if (!Serial) delay(5000);
  Serial.println("Serial took " + String((millis() - when)) + "ms to start");
  uint16_t ID = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481;
  tft.begin(ID);
  tft.fillScreen(0x0000);
  tft.setRotation(1);

  gfxB.begin(tft);
  // gfxT.begin()
  addButtons();
  drawButtons();
}


void loop() {
  if (millis() - timer >= 150) {
    buttonCheck("testPage");
    timer = millis();
    // gfxB.drawButton(newButton2, CUSTOM_GREEN);
  }
}


void addButtons() {
  // screen    x    y    w   h   roundedRect  r
  // gfxButton newButton = gfxB.addButton("testPage", "drawRoundRect", 100, 110, 50, 40, 5, CUSTOM_RED);
  // gfxButton newButton2 = gfxB.addButton("testPage", "fillRoundRect", 200, 110, 50, 40, 5, CUSTOM_RED);
  // gfxTouch newTouch = gfxT.addTouch(newButton, testFunction, "newButton", 10);
  // gfxTouch newTouch2 = gfxT.addTouch(newButton2, testFunction2, "newButton2", 10);

  Serial.print("screen: ");
  Serial.println(newTouch.screen);
  Serial.print("xMin: ");
  Serial.println(newTouch.xMin);
  Serial.print("xMax: ");
  Serial.println(newTouch.xMax);
  Serial.print("yMin: ");
  Serial.println(newTouch.yMin);
  Serial.print("yMax: ");
  Serial.println(newTouch.yMax);

  buttonArray[0] = newButton;
  buttonArray[1] = newButton2;

  touchArray[0] = newTouch;
  touchArray[1] = newTouch2;
}


void drawButtons() {
  for(int i=0; i < arrayElements; i++) {
    if (buttonArray[i].screen == "testPage") {
      gfxB.drawButtons(buttonArray[i]);
    }
  }
}


void buttonCheck(String screen) {
  TSPoint point = ts.getPoint();

  // reset pinmodes for tft
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  int touch_x = map(point.y, 937, 140, 0, 480);
  int touch_y = map(point.x, 846, 148, 0, 320);

  if (point.z >= 100 && point.z <= 1000) {
    for(int i=0; i < arrayElements; i++) {
      // gfxT.checkButtons(touchArray[i], screen, touch_x, touch_y);
      touchArray[i].checkButtons(screen, touch_x, touch_y);
    }
  }
}

void testFunction() {
  Serial.println("test function");

  buttonState = newTouch.getState();

  if (buttonState == true) {
    gfxB.drawButton(newButton, CUSTOM_GREEN);
  }
  else {gfxB.drawButton(newButton, CUSTOM_RED);}
}

void testFunction2() {
  Serial.println("test function2");

  Serial.print("from func getstate: ");
  Serial.println(newTouch2.getState());

  bool btnState = newTouch2.getState();

  if (btnState == true) {
    gfxB.drawButton(newButton2, CUSTOM_GREEN);
  }
  else {gfxB.drawButton(newButton2, CUSTOM_RED);}
}
