#include "Arduino.h"
#include "gfxButton.h"
#include "Adafruit_GFX.h"
#include "SPI.h"

gfxButton::gfxButton(int _x, int _y, int _w, int _h, bool _roundedRect, int _radius) {
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  roundedRect = _roundedRect;
  radius = _radius;
}


// gfxButton::getAttributes() {
//   _page = page;
//   _action = action;
//   _touchPadding = touchPadding;
//   _touchIndicator = touchIndicator;
//   _buttonName = buttonName;
// }
//
//
// gfxButton::setAttributes(String buttonName, String page, String action, String touchPadding, String touch_indicator) {
//   _page = page;
//   _action = action;
//   _touchPadding = touchPadding;
//   _touchIndicator = touchIndicator;
//   _buttonName = buttonName;
// }

TouchDisplay::TouchDisplay() {};


gfxButton TouchDisplay::initButton(int x, int y, int w, int h, bool roundedRect, int radius) {
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _roundedRect = roundedRect;
  _radius = radius;

  return gfxButton(_x, _y, _w, _h, _roundedRect, _radius);
}
