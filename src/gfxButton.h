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
    gfxButton(int _x, int _y, int _w, int _h, String _screen);
    gfxButton(String drawType, int _x, int _y, int _w, int _h, int _r, unsigned long _defaultColour, String _screen);
    gfxButton(const unsigned char* _bitmap, int _x, int _y, int _w, int _h, unsigned long _defaultColour, String _screen);
    gfxButton initBlankButton(int x, int y, int w, int h, String _screen = "");
    gfxButton initButton(String drawType, int x, int y, int w, int h, int r, unsigned long _defaultColour, String _screen = "");
    gfxButton initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long _defaultColour, String _screen = "");
    void drawButton(MCUFRIEND_kbv _tft);
    void drawButton(MCUFRIEND_kbv _tft, unsigned long _colour);
    void drawNewBitmap(MCUFRIEND_kbv _tft, const unsigned char* _bitmap, unsigned long _colour);
    void addBorder(int _width, unsigned long _colour);
    void writeTextCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextTopCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextBottomCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextTopLeft(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextBottomLeft(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextLeft(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextRight(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextCircle(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void replaceButtonText(MCUFRIEND_kbv _tft, String _newText, String _aligned, int _btnX, int _btnY, int _btnW = 0, int _btnH = 0);
    void setBackgroundColour(unsigned long _colour);
    void setButtonColour(unsigned long _colour);
    void setPreviousText(String _text);
    unsigned long getBackgroundColour();
    unsigned long getButtonColour();
    String getPreviousText();

    String screen, drawType;
    const unsigned char* bitmap;
    int x, y, w, h, r;
    unsigned long colour, defaultColour;

  private:
    String _previousText;
    unsigned long _buttonColour, _borderColour;
    static unsigned long g_backgroundColour;
    bool _hasBorder;
    int _borderWidth;
};

class gfxTouch {
  public:
    gfxTouch();
    gfxTouch(String _screen, int _xMin, int _xMax, int _yMin, int _yMax, String _touchType, void (*btnFunction)(bool state));
    gfxTouch addToggle(gfxButton &button, void (*btnFunction)(bool state), int percent);
    gfxTouch addMomentary(gfxButton &button, void (*btnFunction)(bool state), int percent);
    void setTouchBoundary(int _x, int _y, int _w, int _h, int _r, int _percent);
    void checkButton(String currentScreen, int touch_x, int touch_y);
    void runButtonFunction();
    bool getState();
    void setState(bool btnActive);
    void setToggleDebounce(unsigned long toggleDelay);
    void setMomentaryDebounce(unsigned long momentaryDelay);

    int percent;
    int xMin, xMax, yMin, yMax;
    String screen, name, touchType;
    void (*btnFunc)(bool state);

  private:
    TSPoint _point;
    int _xMin, _xMax, _yMin, _yMax;
    int touch_x, touch_y;
    bool _btnActive;
    unsigned long lastTouched, toggleDelay, momentaryDelay;
    static unsigned long g_toggleDelay, g_momentaryDelay;
};

#endif
