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
gfxTouch::gfxTouch(String _screen, String _name, int _xMin, int _yMin, int _xMax, int _yMax, void (*btnFunction)(bool state)) {
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


gfxTouch gfxTouch::addTouch(gfxButton &button, void (*btnFunction)(bool state), String name, int percent) {
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


void gfxTouch::checkButtons(String s, int x, int y) {
  if (screen == s) {
    if ((x >= xMin && x <= xMax) && (y >= yMin && y <= yMax)) {
      Serial.print("touch detected on button: ");
      Serial.println(name);

      // set button state
      setState(!getState());

      // run function tied to button
      runFunction();
    }
  }
}


void gfxTouch::runFunction() {
  btnFunc(getState());
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
