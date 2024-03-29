#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "SdFat.h"

class gfxButton {
  public:
    void begin(MCUFRIEND_kbv *tft);
    void begin(MCUFRIEND_kbv *tft, SdFat *SD);
    gfxButton();
    gfxButton(int x, int y, int w, int h, bool isTactile);
    gfxButton(char* label, int x, int y, int w, int h, bool isTactile);
    gfxButton(char* label, String m_shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile);
    gfxButton(const uint16_t* bitmap, int x, int y, int w, int h, bool isTactile);
    gfxButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, unsigned long defaultBgColour, bool isTactile);
    gfxButton(char* filename, int x, int y, bool isTactile); // bitmap from sd card
    gfxButton initButton(char* label, String shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile);
    gfxButton initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, unsigned long defaultBgColour, bool isTactile);
    gfxButton initRGBBitmapButton(const uint16_t* bitmap, int x, int y, int w, int h, bool isTactile);
    gfxButton initSDBitmapButton(char* filename, int x, int y, bool isTactile);
    gfxButton initTransparentButton(int x, int y, int w, int h, bool isTactile);
    gfxButton initTransparentButton(char* label, int x, int y, int w, int h, bool isTactile);
    gfxButton initVacantButton();
    void addBorder(int width, unsigned long colour);
    void drawBorder(int width);
    void drawBorder(int width, unsigned long colour);
    void drawButton();
    void drawButton(unsigned long colour, unsigned long bg = 0x00);
    void drawNewBitmap(const uint16_t* bitmap);
    void drawNewBitmap(const unsigned char* bitmap, unsigned long colour, unsigned long bg = 0x00);
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
    void setTactile(bool tactile);
    bool isTactile();
    void updateBitmap(const unsigned char* bitmap);
    void updateRGBBitmap(const uint16_t* bitmap);
    void updateColour(unsigned long colour);
    void updateLabel(char* label);
    void hideButton();
    bool isHidden();

    // bitmap loaded from sd card
    #define BMPIMAGEOFFSET  54
    #define BUFFPIXEL       20
    #define NAMEMATCH       ""
    #define PALETTEDEPTH    0     // do not support Palette modes

    uint8_t drawBMPFromSD(char* nm, int x, int y);
    uint16_t read16(File& f);
    uint32_t read32(File& f);
    void setBitmapDimensions(char* filename);


    String m_shape;
    char* m_label;
    char* m_filename;
    const unsigned char* m_bitmap;
    const uint16_t* m_rgb_bitmap;
    int m_x, m_y, m_w, m_h, m_r;
    int m_borderWidth;
    unsigned long m_defaultColour, m_defaultBgColour;
    bool m_isBitmapButton, m_hasBorder;


  private:
    void replaceButtonLabel(char* m_label, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void replaceButtonText(String newText, String prevText, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void replaceButtonValue(String value, String aligned, int btnX, int btnY, int btnW = 0, int btnH = 0);
    void setPreviousText(String _text);
    String getPreviousText();

    String m_previousText;
    unsigned long m_buttonColour, m_borderColour;
    static unsigned long g_backgroundColour;
    bool m_isTactile, m_isHidden;


  public:
    void addToggle(void (*btnFunction)(bool state), int paddingPercent);
    void addMomentary(void (*btnFunction)(bool state), int paddingPercent);
    void addInputKey(void (*btnFunction)(char* label), int paddingPercent);
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
    bool m_isMomentaryButton;
    void (*m_boolFunction)(bool state);
    void (*m_charFunction)(char* label);
    

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
    bool m_buttonActive, m_returnLabel;
    unsigned long m_lastStateChange;
    static unsigned long g_toggleDelay, g_momentaryDelay;
    static int g_screenWidth, g_screenHeight;
    static bool g_toggleActive;
};

#endif
