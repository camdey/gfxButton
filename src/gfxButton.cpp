#include "Arduino.h"
#include "gfxButton.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"


gfxButton::gfxButton() {};

gfxButton::gfxButton(String _screen, int _x, int _y, int _w, int _h, bool _roundedRect, int _radius) {
  screen = _screen;
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  roundedRect = _roundedRect;
  radius = _radius;
}


void gfxButton::begin(MCUFRIEND_kbv &tft) {
  _tft = tft;
}

gfxButton gfxButton::initButton(String screen, int x, int y, int w, int h, bool roundedRect, int radius=0) {
  _screen = screen;
  _x = x;
  _y = y;
  _w = w;
  _h = h;
  _roundedRect = roundedRect;
  _radius = radius;

  return gfxButton(_screen, _x, _y, _w, _h, _roundedRect, _radius);
}

void gfxButton::drawButton(gfxButton &button, int colour) {
  _tft.fillRoundRect(button.x, button.y, button.w, button.h, button.radius, colour);
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
