#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"

class gfxButton {
  public:
    gfxButton();
    gfxButton(String _screen, int _x, int _y, int _w, int _h, bool _roundedRect, int _radius);
    void begin(MCUFRIEND_kbv &tft);
    gfxButton initButton(String screen, int x, int y, int w, int h, bool roundedRect, int radius);
    void drawButton(gfxButton &button, int colour);

    String screen;
    int x, y, w, h, radius;
    bool roundedRect;
    MCUFRIEND_kbv _tft;

  private:
    String _screen;
    int _x, _y, _w, _h, _radius;
    bool _roundedRect;
};

// class TouchDisplay {
//   public:
//     TouchDisplay();
//     gfxButton initButton(String screen, int x, int y, int w, int h, bool roundedRect, int radius);
//     void drawButton(gfxButton &button, int colour);
//
//   private:
//     String _screen;
//     int _x, _y, _w, _h, _radius;
//     bool _roundedRect;
// };

#endif
