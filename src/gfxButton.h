#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "SPI.h"

class gfxButton {
  public:
    gfxButton(int x, int y, int w, int h, bool roundedRect, int radius);
    int x, y, w, h, radius;
    bool roundedRect;

    // void getAttributes();
    // void setAttributes(String buttonName, String page, String action, String touchPadding, String touch_indicator);
    // void drawButton(int x, int y, int w, int h, bool roundedRect, int radius);
    // void addButton();
    // void getButtonByPage();
  private:
    // button attributes
    // String _buttonName
    // String _page;
    // String _action;
    // int _touchPadding;
    // String _touchIndicator;
    // button
    int _x;
    int _y;
    int _w;
    int _h;
    bool _roundedRect;
    int _radius;
};

class TouchDisplay {
  public:
    TouchDisplay();
    gfxButton initButton(int x, int y, int w, int h, bool roundedRect, int radius);

  private:
    int _x;
    int _y;
    int _w;
    int _h;
    bool _roundedRect;
    int _radius;
};

#endif
