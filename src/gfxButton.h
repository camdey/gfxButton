#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"

class gfxButton {
  public:
    void begin(MCUFRIEND_kbv *tft);
    gfxButton();
    gfxButton(int x, int y, int w, int h, bool isTactile);
    gfxButton(String label, String m_shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile);
    gfxButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, bool isTactile);
    gfxButton initButton(String label, String shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile);
    gfxButton initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, bool isTactile);
    gfxButton initTransparentButton(int x, int y, int w, int h, bool isTactile);
    gfxButton initVacantButton();
    void addBorder(int width, unsigned long colour);
    void drawBorder(int width);
    void drawBorder(int width, unsigned long colour);
    void drawButton();
    void drawButton(unsigned long colour);
    void drawNewBitmap(const unsigned char* bitmap, unsigned long colour);
    void writeTextCentre(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextTopCentre(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextBottomCentre(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextTopLeft(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextBottomLeft(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextLeft(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextRight(GFXfont font, unsigned long colour, String btnText = "");
    void writeTextCircle(GFXfont font, unsigned long colour, String btnText = "");
    void setBackgroundColour(unsigned long colour);
    unsigned long getBackgroundColour();
    void setButtonColour(unsigned long colour);
    unsigned long getButtonColour();
    bool isTactile();
    void updateLabel(String label);
    void updateColour(unsigned long colour);
    void updateBitmap(const unsigned char* bitmap);

    String m_shape, m_label;
    const unsigned char* m_bitmap;
    int m_x, m_y, m_w, m_h, m_r;
    int m_borderWidth;
    unsigned long m_defaultColour;
    bool m_isBitmapButton, m_hasBorder;


  private:
    void replaceButtonLabel(String m_label, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void replaceButtonText(String newText, String prevText, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void replaceButtonValue(String value, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void setPreviousText(String _text);
    String getPreviousText();

    String m_previousText;
    unsigned long m_buttonColour, m_borderColour, m_isTactile;
    static unsigned long g_backgroundColour;


  public:
    void addToggle(void (*btnFunction)(bool state), int paddingPercent);
    void addMomentary(void (*btnFunction)(bool state), int paddingPercent);
    void contains(int x, int y);
    void actuateButton(bool actuate);
    void setButtonActive(bool active);
    bool isButtonActive();
    void setScreenSize(int width, int height);
    void setToggleDelay(unsigned long delay);
    void setMomentaryDelay(unsigned long delay);
    void setToggleActive(bool active);
    bool isToggleActive();

    int m_xMin, m_xMax, m_yMin, m_yMax;
    String m_touchType;
    void (*m_btnFunc)(bool state);
    

  private:
    struct touchBoundary {
      int xMin;
      int xMax;
      int yMin;
      int yMax;
    };
    void executeFunction();
    void setTouchBoundary(int x, int y, int w, int h, int r, int paddingPercent);

    struct touchBoundary vals;
    bool m_buttonActive;
    unsigned long m_lastStateChange;
    static unsigned long g_toggleDelay, g_momentaryDelay;
    static int g_screenWidth, g_screenHeight;
    static bool g_toggleActive;
};

#endif
