#include "Arduino.h"
#include "gfxButton.h"
#include "gui_control.h"
#include "gui_test_screen.h"
#include "extern_vars.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"
#include "Wire.h"

gfxButton       gfxB;
gfxTouch        gfxT;
MCUFRIEND_kbv   tft;
TouchScreen	    ts = TouchScreen(XP, YP, XM, YM, 200);

unsigned long prevButtonCheck = 0; 

void setup(void) {
  Serial.begin(250000);
  tft.reset();
  uint16_t ID = tft.readID(); //
  tft.begin(ID);
  tft.fillScreen(0x0000);
  tft.setRotation(1);


  initButtons(200, 75);
  populateScreen("Test");
}


void loop() {
  // take touch reading
  if (millis() - prevButtonCheck >= 50) {
    checkButtons(getCurrentScreen());
    prevButtonCheck = millis();
  }
}

