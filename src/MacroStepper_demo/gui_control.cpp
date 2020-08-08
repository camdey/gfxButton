#include "gui_control.h"
#include "gui_test_screen.h"
#include "extern_vars.h"

using namespace test_screen;

String currentScreen = "Test"; // set current screen shown to user
int xVal = 0, yVal = 0;
bool zState = false;
void readXStick();
void readYStick();
int getDirection(int val);
int xDirection = 0;
int yDirection = 0;
unsigned long lastNavUpdate = 0;

void initButtons(unsigned long toggleDebounce, unsigned long momentaryDebounce) {
  gfxB.setBackgroundColour(BLACK);
  gfxB.setToggleDelay(toggleDebounce);
  gfxB.setMomentaryDelay(momentaryDebounce);

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


void checkTouch(String screen) {
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
      // Serial.print("touch_x: "); Serial.print(touch_x);
      // Serial.print(" | touch_y: "); Serial.println(touch_y);
      if (screen == "Test") {
        test_screen::checkTestButtons(touch_x, touch_y);
      }
    }
  }
  else if (touch_z == 0 && !zState && gfxB.isToggleActive()) {
    // if toggle active, reset flag to false when
    gfxB.setToggleActive(false);
  }
}


void checkNavigation(String screen) {
  readXStick();
  readYStick();

  if (screen == "Test" && millis() - lastNavUpdate >= navDelay) {
    test_screen::checkTestNav();
  }
}


void checkNavigationInput(String screen) {
  readZStick();
  if (screen == "Test") {
    test_screen::checkTestNavInput();
  }
  if (!zState && gfxB.isToggleActive()) {
    // if toggle active, reset flag to false when
    gfxB.setToggleActive(false);
  }
}


void readXStick() {
  xVal = analogRead(joystickX);
  xDirection = getDirection(xVal);
}

void readYStick() {
  yVal = analogRead(joystickY);
  yDirection = getDirection(yVal);
}

void readZStick() {
  zState = !digitalRead(joystickZ); // high is off/idle
}


int getDirection(int val) {
  // x left or y up
  if (val < 50) {
    return -1;
  }
  // x right or y down
  else if (val > 900) {
    return 1;
  }
  else {
    return 0;
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

