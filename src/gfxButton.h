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
    gfxTouch(String _screen, String _name, int _xMin, int _yMin, int _xMax, int _yMax, void (*btnFunction)(bool state));
    gfxTouch addTouch(gfxButton &button, void (*btnFunction)(bool state), String name, int percent);
    void begin(TSPoint &point);
    void checkButtons(String screen2, int x, int y);
    void runFunction();
    bool getState();
    void setState(bool btnActive);

    int percent, x, y;
    int xMin, xMax, yMin, yMax;
    String screen, name;
    void (*btnFunc)(bool state);

  private:
    TSPoint _point;
    String _screen, _shape, _name;
    int _x, _y, _w, _h, _r, _colour, _defaultColour;
    int _xMin, _xMax, _yMin, _yMax;
    bool _btnActive;
};

#endif
