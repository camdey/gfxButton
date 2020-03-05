#include "Arduino.h"
#include "gfxButton.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"


// constructor
gfxButton::gfxButton() {};


// return new button object
gfxButton::gfxButton(String _screen, String _shape, int _x, int _y, int _w, int _h, int _r, int _defaultColour) {
  screen = _screen;
  shape = _shape;
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  r = _r;
  defaultColour = _defaultColour;
}


// initialise a new button
gfxButton gfxButton::addButton(String screen, String shape, int x, int y, int w, int h, int r, int defaultColour) {
  _screen = screen;
  _shape = shape;
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _r = r;
  _defaultColour = defaultColour;

  return gfxButton(_screen, _shape, _x, _y, _w, _h, _r, _defaultColour);
}


// draw a single button with a different colour
void gfxButton::drawButton(MCUFRIEND_kbv _tft, int colour) {
  if (shape == "drawRect") {
    _tft.drawRect(x, y, w, h, colour);
  }
  else if (shape == "fillRect") {
    _tft.fillRect(x, y, w, h, colour);
  }
  else if (shape == "drawRoundRect") {
    _tft.drawRoundRect(x, y, w, h, r, colour);
  }
  else if (shape == "fillRoundRect") {
    _tft.fillRoundRect(x, y, w, h, r, colour);
  }
  else if (shape == "drawCircle") {
    _tft.drawCircle(x, y, r, colour);
  }
  else if (shape == "fillCircle") {
    _tft.fillCircle(x, y, r, colour);
  }
  // TODO support triangles
  // else if (button.shape == "drawTriangle") {
  //   _tft.drawTriangle(button.x, button.y, button.w, button.h, colour);
  // }
  // else if (button.shape == "fillTriangle") {
  //   _tft.fillTriangle(button.x, button.y, button.w, button.h, colour);
  // }
}


// draw each button based on default settings
void gfxButton::drawButtons(MCUFRIEND_kbv _tft) {
  if (shape == "drawRect") {
    _tft.drawRect(x, y, w, h, defaultColour);
  }
  else if (shape == "fillRect") {
    _tft.fillRect(x, y, w, h, defaultColour);
  }
  else if (shape == "drawRoundRect") {
    _tft.drawRoundRect(x, y, w, h, r, defaultColour);
  }
  else if (shape == "fillRoundRect") {
    _tft.fillRoundRect(x, y, w, h, r, defaultColour);
  }
  else if (shape == "drawCircle") {
    _tft.drawCircle(x, y, r, defaultColour);
  }
  else if (shape == "fillCircle") {
    _tft.fillCircle(x, y, r, defaultColour);
  }
  // TODO support triangles
  // else if (button.shape == "drawTriangle") {
  //   _tft.drawTriangle(button.x, button.y, button.w, button.h, button.defaultColour);
  // }
  // else if (button.shape == "fillTriangle") {
  //   _tft.fillTriangle(button.x, button.y, button.w, button.h, button.defaultColour);
  // }
}


// constructor
gfxTouch::gfxTouch() {};


// return class object with touch perimeter for button
gfxTouch::gfxTouch(String _screen, String _name, int _xMin, int _xMax, int _yMin, int _yMax, String _btnType, void (*btnFunction)(bool state)) {
  screen = _screen;
  name =_name;
  xMin = _xMin;
  xMax = _xMax;
  yMin = _yMin;
  yMax = _yMax;
  btnType = _btnType;
  lastTouched = 0UL;
  btnFunc = *btnFunction;
}


// add toggle type button - can only change state once per button press
gfxTouch gfxTouch::addToggle(gfxButton &button, void (*btnFunction)(bool state), String name, int percent) {
  String _screen = button.screen;
  String _name = name;
  String _btnType = "toggle";

  // set xMin, xMax, yMin, yMax
  setTouchBoundary(button.x, button.y, button.w, button.h, button.r);
  // initialise button as off
  setState(false);

  return gfxTouch(_screen, _name, _xMin, _xMax, _yMin, _yMax, _btnType, *btnFunction);
}


