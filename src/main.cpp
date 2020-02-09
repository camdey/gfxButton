#include "gfxButton.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define	BLACK   						0x0000
#define CUSTOM_RED          0xFBCC

#define TS_MINX 					316
#define TS_MAXX 					762
#define TS_MINY 					242
#define TS_MAXY 					805

// pin definitions for touch inputs
#define YP 								A3 						// must be an analog pin, use "An" notation!
#define XM 								A2            // must be an analog pin, use "An" notation!
#define YM 								9             // can be a digital pin
#define XP 								8             // can be a digital pin

// TouchDisplay td = TouchDisplay();
gfxButton gfxB;
gfxTouch gfxT;
MCUFRIEND_kbv tft;
TouchScreen	ts = TouchScreen(XP, YP, XM, YM, 300);

void addButtons();
void drawButtons();
#define arrayElements 10
gfxButton buttonArray[arrayElements];

long timer;

void setup(void) {
  Serial.begin(9600);
  uint32_t when = millis();
  //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
  if (!Serial) delay(5000);           //allow some time for Leonardo
  Serial.println("Serial took " + String((millis() - when)) + "ms to start");
  //    tft.reset();                 //hardware reset
  uint16_t ID = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  //    ID = 0x9329;                             // force ID
  tft.begin(ID);
  tft.fillScreen(0x0000);

  gfxB.begin(tft);
  // gfxT.begin()
  addButtons();
  drawButtons();

  timer = millis();
}


void loop() {
  if (millis() - timer >= 10) {
    TSPoint point = ts.getPoint();

    timer = millis();
  }
}


void addButtons() {
  // screen    x    y    w   h   roundedRect  r
  gfxButton newButton = gfxB.addButton("testPage", "drawRoundRect", 100, 110, 50, 40, 5, CUSTOM_RED);
  gfxButton newButton2 = gfxB.addButton("testPage", "fillRoundRect", 200, 110, 50, 40, 5, CUSTOM_RED);

  buttonArray[0] = newButton;
  buttonArray[1] = newButton2;

  gfxT.setTouchBoundary(newButton);
}


void drawButtons() {
  for(int i=0; i < arrayElements; i++) {
    if (buttonArray[i].screen == "testPage") {
      gfxB.drawButtons(buttonArray[i]);
    }
  }
}
