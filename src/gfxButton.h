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
    void begin(MCUFRIEND_kbv &tft);
    gfxButton addButton(String screen, String shape, int x, int y, int w, int h, int r, int defaultColour);
    void drawButton(gfxButton &button, int colour);
    void drawButtons(gfxButton &button);

    String screen, shape;
    int x, y, w, h, r, colour, defaultColour;
    MCUFRIEND_kbv _tft;

  private:
    String _screen, _shape;
    int _x, _y, _w, _h, _r, _colour, _defaultColour;
};

class gfxTouch {
  public:
    gfxTouch();
    gfxTouch(String screen, String name, int min_x, int min_y, int max_x, int max_y, void (*btnFunction)());
    void begin(TSPoint &point);
    gfxTouch addTouch(gfxButton &button, void (*btnFunction)(), String name, int percent);
    void checkButtons(gfxTouch &button, String screen, int x, int y);

    TSPoint _point;
    int percent, x, y;
    int xMin, xMax, yMin, yMax;
    String screen, name;
    void (*btnFunc)();
  private:
    String _screen, _shape, _name;
    int _x, _y, _w, _h, _r, _colour, _defaultColour;
    int _xMin, _xMax, _yMin, _yMax;
};

#endif
