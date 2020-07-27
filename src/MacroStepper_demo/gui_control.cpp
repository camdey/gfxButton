#include "gui_control.h"
#include "gui_test_screen.h"
#include "extern_vars.h"

using namespace test_screen;
String currentScreen = "Test"; // set current screen shown to user

void initButtons(unsigned long toggleDebounce, unsigned long momentaryDebounce) {
  gfxB.setBackgroundColour(BLACK);
  gfxT.setToggleDebounce(toggleDebounce);
  gfxT.setMomentaryDebounce(momentaryDebounce);

  initTestButtons();
}


void populateScreen(String screen) {
  tft.fillScreen(BLACK);
  delay(20); // see if this solves the superimposition of two different screens
  tft.fillScreen(BLACK);
  if (screen == "Test") {
    populateTestScreen();
  }
}


void checkButtons(String screen) {
  TSPoint point = ts.getPoint();

  // reset pinModes for tft (otherwise can't draw!)
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  int touch_x;
  int touch_y;
  int touch_z = point.z;

  touch_x = map(point.y, TS_MINY, TS_MAXY, 0, tft.width());
  touch_y = map(point.x, TS_MINX, TS_MAXX, 0, tft.height());

  
  if (touch_z >= 50 && touch_z <= 1000) {
    if ((touch_x > 0 && touch_x <= tft.width()) && (touch_y > 0 && touch_y <= tft.height())) {
      if (screen == "Test") {
        checkTestButtons(touch_x, touch_y);
      }
    }
  }
  else if (touch_z == 0 && gfxT.getToggleFlag()) {
    // if toggle active, reset flag to false when
    // no touch is recorded
    gfxT.setToggleFlag(false);
  }
}


// Set the current screen displayed to the user
void setCurrentScreen(String screen) {
  currentScreen = screen;
}


// Get the current screen displayed to the user
String getCurrentScreen() {
  return currentScreen;
}