// add momentary type button - can change state as long as your finger is held on the button
gfxTouch gfxTouch::addMomentary(gfxButton &button, void (*btnFunction)(bool state), String name, int percent) {
  String _screen = button.screen;
  String _name = name;
  String _btnType = "momentary";

  // set xMin, xMax, yMin, yMax
  setTouchBoundary(button.x, button.y, button.w, button.h, button.r);
  // initialise button as off
  setState(false);

  return gfxTouch(_screen, _name, _xMin, _xMax, _yMin, _yMax, _btnType, *btnFunction);
}


// set touch boundary for button
void gfxTouch::setTouchBoundary(int _x, int _y, int _w, int _h, int _r) {
  // if w and h dimensions are zero and radius > 0, then button is circle
  if (_w == 0 && _h == 0 && _r > 0) {
    // get new padded radius dimension
    int _pad_r = ceil(_r * (100 + percent)/100);
    // circles are drawn from the centre point
    _xMin = _x - _pad_r;
    _xMax = _x + _pad_r;
    _yMin = _y - _pad_r;
    _yMax = _y + _pad_r;
  }
  // else button must be a rectangle
  else {
    // get new w,h dimensions
    int _pad_w = ceil(_w * (100 + percent)/100);
    int _pad_h = ceil(_h * (100 + percent)/100);
    // offset xy position by half the difference between original dimensions and padded dimensions
    _yMin = _y - (_pad_h - _h)/2;
    _xMin = _x - (_pad_w - _w)/2;
    // add the padded dimensions to the new xy positions
    _xMax = _xMin + _pad_w;
    _yMax = _yMin + _pad_h;
  }
}


// check button for touch reading
void gfxTouch::checkButton(String currentScreen, int touch_x, int touch_y) {
  unsigned long currentTime = millis();

  if (btnType == "momentary") {
    if (screen == currentScreen && (currentTime - lastTouched >= _momentary_delay)) {
      if ((touch_x >= xMin && touch_x <= xMax) && (touch_y >= yMin && touch_y <= yMax)) {
        Serial.print("touch detected on button: ");
        Serial.println(name);
        lastTouched = currentTime;
        // set button state
        setState(!getState());
        // run function tied to button
        runButtonFunction();
      }
    }
  }
  else if (btnType == "toggle" && _coolOff == false) {
    if (screen == currentScreen && (currentTime - lastTouched >= _toggle_delay)) {
      if ((touch_x >= xMin && touch_x <= xMax) && (touch_y >= yMin && touch_y <= yMax)) {
        Serial.print("touch detected on button: ");
        Serial.println(name);
        lastTouched = currentTime;
        // set button state
        setState(!getState());
        // don't allow toggle again until touch pressure is zeroed
        _coolOff = true;
        // run function tied to button
        runButtonFunction();
      }
    }
  }
}


// wait for touch reading of zero before
// allowing toggle to change state again
void gfxTouch::toggleCoolOff() {
  _coolOff = false;
}


// run function attached to touch button
void gfxTouch::runButtonFunction() {
  btnFunc(getState());
}


// fetch current state of button
// false is off / default, true is on / active
bool gfxTouch::getState() {
  return _btnActive;
}


// set state of button
void gfxTouch::setState(bool btnActive) {
  _btnActive = btnActive;
}

// init global variables shared across class instances
unsigned long gfxTouch::_toggle_delay = 0;
unsigned long gfxTouch::_momentary_delay = 0;


// set debounce delay value between state changes
void gfxTouch::setToggleDebounce(unsigned long toggle_delay) {
  _toggle_delay = toggle_delay;
}


// set debounce delay value between state changes
void gfxTouch::setMomentaryDebounce(unsigned long momentary_delay) {
  _momentary_delay = momentary_delay;
}
