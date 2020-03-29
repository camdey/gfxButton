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
    gfxButton(String _screen, String buttonType, int _x, int _y, int _w, int _h, int _r, unsigned long defaultColour);
    gfxButton(String _screen, const unsigned char* _bitmap, int _x, int _y, int _w, int _h, unsigned long defaultColour);
    gfxButton initButton(String screen, String buttonType, int x, int y, int w, int h, int r, unsigned long defaultColour);
    gfxButton initBitmapButton(String screen, const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour);
    void drawButton(MCUFRIEND_kbv _tft, unsigned long colour);
    void drawButton(MCUFRIEND_kbv _tft);
    void writeTextCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextTopCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextBottomCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextLeft(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextRight(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void writeTextCircle(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour);
    void replaceButtonText(MCUFRIEND_kbv _tft, String _newText, String _aligned, int _btnX, int _btnY, int _btnW = 0, int _btnH = 0);
    void setPreviousText(String _text);
    String getPreviousText();
    void setButtonColour(unsigned long _colour);
    int getButtonColour();

    String screen, buttonType;
    const unsigned char* bitmap;
    int x, y, w, h, r;
    unsigned long colour, defaultColour;

  private:
    String _previousText;
    unsigned long _buttonColour;
};

class gfxTouch {
  public:
    gfxTouch();
    gfxTouch(String _screen, String _name, int _xMin, int _xMax, int _yMin, int _yMax, String _touchType, void (*btnFunction)(bool state));
    gfxTouch addToggle(gfxButton &button, void (*btnFunction)(bool state), String name, int percent);
    gfxTouch addMomentary(gfxButton &button, void (*btnFunction)(bool state), String name, int percent);
    void setTouchBoundary(int _x, int _y, int _w, int _h, int _r, int _percent);
    void checkButton(String currentScreen, int touch_x, int touch_y);
    void runButtonFunction();
    bool getState();
    void setState(bool btnActive);
    void setToggleDebounce(unsigned long toggle_delay);
    void setMomentaryDebounce(unsigned long momentary_delay);
    void toggleCoolOff();

    int percent;
    int xMin, xMax, yMin, yMax;
    String screen, name, touchType;
    void (*btnFunc)(bool state);

  private:
    TSPoint _point;
    int _xMin, _xMax, _yMin, _yMax;
    int touch_x, touch_y;
    bool _btnActive, _coolOff;
    unsigned long lastTouched, toggle_delay, momentary_delay;
    static unsigned long g_toggle_delay, g_momentary_delay;
};

#endif
