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


// referemce to display library instance
void gfxButton::begin(MCUFRIEND_kbv &tft) {
  _tft = tft;
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
void gfxButton::drawButton(gfxButton &button, int colour) {
  if (button.shape == "drawRect") {
    _tft.drawRect(button.x, button.y, button.w, button.h, colour);
  }
  else if (button.shape == "fillRect") {
    _tft.fillRect(button.x, button.y, button.w, button.h, colour);
  }
  else if (button.shape == "drawRoundRect") {
    _tft.drawRoundRect(button.x, button.y, button.w, button.h, button.r, colour);
  }
  else if (button.shape == "fillRoundRect") {
    _tft.fillRoundRect(button.x, button.y, button.w, button.h, button.r, colour);
  }
  else if (button.shape == "drawCircle") {
    _tft.drawCircle(button.x, button.y, button.r, colour);
  }
  else if (button.shape == "fillCircle") {
    _tft.fillCircle(button.x, button.y, button.r, colour);
  }
  // TODO support triagnles
  // else if (button.shape == "drawTriangle") {
  //   _tft.drawTriangle(button.x, button.y, button.w, button.h, colour);
  // }
  // else if (button.shape == "fillTriangle") {
  //   _tft.fillTriangle(button.x, button.y, button.w, button.h, colour);
  // }
}


// draw each button based on default settings
void gfxButton::drawButtons(gfxButton &button) {
  if (button.shape == "drawRect") {
    _tft.drawRect(button.x, button.y, button.w, button.h, button.defaultColour);
  }
  else if (button.shape == "fillRect") {
    _tft.fillRect(button.x, button.y, button.w, button.h, button.defaultColour);
  }
  else if (button.shape == "drawRoundRect") {
    _tft.drawRoundRect(button.x, button.y, button.w, button.h, button.r, button.defaultColour);
  }
  else if (button.shape == "fillRoundRect") {
    _tft.fillRoundRect(button.x, button.y, button.w, button.h, button.r, button.defaultColour);
  }
  else if (button.shape == "drawCircle") {
    _tft.drawCircle(button.x, button.y, button.r, button.defaultColour);
  }
  else if (button.shape == "fillCircle") {
    _tft.fillCircle(button.x, button.y, button.r, button.defaultColour);
  }
  // TODO support triagnles
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
gfxTouch::gfxTouch(String _screen, String _name, int _xMin, int _yMin, int _xMax, int _yMax, void (*btnFunction)()) {
  screen = _screen;
  name =_name;
  xMin = _xMin;
  yMin = _yMin;
  xMax = _xMax;
  yMax = _yMax;
  btnFunc = *btnFunction;
}


// reference to TSPoint point from TouchScreen library
void gfxTouch::begin(TSPoint &point) {
  _point = point;
}


gfxTouch gfxTouch::addTouch(gfxButton &button, void (*btnFunction)(), String name, int percent) {
  _screen = button.screen;
  _name = name;
  _x = button.x;
  _y = button.y;
  _w = button.w;
  _h = button.h;
  _r = button.r;

  // get new w,h dimensions
  int _pad_w = ceil(_w * (100 + percent)/100);
  int _pad_h = ceil(_h * (100 + percent)/100);
  // offset xy position by half the difference between original dimensions and padded dimensions
  int _yMin = _y - (_pad_h - _h)/2;
  int _xMin = _x - (_pad_w - _w)/2;
  // add the padded dimensions to the new xy positions
  int _xMax = _xMin + _pad_w;
  int _yMax = _yMin + _pad_h;

  // initialise button as off
  setState(false);

  return gfxTouch(_screen, _name, _xMin, _yMin, _xMax, _yMax, *btnFunction);
}


// void gfxTouch::checkButtons(gfxTouch &button, String screen, int x, int y) {
void gfxTouch::checkButtons(String screen2, int x, int y) {
  // Serial.print("x: ");
  // Serial.println(x);
  // Serial.print("y: ");
  // Serial.println(y);

  if (screen == screen2) {
    if ((x >= xMin && x <= xMax) && (y >= yMin && y <= yMax)) {
      Serial.print("touch detected on button: ");
      Serial.println(name);

      // set button state
      setState(!getState());
      Serial.print("from lib getState: ");
      Serial.println(getState());
      // run function tied to button
      btnFunc();
    }
  }
}


// fetch current state of button
// false is off / default
// true is on / active
bool gfxTouch::getState() {
  return _btnActive;
}


// set state of button
void gfxTouch::setState(bool btnActive) {
  _btnActive = btnActive;
}
