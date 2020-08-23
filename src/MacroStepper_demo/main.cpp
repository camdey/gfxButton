#include "Arduino.h"
#include "gfxButton.h"
#include "gui_control.h"
#include "gui_test_screen.h"
#include "extern_vars.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"
#include "Wire.h"

gfxButton       btn;
MCUFRIEND_kbv   tft;
TouchScreen	    ts = TouchScreen(XP, YP, XM, YM, 200);

unsigned long prevButtonCheck = 0;
unsigned long prevJoystickCheck = 0;


void setup(void) {
  Serial.begin(250000);
  tft.reset();
  uint16_t ID = tft.readID(); //
  tft.begin(ID);
  tft.fillScreen(0x0000);
  tft.setRotation(1);

  pinMode(joystickZ, INPUT_PULLUP);
  btn.begin(&tft);
  btn.setScreenSize(480, 320);
  initButtons(200, 75);
  // populateScreen("Test");
  populateScreen("Calc");
}

// todo delay between joystick inputs?
// todo delay between navigation movements


void loop() {
  // take touch reading
  if (millis() - prevButtonCheck >= 100) {
    checkTouch(getCurrentScreen());
    checkNavigation(getCurrentScreen());
    prevButtonCheck = millis();
  }
  if (millis() - prevJoystickCheck >= 50) {
    checkNavigationInput(getCurrentScreen());
    prevJoystickCheck = millis();
  }
}
