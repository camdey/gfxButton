#ifndef gfxButton_h
#define gfxButton_h

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
#include "SdFat.h"

class gfxButton {
  public:
    enum class Shape : uint8_t {
      Vacant,
      Blank,
      DrawRect,
      FillRect,
      DrawRoundRect,
      FillRoundRect,
      DrawCircle,
      FillCircle,
      Bitmap,
      RGBBitmap,
      SDBitmap
    };

    static void begin(MCUFRIEND_kbv *tft);
    static void begin(MCUFRIEND_kbv *tft, SdFat *SD);
    gfxButton();
    gfxButton(int x, int y, int w, int h, bool isTactile);
    gfxButton(const char* label, int x, int y, int w, int h, bool isTactile);
    gfxButton(const char* label, Shape shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile);
    gfxButton(const uint16_t* bitmap, int x, int y, int w, int h, bool isTactile);
    gfxButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, unsigned long defaultBgColour, bool isTactile);
    gfxButton(const char* filename, int x, int y, bool isTactile); // bitmap from sd card
    gfxButton initButton(const char* label, Shape shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile);
    gfxButton initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, unsigned long defaultBgColour, bool isTactile);
    gfxButton initRGBBitmapButton(const uint16_t* bitmap, int x, int y, int w, int h, bool isTactile);
    gfxButton initSDBitmapButton(const char* filename, int x, int y, bool isTactile);
    gfxButton initTransparentButton(int x, int y, int w, int h, bool isTactile);
    gfxButton initTransparentButton(const char* label, int x, int y, int w, int h, bool isTactile);
    gfxButton initVacantButton();
    void addBorder(int width, unsigned long colour);
    void drawBorder(int width);
    void drawBorder(int width, unsigned long colour);
    void drawButton();
    void drawButton(unsigned long colour, unsigned long bg = 0x00);
    void drawNewBitmap(const uint16_t* bitmap);
    void drawNewBitmap(const unsigned char* bitmap, unsigned long colour, unsigned long bg = 0x00);
    void writeTextCentre(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextTopCentre(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextBottomCentre(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextTopLeft(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextBottomLeft(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextLeft(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextRight(const GFXfont &font, unsigned long colour, String btnText = "");
    void writeTextCircle(const GFXfont &font, unsigned long colour, String btnText = "");
    void invalidateTextCache();
    void setBackgroundColour(unsigned long colour);
    unsigned long getBackgroundColour() const;
    void setButtonColour(unsigned long colour);
    unsigned long getButtonColour() const;
    void setTactile(bool tactile);
    bool isTactile() const;
    void updateBitmap(const unsigned char* bitmap);
    void updateRGBBitmap(const uint16_t* bitmap);
    void updateColour(unsigned long colour);
    void updateLabel(const char* label);
    void hideButton();
    void showButton();
    void setVisible(bool visible);
    bool isHidden() const;

    // bitmap loaded from sd card
    #define BMPIMAGEOFFSET  54
    #define BUFFPIXEL       20
    #define NAMEMATCH       ""
    #define PALETTEDEPTH    0     // do not support Palette modes

    uint8_t drawBMPFromSD(const char* nm, int x, int y);
    uint16_t read16(File& f);
    uint32_t read32(File& f);
    void setBitmapDimensions(const char* filename);


    Shape m_shape = Shape::Vacant;
    const char* m_label = nullptr;  // non-owning pointer — caller must ensure string outlives the button
    const char* m_filename = nullptr;
    const unsigned char* m_bitmap = nullptr;
    const uint16_t* m_rgb_bitmap = nullptr;
    int m_x = 0, m_y = 0, m_w = 0, m_h = 0, m_r = 0;
    int m_borderWidth = 0;
    unsigned long m_defaultColour = 0, m_defaultBgColour = 0;
    bool m_isBitmapButton = false, m_hasBorder = false;


  private:
    enum TextAlignX : uint8_t { AlignCentre, AlignLeft, AlignRight };
    enum TextRegionY : uint8_t { RegionFull, RegionTop, RegionBottom, RegionCircle };
    static const uint8_t TextCacheSlots = 2;
    struct TextRenderState {
      bool valid = false;
      uint32_t textHash = 0;
      const GFXfont *font = nullptr;
      unsigned long colour = 0;
      TextAlignX alignment = AlignCentre;
      TextRegionY region = RegionFull;
      int16_t cursorX = 0;
      int16_t cursorY = 0;
      int16_t boundsX = 0;
      int16_t boundsY = 0;
      uint16_t boundsW = 0;
      uint16_t boundsH = 0;
    };
    void writeTextHelper(const GFXfont &font, unsigned long colour, String btnText, TextAlignX alignX, TextRegionY regionY);
    void renderCachedText(const GFXfont &font, unsigned long colour, const String &text, TextAlignX alignX, TextRegionY regionY, int16_t cursorX, int16_t cursorY);
    void eraseTextRegion(TextRegionY region);
    void prepareTextRegion(TextRegionY region);
    uint8_t textCacheSlot(TextRegionY region) const;
    uint32_t textHash(const String &text) const;
    unsigned long textBackgroundColour() const;
    TextRenderState m_textCache[TextCacheSlots];
    unsigned long m_buttonColour = 0, m_borderColour = 0;
    static unsigned long g_backgroundColour;
    static MCUFRIEND_kbv *s_tft;
    static SdFat *s_sd;
    bool m_isTactile = false, m_isHidden = false;


  public:
    void addToggle(void (*btnFunction)(bool state), int paddingPercent);
    void addMomentary(void (*btnFunction)(bool state), int paddingPercent);
    void addInputKey(void (*btnFunction)(const char* label), int paddingPercent);
    void contains(int x, int y);
    void actuateButton(bool actuate);
    void setButtonActive(bool active);
    bool isButtonActive() const;
    void setScreenSize(int width, int height);
    void setToggleDelay(unsigned long delay);
    void setMomentaryDelay(unsigned long delay);
    void setButtonToggleDelay(unsigned long delay);
    void setButtonMomentaryDelay(unsigned long delay);
    void setToggleActive(bool active);
    bool isToggleActive() const;

    int m_xMin = 0, m_xMax = 0, m_yMin = 0, m_yMax = 0;
    bool m_isMomentaryButton = false;
    void (*m_boolFunction)(bool state) = nullptr;
    void (*m_charFunction)(const char* label) = nullptr;
    

  private:
    struct touchBoundary {
      int xMin;
      int xMax;
      int yMin;
      int yMax;
    };
    void executeFunction();
    void setTouchBoundary(int x, int y, int w, int h, int r, int paddingPercent);

    struct touchBoundary vals = {0, 0, 0, 0};
    bool m_buttonActive = false, m_returnLabel = false;
    unsigned long m_lastStateChange = 0;
    unsigned long m_buttonToggleDelay = 0, m_buttonMomentaryDelay = 0;  // per-button overrides (0 = use global)
    static unsigned long g_toggleDelay, g_momentaryDelay;
    static int g_screenWidth, g_screenHeight;
    static bool g_toggleActive;
};

#endif
