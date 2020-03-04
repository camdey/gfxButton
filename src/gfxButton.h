#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"

class gfxButton {
  public:
    gfxButton();
    gfxButton(String _screen, String shape, int _x, int _y, int _w, int _h, int _r, int defaultColour);
    gfxButton addButton(String screen, String shape, int x, int y, int w, int h, int r, int defaultColour);
    void drawButton(MCUFRIEND_kbv _tft, int colour);
    void drawButtons(MCUFRIEND_kbv _tft);

    String screen, shape;
    int x, y, w, h, r, colour, defaultColour;

  private:
    String _screen, _shape;
    int _x, _y, _w, _h, _r, _colour, _defaultColour;
    static MCUFRIEND_kbv _tft;
};

class gfxTouch {
  public:
    gfxTouch();
    gfxTouch(String _screen, String _name, int _xMin, int _yMin, int _xMax, int _yMax, String _btnType, void (*btnFunction)(bool state));
    gfxTouch addToggle(gfxButton &button, void (*btnFunction)(bool state), String name, int percent);
    gfxTouch addMomentary(gfxButton &button, void (*btnFunction)(bool state), String name, int percent);
    void checkButton(String currentScreen, int touch_x, int touch_y);
    void runButtonFunction();
    bool getState();
    void setState(bool btnActive);
    void setToggleDebounce(unsigned long toggle_delay);
    void setMomentaryDebounce(unsigned long momentary_delay);
    void toggleCoolOff();

    int percent;
    int xMin, xMax, yMin, yMax;
    String screen, name, btnType;
    void (*btnFunc)(bool state);

  private:
    TSPoint _point;
    String _screen, _shape, _name, _btnType;
    int _x, _y, _w, _h, _r, _colour, _defaultColour;
    // int _xMin, _xMax, _yMin, _yMax;
    int touch_x, touch_y;
    bool _btnActive, _coolOff;
    unsigned long lastTouched, toggle_delay, momentary_delay;
    static unsigned long _toggle_delay, _momentary_delay;
};

#endif
