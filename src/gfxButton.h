#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"
#include "Wire.h"

class gfxButton {
  public:
    gfxButton();
    gfxButton(int x, int y, int w, int h, bool isTactile, String screen);
    gfxButton(String m_drawType, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile, String screen);
    gfxButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, bool isTactile, String screen);
    gfxButton initBlankButton(int x, int y, int w, int h, bool isTactile, String screen = "");
    gfxButton initButton(String drawType, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile, String screen = "");
    gfxButton initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, bool isTactile, String screen = "");
    void addBorder(int width, unsigned long colour);
    void drawBorder(MCUFRIEND_kbv tft, int width);
    void drawBorder(MCUFRIEND_kbv tft, int width, unsigned long colour);
    void drawButton(MCUFRIEND_kbv tft);
    void drawButton(MCUFRIEND_kbv tft, unsigned long colour);
    void drawNewBitmap(MCUFRIEND_kbv tft, const unsigned char* bitmap, unsigned long colour);
    void writeTextCentre(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextTopCentre(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextBottomCentre(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextTopLeft(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextBottomLeft(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextLeft(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextRight(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void writeTextCircle(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour);
    void replaceButtonText(MCUFRIEND_kbv tft, String newText, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void setBackgroundColour(unsigned long colour);
    unsigned long getBackgroundColour();
    void setButtonColour(unsigned long colour);
    unsigned long getButtonColour();
    void setPreviousText(String _text);
    String getPreviousText();
    bool isTactile();

    String m_screen, m_drawType;
    const unsigned char* m_bitmap;
    int m_x, m_y, m_w, m_h, m_r;
    int m_borderWidth;
    unsigned long m_defaultColour;
    bool m_isBitmapButton, m_hasBorder;

  private:
    String m_previousText;
    unsigned long m_buttonColour, m_borderColour, m_isTactile;
    static unsigned long g_backgroundColour;
};


class gfxTouch {
  public:
    struct touchBoundary {
      int xMin;
      int xMax;
      int yMin;
      int yMax;
    };

    gfxTouch();
    gfxTouch(String screen, int xMin, int xMax, int yMin, int yMax, String touchType, void (*btnFunction)(bool state));
    gfxTouch addToggle(gfxButton &button, void (*btnFunction)(bool state), int percent);
    gfxTouch addMomentary(gfxButton &button, void (*btnFunction)(bool state), int percent);
    void initNavigationLayout(gfxButton **array, int rows, int cols);
    void setTouchBoundary(int x, int y, int w, int h, int r, int percent);
    void checkTouchInput(String currentScreen, int touch_x, int touch_y);
    void checkDigitalInput(String currentScreen, bool isActive);
    void runButtonFunction();
    void setButtonActive(bool active);
    bool isButtonActive();
    void setScreenSize(int width, int height);
    void setToggleDelay(unsigned long delay);
    void setMomentaryDelay(unsigned long delay);
    void setToggleActive(bool active);
    bool isToggleActive();

    struct touchBoundary vals;
    int m_xMin, m_xMax, m_yMin, m_yMax;
    String m_screen, m_touchType;
    void (*m_btnFunc)(bool state);
    static bool g_toggleActive;

  private:
    bool m_buttonActive;
    unsigned long m_lastStateChange;
    static unsigned long g_toggleDelay, g_momentaryDelay;
    static int g_screenWidth, g_screenHeight;
};

#endif
