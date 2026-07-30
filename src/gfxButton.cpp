#include "Arduino.h"
#include "gfxButton.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"


MCUFRIEND_kbv *gfxButton::s_tft = nullptr;
SdFat *gfxButton::s_sd = nullptr;


// init tft so it can be used in other functions
void gfxButton::begin(MCUFRIEND_kbv *tft) {
  s_tft = tft;
}

void gfxButton::begin(MCUFRIEND_kbv *tft, SdFat *SD) {
  s_tft = tft;
  s_sd = SD;
}

/******************************************************
/              Create a Button Instance
/ Creates a button instance for GFX shapes that will allow
/ you to add touch functionality for using the shape
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton() {
  m_isTactile = false;
};


gfxButton::gfxButton(const char* label, Shape shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile) {
  m_label = label;
  m_shape = shape;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = r;
  m_defaultColour = defaultColour;
  m_isBitmapButton = false;
  m_isTactile = isTactile;
  m_isHidden = false;
}


/******************************************************
/          Create a blank Button Instance
/ Creates a button instance for GFX shapes that will allow
/ you to add touch functionality for using the shape
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(int x, int y, int w, int h, bool isTactile) {
  m_shape = Shape::Blank;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = 0;
  m_defaultColour = 0;
  m_isBitmapButton = false;
  m_isTactile = isTactile;
  m_isHidden = false;
}


gfxButton::gfxButton(const char* label, int x, int y, int w, int h, bool isTactile) {
  m_label = label;
  m_shape = Shape::Blank;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = 0;
  m_defaultColour = 0;
  m_isBitmapButton = false;
  m_isTactile = isTactile;
  m_isHidden = false;
}


/******************************************************
/           Create a Bitmap Button Instance
/ Creates a button instance for bitmaps that will allow
/ you to add touch functionality for using the bitmap
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, unsigned long defaultBgColour, bool isTactile) {
  m_bitmap = bitmap;
  m_shape = Shape::Bitmap;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = 0;
  m_defaultColour = defaultColour;
  m_defaultBgColour = defaultBgColour;
  m_isBitmapButton = true;
  m_isTactile = isTactile;
  m_isHidden = false;
}


/******************************************************
/           Create a RGB Bitmap Button Instance
/ Creates a button instance for bitmaps that will allow
/ you to add touch functionality for using the bitmap
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(const uint16_t* bitmap, int x, int y, int w, int h, bool isTactile) {
  m_rgb_bitmap = bitmap;
  m_shape = Shape::RGBBitmap;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = 0;
  m_isBitmapButton = true;
  m_isTactile = isTactile;
  m_isHidden = false;
}


/******************************************************
/      Create a SD card Bitmap Button Instance
/ Creates a button instance for bitmaps loaded from SD
/ card
******************************************************/
gfxButton::gfxButton(const char* filename, int x, int y, bool isTactile) {
  m_filename = filename;
  m_shape = Shape::SDBitmap;
  m_x = x;
  m_y = y;
  m_isBitmapButton = true;
  m_isTactile = isTactile;
  m_isHidden = false;
}


/******************************************************
/                    Init a Button
/ Initiates a button instance for GFX shapes, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initButton(const char* label, Shape shape, int x, int y, int w, int h, int r, unsigned long defaultColour, bool isTactile) {
  return gfxButton(label, shape, x, y, w, h, r, defaultColour, isTactile);
}


/******************************************************
/                Init a blank Button
/ Used for a button with no background or shape
/ Suitable for printing and centering text
******************************************************/
gfxButton gfxButton::initTransparentButton(int x, int y, int w, int h, bool isTactile) {
  return gfxButton(x, y, w, h, isTactile);
}


gfxButton gfxButton::initTransparentButton(const char* label, int x, int y, int w, int h, bool isTactile) {
  return gfxButton(label, x, y, w, h, isTactile);
}


/******************************************************
/                Init a vacant Button
/ A vacant button can be used when you have a column
or row of buttons with less than the min. amount
******************************************************/
gfxButton gfxButton::initVacantButton() {
  return gfxButton();
}


/******************************************************
/               Init a bitmap Button
/ Initiates a button instance for bitmaps, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, unsigned long defaultBgColour, bool isTactile) {
  return gfxButton(bitmap, x, y, w, h, defaultColour, defaultBgColour, isTactile);
}


/******************************************************
/               Init a RGB bitmap Button
/ Initiates a button instance for bitmaps, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initRGBBitmapButton(const uint16_t* bitmap, int x, int y, int w, int h, bool isTactile) {
  return gfxButton(bitmap, x, y, w, h, isTactile);
}


/******************************************************
/             Init a SD card bitmap Button
/ Initiates a button instance for bitmaps, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initSDBitmapButton(const char* filename, int x, int y, bool isTactile) {
  return gfxButton(filename, x, y, isTactile);
}


/******************************************************
/               Draw Button Shapes
/ Draws a button based on the GFX Library commands.
/ Can draw different types of buttons based on the
/ m_shape parameter set for the button.
******************************************************/
void gfxButton::drawButton() {
  m_isHidden = false;
  invalidateTextCache();
  switch (m_shape) {
    case Shape::DrawRect:
      s_tft->drawRect(m_x, m_y, m_w, m_h, m_defaultColour);
      break;
    case Shape::FillRect:
      s_tft->fillRect(m_x, m_y, m_w, m_h, m_defaultColour);
      break;
    case Shape::DrawRoundRect:
      s_tft->drawRoundRect(m_x, m_y, m_w, m_h, m_r, m_defaultColour);
      break;
    case Shape::FillRoundRect:
      s_tft->fillRoundRect(m_x, m_y, m_w, m_h, m_r, m_defaultColour);
      break;
    case Shape::DrawCircle:
      s_tft->drawCircle(m_x, m_y, m_r, m_defaultColour);
      break;
    case Shape::FillCircle:
      s_tft->fillCircle(m_x, m_y, m_r, m_defaultColour);
      break;
    case Shape::Bitmap:
      s_tft->drawBitmap(m_x, m_y, m_bitmap, m_w, m_h, m_defaultColour, m_defaultBgColour);
      break;
    case Shape::RGBBitmap:
      s_tft->drawRGBBitmap(m_x, m_y, m_rgb_bitmap, m_w, m_h);
      break;
    case Shape::SDBitmap:
      drawBMPFromSD(m_filename, m_x, m_y);
      break;
    case Shape::Vacant:
    case Shape::Blank:
      break;
  }
  // TODO support triangles
  // else if (button.m_shape == "drawTriangle") {
  //   s_tft->drawTriangle(button.m_x, button.m_y, button.m_w, button.m_h, button.m_defaultColour);
  // }
  // else if (button.m_shape == "fillTriangle") {
  //   s_tft->fillTriangle(button.m_x, button.m_y, button.m_w, button.m_h, button.m_defaultColour);
  // }

  // store button colour, used for overwriting text
  setButtonColour(m_defaultColour);

  if (m_hasBorder == true) {
    drawBorder(m_borderWidth, m_borderColour);
  }
}


/******************************************************
/               Draw Button Shapes
/ Draws a button based on the GFX Library commands.
/ Can draw different types of buttons based on the
/ m_shape parameter set for the button.
******************************************************/
void gfxButton::drawButton(unsigned long colour, unsigned long bg) {
  m_isHidden = false;
  invalidateTextCache();
  switch (m_shape) {
    case Shape::DrawRect:
      s_tft->drawRect(m_x, m_y, m_w, m_h, colour);
      break;
    case Shape::FillRect:
      s_tft->fillRect(m_x, m_y, m_w, m_h, colour);
      break;
    case Shape::DrawRoundRect:
      s_tft->drawRoundRect(m_x, m_y, m_w, m_h, m_r, colour);
      break;
    case Shape::FillRoundRect:
      s_tft->fillRoundRect(m_x, m_y, m_w, m_h, m_r, colour);
      break;
    case Shape::DrawCircle:
      s_tft->drawCircle(m_x, m_y, m_r, colour);
      break;
    case Shape::FillCircle:
      s_tft->fillCircle(m_x, m_y, m_r, colour);
      break;
    case Shape::Bitmap:
      s_tft->drawBitmap(m_x, m_y, m_bitmap, m_w, m_h, colour, bg);
      break;
    case Shape::RGBBitmap:
      s_tft->drawRGBBitmap(m_x, m_y, m_rgb_bitmap, m_w, m_h);
      break;
    case Shape::SDBitmap:
      drawBMPFromSD(m_filename, m_x, m_y);
      break;
    case Shape::Vacant:
    case Shape::Blank:
      break;
  }
  // TODO support triangles
  // else if (button.m_shape == "drawTriangle") {
  //   s_tft->drawTriangle(button.m_x, button.m_y, button.m_w, button.m_h, colour);
  // }
  // else if (button.m_shape == "fillTriangle") {
  //   s_tft->fillTriangle(button.m_x, button.m_y, button.m_w, button.m_h, colour);
  // }

  // store button colour, used for overwriting text
  setButtonColour(colour);

  if (m_hasBorder == true) {
    drawBorder(m_borderWidth, m_borderColour);
  }
}


/******************************************************
/               Draw New Bitmap
/ Draws a new bitmap image for an existing button
/ Allows you to change the bitmap image depending on
/ the state of the button.
******************************************************/
void gfxButton::drawNewBitmap(const unsigned char* bitmap, unsigned long colour, unsigned long bg) {
  m_bitmap = bitmap;
  m_isHidden = false;
  invalidateTextCache();
  // fill over previous bitmap/button
  s_tft->fillRect(m_x, m_y, m_w, m_h, getBackgroundColour());
  // draw new bitmap
  s_tft->drawBitmap(m_x, m_y, bitmap, m_w, m_h, colour, bg);

  // store button colour, used for overwriting text
  setButtonColour(colour);
}


/******************************************************
/               Draw New RGB Bitmap
/ Draws a new bitmap image for an existing button
/ Allows you to change the bitmap image depending on
/ the state of the button.
******************************************************/
void gfxButton::drawNewBitmap(const uint16_t* bitmap) {
  m_rgb_bitmap = bitmap;
  m_isHidden = false;
  invalidateTextCache();
  // fill over previous bitmap/button
  s_tft->fillRect(m_x, m_y, m_w, m_h, getBackgroundColour());
  // draw new bitmap
  s_tft->drawRGBBitmap(m_x, m_y, bitmap, m_w, m_h);
}


void gfxButton::addBorder(int width, unsigned long colour) {
  if (m_shape == Shape::FillRect ||
      m_shape == Shape::FillRoundRect ||
      m_shape == Shape::FillCircle) {
    m_hasBorder = true;
    m_borderWidth = width;
    m_borderColour = colour;
  }
}


void gfxButton::drawBorder(int width, unsigned long colour) {
  if (!m_isBitmapButton) {
    for (int i = 0; i < width; i++) {
      int x = m_x + i;
      int y = m_y + i;
      int w = m_w - i*2;
      int h = m_h - i*2;
      int r = m_r - i;

      if (m_shape == Shape::FillRect) {
        s_tft->drawRect(x, y, w, h, colour);
      }
      else if (m_shape == Shape::FillRoundRect) {
        s_tft->drawRoundRect(x, y, w, h, r, colour);
      }
      else if (m_shape == Shape::FillCircle) {
        s_tft->drawCircle(m_x, m_y, r, colour);
      }
    }
  }
  else if (m_isBitmapButton) {
    int borderX = m_x - 5;
    int borderY = m_y - 5;
    int borderW = m_w + 5*2;
    int borderH = m_h + 5*2;
    s_tft->drawRect(borderX, borderY, borderW, borderH, colour);
  }
}


void gfxButton::drawBorder(int width) {
  // if no colour specified use background colour
  // unsigned long colour = getBackgroundColour();
  unsigned long colour = m_defaultColour;
  // but if button has a border use default values
  if (m_hasBorder) {
    colour = m_borderColour;
    width = m_borderWidth;
  }

  drawBorder(width, colour);
}


/******************************************************
/          Common Text Rendering Helper
/ Handles text positioning, overdraw, and rendering for
/ all writeText variants.
******************************************************/
void gfxButton::writeTextHelper(const GFXfont &font, unsigned long colour, String btnText, TextAlignX alignX, TextRegionY regionY) {
  if (btnText == "") {
    btnText = m_label == nullptr ? "" : m_label;
  }

  // compute button region based on vertical region
  int btnX = m_x;
  int btnW = m_w;
  int btnY, btnH;
  switch (regionY) {
    case RegionTop:
      btnY = m_y + (m_h / 2);
      btnH = (m_h / 2);
      break;
    case RegionBottom:
      btnY = m_y + m_h;
      btnH = (m_h / 2);
      break;
    case RegionFull:
    default:
      btnY = m_y + m_h;
      btnH = m_h;
      break;
  }

  int16_t textX, textY;
  uint16_t textW, textH;
  s_tft->setFont(&font);
  s_tft->getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int xPad = (btnW - textW) / 2;
  int yPad = (btnH - textH) / 2;
  int xPos, yPos;

  switch (alignX) {
    case AlignLeft:
      xPos = btnX + ceil(btnW * 0.05);
      yPos = btnY - yPad;
      break;
    case AlignRight:
      xPos = (btnX + btnW) - (textW + ceil(btnW * 0.05));
      yPos = btnY - yPad;
      break;
    case AlignCentre:
    default:
      xPos = btnX + xPad;
      yPos = btnY - yPad;
      break;
  }

  renderCachedText(font, colour, btnText, alignX, regionY, xPos, yPos);
}


// TODO support text alignment for triangles
/******************************************************
/          Write Text for Buttons
/ Calculates the m_x,y,w,h dimensions for a piece of text
/ based on font and size and uses this to find the closest
/ centre/left/right aligned point within a button's
/ dimensions to print the text.
******************************************************/
void gfxButton::writeTextCentre(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignCentre, RegionFull);
}


void gfxButton::writeTextTopCentre(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignCentre, RegionTop);
}


void gfxButton::writeTextBottomCentre(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignCentre, RegionBottom);
}


void gfxButton::writeTextTopLeft(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignLeft, RegionTop);
}


void gfxButton::writeTextBottomLeft(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignLeft, RegionBottom);
}


void gfxButton::writeTextLeft(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignLeft, RegionFull);
}


void gfxButton::writeTextRight(const GFXfont &font, unsigned long colour, String btnText) {
  writeTextHelper(font, colour, btnText, AlignRight, RegionFull);
}


void gfxButton::writeTextCircle(const GFXfont &font, unsigned long colour, String btnText) {
  if (btnText == "") {
    btnText = m_label == nullptr ? "" : m_label;
  }
  int btnX = m_x;
  int btnY = m_y + m_h;

  int16_t textX, textY;
  uint16_t textW, textH;
  s_tft->setFont(&font);
  s_tft->getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  // for circles, x and y define centre so offset by half text dimensions
  int xPos = btnX - (textW / 2);
  int yPos = btnY + (textH / 2);

  renderCachedText(
    font, colour, btnText, AlignCentre, RegionCircle, xPos, yPos);
}


uint32_t gfxButton::textHash(const String &text) const {
  uint32_t hash = 2166136261UL;
  for (unsigned int i = 0; i < text.length(); ++i) {
    hash ^= (uint8_t)text[i];
    hash *= 16777619UL;
  }
  return hash;
}


unsigned long gfxButton::textBackgroundColour() const {
  if (m_shape == Shape::FillRect ||
      m_shape == Shape::FillRoundRect ||
      m_shape == Shape::FillCircle) {
    return getButtonColour();
  }
  return getBackgroundColour();
}


void gfxButton::eraseTextRegion(TextRegionY region) {
  TextRenderState &state = m_textCache[textCacheSlot(region)];
  if (!state.valid || state.region != region) return;

  const bool circle =
    m_shape == Shape::DrawCircle || m_shape == Shape::FillCircle;
  const int buttonLeft = circle ? m_x - m_r : m_x;
  const int buttonTop = circle ? m_y - m_r : m_y;
  const int buttonRight = circle ? m_x + m_r + 1 : m_x + m_w;
  const int buttonBottom = circle ? m_y + m_r + 1 : m_y + m_h;
  const int left = max(max(0, buttonLeft), (int)state.boundsX);
  const int top = max(max(0, buttonTop), (int)state.boundsY);
  const int right = min(
    min(g_screenWidth, buttonRight),
    (int)state.boundsX + (int)state.boundsW);
  const int bottom = min(
    min(g_screenHeight, buttonBottom),
    (int)state.boundsY + (int)state.boundsH);
  if (right > left && bottom > top) {
    s_tft->fillRect(
      left, top, right - left, bottom - top, textBackgroundColour());
  }
  state.valid = false;
}


uint8_t gfxButton::textCacheSlot(TextRegionY region) const {
  return region == RegionBottom ? 1 : 0;
}


void gfxButton::prepareTextRegion(TextRegionY region) {
  if (region == RegionFull || region == RegionCircle) {
    if (m_textCache[0].valid) {
      eraseTextRegion(m_textCache[0].region);
    }
    if (m_textCache[1].valid) {
      eraseTextRegion(m_textCache[1].region);
    }
    return;
  }

  if (region == RegionTop) {
    if (m_textCache[0].valid &&
        (m_textCache[0].region == RegionFull ||
         m_textCache[0].region == RegionCircle)) {
      eraseTextRegion(m_textCache[0].region);
      if (m_textCache[1].valid) {
        eraseTextRegion(m_textCache[1].region);
      }
    }
    else {
      eraseTextRegion(RegionTop);
    }
    return;
  }

  if (m_textCache[0].valid &&
      (m_textCache[0].region == RegionFull ||
       m_textCache[0].region == RegionCircle)) {
    eraseTextRegion(m_textCache[0].region);
  }
  eraseTextRegion(RegionBottom);
}


void gfxButton::renderCachedText(
    const GFXfont &font,
    unsigned long colour,
    const String &text,
    TextAlignX alignX,
    TextRegionY regionY,
    int16_t cursorX,
    int16_t cursorY) {
  TextRenderState &state = m_textCache[textCacheSlot(regionY)];
  const uint32_t hash = textHash(text);
  if (state.valid &&
      state.region == regionY &&
      state.textHash == hash &&
      state.font == &font &&
      state.colour == colour &&
      state.alignment == alignX &&
      state.cursorX == cursorX &&
      state.cursorY == cursorY) {
    return;
  }

  prepareTextRegion(regionY);
  s_tft->setFont(&font);
  s_tft->setTextColor(colour);
  s_tft->setCursor(cursorX, cursorY);
  s_tft->print(text);

  state.valid = true;
  state.region = regionY;
  state.textHash = hash;
  state.font = &font;
  state.colour = colour;
  state.alignment = alignX;
  state.cursorX = cursorX;
  state.cursorY = cursorY;
  s_tft->getTextBounds(
    text,
    cursorX,
    cursorY,
    &state.boundsX,
    &state.boundsY,
    &state.boundsW,
    &state.boundsH);
}


void gfxButton::invalidateTextCache() {
  for (int i = 0; i < TextCacheSlots; ++i) {
    m_textCache[i].valid = false;
  }
}


// use this function to change the label assigned to a button
// if you use a writeText function before updating the label,
// it will cause issues when updating other text on the button
void gfxButton::updateLabel(const char* label) {
  m_label = label;
}


// use this function to change the default colour assigned
// to a button. Useful when a button can have different states
// that may depend on other variables
void gfxButton::updateColour(unsigned long colour) {
  m_defaultColour = colour;
}


// use this function to change the bitmap assigned
// to a bitmap button. Useful when a button can have different
// states that may depend on other variables
void gfxButton::updateBitmap(const unsigned char* bitmap) {
  m_bitmap = bitmap;
}


// use this function to change the bitmap assigned
// to a bitmap button. Useful when a button can have different
// states that may depend on other variables
void gfxButton::updateRGBBitmap(const uint16_t* bitmap) {
  m_rgb_bitmap = bitmap;
}


// Hide the button, erase its drawn area, and disable touch handling.
void gfxButton::hideButton() {
  if (m_isHidden) {
    return;
  }

  m_isHidden = true;
  invalidateTextCache();

  switch (m_shape) {
    case Shape::DrawRect:
      s_tft->drawRect(m_x, m_y, m_w, m_h, g_backgroundColour);
      break;
    case Shape::FillRect:
    case Shape::Blank:
    case Shape::Bitmap:
    case Shape::RGBBitmap:
    case Shape::SDBitmap:
      s_tft->fillRect(m_x, m_y, m_w, m_h, g_backgroundColour);
      break;
    case Shape::DrawRoundRect:
      s_tft->drawRoundRect(m_x, m_y, m_w, m_h, m_r, g_backgroundColour);
      break;
    case Shape::FillRoundRect:
      s_tft->fillRoundRect(m_x, m_y, m_w, m_h, m_r, g_backgroundColour);
      break;
    case Shape::DrawCircle:
      s_tft->drawCircle(m_x, m_y, m_r, g_backgroundColour);
      break;
    case Shape::FillCircle:
      s_tft->fillCircle(m_x, m_y, m_r, g_backgroundColour);
      break;
    case Shape::Vacant:
      break;
  }
}


// Show and redraw a hidden button.
void gfxButton::showButton() {
  drawButton();
}


// Change visibility without redrawing or erasing when the state is unchanged.
void gfxButton::setVisible(bool visible) {
  if (visible == !m_isHidden) {
    return;
  }
  if (visible) {
    showButton();
  }
  else {
    hideButton();
  }
}


// check if button is hidden
bool gfxButton::isHidden() const {
  return m_isHidden;
}


unsigned long gfxButton::getButtonColour() const {
  if (m_buttonColour == 0) {
    return m_defaultColour;
  }
  return m_buttonColour;
}


void gfxButton::setButtonColour(unsigned long colour) {
  m_buttonColour = colour;
}


/******************************************************
/           Declare Background Colour
/ Declare background colour variable as it is global.
/ Used to fill over text when the button type is an
/ outline of a shape and not a solid shape.
******************************************************/
unsigned long gfxButton::g_backgroundColour = 0x0000;

unsigned long gfxButton::getBackgroundColour() const {
  return g_backgroundColour;
}


void gfxButton::setBackgroundColour(unsigned long colour) {
  g_backgroundColour = colour;
}


// change whether button is tactile or not
void gfxButton::setTactile(bool tactile) {
  m_isTactile = tactile;
}


// check if button is tactile, i.e. can be pressed/change state
bool gfxButton::isTactile() const {
  return m_isTactile;
}


/******************************************************
/                Init new Toggle
/ Adds toggle-like responsiveness for a button.
/ Allows triggering that button with toggle
/ functionality and call a function on state change
******************************************************/
void gfxButton::addToggle(void (*btnFunction)(bool state), int paddingPercent) {
  // set m_xMin, m_xMax, m_yMin, m_yMax
  setTouchBoundary(m_x, m_y, m_w, m_h, m_r, paddingPercent);
  // initialise button as off
  setButtonActive(false);

  m_xMin = vals.xMin;
  m_xMax = vals.xMax;
  m_yMin = vals.yMin;
  m_yMax = vals.yMax;
  m_isMomentaryButton = false;
  m_lastStateChange = 0UL;
  m_buttonToggleDelay = 0UL;
  m_buttonMomentaryDelay = 0UL;
  m_boolFunction = *btnFunction;
  m_returnLabel = false;
}


/******************************************************
/                Init new Momentary
/ Adds momentary-like responsiveness for a button.
/ Allows triggering that button with momentary
/ functionality and call a function on state change
******************************************************/
void gfxButton::addMomentary(void (*btnFunction)(bool state), int paddingPercent) {
  // set m_xMin, m_xMax, m_yMin, m_yMax
  setTouchBoundary(m_x, m_y, m_w, m_h, m_r, paddingPercent);
  // initialise button as off
  setButtonActive(false);

  m_xMin = vals.xMin;
  m_xMax = vals.xMax;
  m_yMin = vals.yMin;
  m_yMax = vals.yMax;
  m_isMomentaryButton = true;
  m_lastStateChange = 0UL;
  m_buttonToggleDelay = 0UL;
  m_buttonMomentaryDelay = 0UL;
  m_boolFunction = *btnFunction;
  m_returnLabel = false;
}


/******************************************************
/                Init new Input Key
/ Adds momentary-like responsiveness for a button. The
/ button will function as an input key, using the label
/ of the button as the argument in the button's
/ function. This makes it easy to implement a keyboard
/ of buttons as you require only one catch function on
/ the client side.
******************************************************/
void gfxButton::addInputKey(void (*btnFunction)(const char* label), int paddingPercent) {
  // set m_xMin, m_xMax, m_yMin, m_yMax
  setTouchBoundary(m_x, m_y, m_w, m_h, m_r, paddingPercent);
  // initialise button as off
  setButtonActive(false);

  m_xMin = vals.xMin;
  m_xMax = vals.xMax;
  m_yMin = vals.yMin;
  m_yMax = vals.yMax;
  m_isMomentaryButton = true;
  m_lastStateChange = 0UL;
  m_buttonToggleDelay = 0UL;
  m_buttonMomentaryDelay = 0UL;
  m_charFunction = *btnFunction;
  m_returnLabel = true;
}


/******************************************************
/         Set Touch Boundary for Button
/ Determines min and max XY values for where a
/ touch needs to register to trigger the button
/ Boundary size can be modified by paddingPercent value
******************************************************/
void gfxButton::setTouchBoundary(int x, int y, int w, int h, int r, int paddingPercent) {
  // if reading bitmap from sd card, width and height are not known at initialisation
  if (m_shape == Shape::SDBitmap) {
    setBitmapDimensions(m_filename);
    w = m_w;
    h = m_h;
  }
  // if w and h dimensions are zero and radius > 0, then button is circle
  if (w == 0 && h == 0 && r > 0) {
    // get new padded radius dimension
    int _pad_r = ceil(r * (100 + paddingPercent)/100);
    // circles are drawn from the centre point
    m_xMin = x - _pad_r;
    m_xMax = x + _pad_r;
    m_yMin = y - _pad_r;
    m_yMax = y + _pad_r;
  }
  // else button must be a rectangle
  else {
    // get new w,h dimensions
    int _pad_w = ceil((w * (100 + paddingPercent))/100);
    int _pad_h = ceil((h * (100 + paddingPercent))/100);
    // offset xy position by half the difference between original dimensions and padded dimensions
    m_xMin = x - (_pad_w - w)/2;
    m_yMin = y - (_pad_h - h)/2;
    // add the padded dimensions to the new xy positions
    m_xMax = m_xMin + _pad_w;
    m_yMax = m_yMin + _pad_h;
  }
  // struct touchBoundary vals;
  // limit possible boundary values by screen size
  vals.xMin = m_xMin >= 0 ? m_xMin : 0;
  vals.yMin = m_yMin >= 0 ? m_yMin : 0;
  vals.xMax = m_xMax <= g_screenWidth ? m_xMax : g_screenWidth;
  vals.yMax = m_yMax <= g_screenHeight ? m_yMax : g_screenHeight;
  
  // return vals; // Return the local structure
}


/******************************************************
/             Check Button for Touch
/ Checks against current screen shown to user as well
/ as how long it has been since the previous touch and
/ if that is longer than the specified debounce time.
/ Will then check if XY co-ordinates are within button
/ boundary. Toggle  requires cooloff time before next
/ trigger.
******************************************************/
void gfxButton::contains(int x, int y) {
  if (!m_isTactile || m_isHidden) {
    return;
  }
  if ((x >= m_xMin && x <= m_xMax) && (y >= m_yMin && y <= m_yMax)) {
    actuateButton(true);
  }
}


void gfxButton::actuateButton(bool actuate) {
  if (actuate && m_isTactile && !m_isHidden) {
    if (m_isMomentaryButton) {
      unsigned long delay = m_buttonMomentaryDelay > 0 ? m_buttonMomentaryDelay : g_momentaryDelay;
      if (millis() - m_lastStateChange >= delay) {
        m_lastStateChange = millis();
        // set button state
        setButtonActive(true); // momentary buttons are always active when pressed
        // run function tied to button
        executeFunction();
      }
    }
    else if (!m_isMomentaryButton && isToggleActive() == false) {
      unsigned long delay = m_buttonToggleDelay > 0 ? m_buttonToggleDelay : g_toggleDelay;
      if (millis() - m_lastStateChange >= delay) {
        m_lastStateChange = millis();
        // set button state
        setButtonActive(!isButtonActive());
        // set toggle flag state
        // reset on client side when no touch detected
        setToggleActive(true);
        // run function tied to button
        executeFunction();
      }
    }
  }
}


/******************************************************
/            Run function tied to Button
/ Run the function assigned to that button when it
/ has been triggered by a touch.
******************************************************/
void gfxButton::executeFunction() {
  if (m_returnLabel) {
    m_charFunction(m_label);
  }
  else {
    m_boolFunction(isButtonActive());
  }
}


/******************************************************
/               Get Button State
/ Get the latest state of the button, false if inactive.
******************************************************/
bool gfxButton::isButtonActive() const {
  return m_buttonActive;
}


/******************************************************
/               Set Button State
/ Set the latest state of the button, false if inactive.
******************************************************/
void gfxButton::setButtonActive(bool active) {
  m_buttonActive = active;
}

/******************************************************
/           Declare Debouncing Delay Variables
/ Declare variables for debouncing toggle and momentary
/ buttons. These values are shared across instances and
/ will be used by all buttons of that type.
******************************************************/
unsigned long gfxButton::g_toggleDelay = 0;
unsigned long gfxButton::g_momentaryDelay = 0;


/******************************************************
/              Set Debouncing Delay Values
/ Set debouncing delay for toggle buttons.
******************************************************/
void gfxButton::setToggleDelay(unsigned long delay) {
  g_toggleDelay = delay;
}


/******************************************************
/              Set Debouncing Delay Values
/ Set debouncing delay for momentary buttons.
******************************************************/
void gfxButton::setMomentaryDelay(unsigned long delay) {
  g_momentaryDelay = delay;
}


void gfxButton::setButtonToggleDelay(unsigned long delay) {
  m_buttonToggleDelay = delay;
}


void gfxButton::setButtonMomentaryDelay(unsigned long delay) {
  m_buttonMomentaryDelay = delay;
}

// delcare and initialise global variable for toggle state
bool gfxButton::g_toggleActive = false;

/******************************************************
/              Set Toggle Flag
******************************************************/
void gfxButton::setToggleActive(bool active) {
  g_toggleActive = active;
}


/******************************************************
/              Get Toggle Flag
/ Get state of toggle flag. Set when a toggle button
/ is active and needs to be reset by 0 touch reading.
******************************************************/
bool gfxButton::isToggleActive() const {
  return g_toggleActive;
}

/******************************************************
/           Declare Screen Dimensions
******************************************************/
int gfxButton::g_screenWidth = 480;
int gfxButton::g_screenHeight = 320;

void gfxButton::setScreenSize(int width, int height) {
  g_screenWidth = width;
  g_screenHeight = height;
}


uint16_t gfxButton::read16(File& f) {
  uint16_t result;
  f.read((uint8_t*)&result, sizeof(result));
  return result;
}

uint32_t gfxButton::read32(File& f) {
  uint32_t result;
  f.read((uint8_t*)&result, sizeof(result));
  return result;
}


uint8_t gfxButton::drawBMPFromSD(const char *nm, int x, int y) {
  File bmpFile;
  int bmpWidth, bmpHeight;    // W+H in pixels
  uint8_t bmpDepth;           // Bit depth (currently must be 24, 16, 8, 4, 1)
  uint32_t bmpImageoffset;    // Start of image data in file
  uint32_t rowSize;           // Not always = bmpWidth; may have padding
  uint8_t sdbuffer[3 * BUFFPIXEL];    // pixel in buffer (R+G+B per pixel)
  uint16_t lcdbuffer[(1 << PALETTEDEPTH) + BUFFPIXEL], *palette = NULL;
  uint8_t bitmask, bitshift;
  boolean flip = true;        // BMP is stored bottom-to-top
  int w, h, row, col, lcdbufsiz = (1 << PALETTEDEPTH) + BUFFPIXEL;
  size_t buffidx = sizeof(sdbuffer);
  uint32_t pos;               // seek position
  boolean is565 = false;      //

  uint16_t bmpID;
  uint16_t n;                 // blocks read
  uint8_t ret;

  if ((x >= s_tft->width()) || (y >= s_tft->height()))
    return 1;               // off screen

  bmpFile = s_sd->open(nm);   // Parse BMP header
  if (!bmpFile) {
    return 2;
  }
  bmpID = read16(bmpFile);    // BMP signature
  (void) read32(bmpFile);     // Read & ignore file size
  (void) read32(bmpFile);     // Read & ignore creator bytes
  bmpImageoffset = read32(bmpFile);       // Start of image data
  (void) read32(bmpFile);     // Read & ignore DIB header size
  bmpWidth = read32(bmpFile);
  bmpHeight = read32(bmpFile);
  n = read16(bmpFile);        // # planes -- must be '1'
  bmpDepth = read16(bmpFile); // bits per pixel
  pos = read32(bmpFile);      // format
  if (bmpID != 0x4D42) ret = 2; // bad ID
  else if (n != 1) ret = 3;   // too many planes
  else if (pos != 0 && pos != 3) ret = 4; // format: 0 = uncompressed, 3 = 565
  else if (bmpDepth < 16 && bmpDepth > PALETTEDEPTH) ret = 5; // palette 
  else {
    bool first = true;
    is565 = (pos == 3);               // ?already in 16-bit format
    // BMP rows are padded (if needed) to 4-byte boundary
    rowSize = (bmpWidth * bmpDepth / 8 + 3) & ~3;
    if (bmpHeight < 0) {              // If negative, image is in top-down order.
      bmpHeight = -bmpHeight;
      flip = false;
    }

    w = bmpWidth;
    h = bmpHeight;
    if ((x + w) >= s_tft->width())       // Crop area to be loaded
      w = s_tft->width() - x;
    if ((y + h) >= s_tft->height())      //
      h = s_tft->height() - y;

    if (bmpDepth <= PALETTEDEPTH) {   // these modes have separate palette
      //bmpFile.seek(BMPIMAGEOFFSET); //palette is always @ 54
      bmpFile.seek(bmpImageoffset - (4<<bmpDepth)); //54 for regular, diff for colorsimportant
      bitmask = 0xFF;
      if (bmpDepth < 8)
        bitmask >>= bmpDepth;
      bitshift = 8 - bmpDepth;
      n = 1 << bmpDepth;
      lcdbufsiz -= n;
      palette = lcdbuffer + lcdbufsiz;
      for (col = 0; col < n; col++) {
        pos = read32(bmpFile);    //map palette to 5-6-5
        palette[col] = ((pos & 0x0000F8) >> 3) | ((pos & 0x00FC00) >> 5) | ((pos & 0xF80000) >> 8);
      }
    }

    // Set TFT address window to clipped image bounds
    s_tft->setAddrWindow(x, y, x + w - 1, y + h - 1);
    for (row = 0; row < h; row++) { // For each scanline...
      // Seek to start of scan line.  It might seem labor-
      // intensive to be doing this on every line, but this
      // method covers a lot of gritty details like cropping
      // and scanline padding.  Also, the seek only takes
      // place if the file position actually needs to change
      // (avoids a lot of cluster math in SD library).
      uint8_t r, g, b;
      int lcdidx, lcdleft;
      if (flip)   // Bitmap is stored bottom-to-top order (normal BMP)
          pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
      else        // Bitmap is stored top-to-bottom
          pos = bmpImageoffset + row * rowSize;
      if (bmpFile.position() != pos) { // Need seek?
          bmpFile.seek(pos);
          buffidx = sizeof(sdbuffer); // Force buffer reload
      }

      for (col = 0; col < w; ) {  //pixels in row
        lcdleft = w - col;
        if (lcdleft > lcdbufsiz) lcdleft = lcdbufsiz;
        for (lcdidx = 0; lcdidx < lcdleft; lcdidx++) { // buffer at a time
          uint16_t color = 0;
          // Time to read more pixel data?
          if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
              r = 0;
          }
          switch (bmpDepth) {          // Convert pixel from BMP to TFT format
            case 24:
              b = sdbuffer[buffidx++];
              g = sdbuffer[buffidx++];
              r = sdbuffer[buffidx++];
              color = s_tft->color565(r, g, b);
              break;
            case 16:
              b = sdbuffer[buffidx++];
              r = sdbuffer[buffidx++];
              if (is565)
                color = (r << 8) | (b);
              else
                color = (r << 9) | ((b & 0xE0) << 1) | (b & 0x1F);
              break;
            case 1:
            case 4:
            case 8:
              if (r == 0)
                b = sdbuffer[buffidx++], r = 8;
              color = palette[(b >> bitshift) & bitmask];
              r -= bmpDepth;
              b <<= bmpDepth;
              break;
          }
          lcdbuffer[lcdidx] = color;
        }
        s_tft->pushColors(lcdbuffer, lcdidx, first);
        first = false;
        col += lcdidx;
      }           // end cols
    }               // end rows
    s_tft->setAddrWindow(0, 0, s_tft->width() - 1, s_tft->height() - 1); //restore full screen
    ret = 0;        // good render
  }
  bmpFile.close();
  return (ret);
}


struct bmp_file_header_t {
  uint16_t signature;
  uint32_t file_size;
  uint16_t reserved[2];
  uint32_t image_offset;
};

struct bmp_image_header_t {
  uint32_t header_size;
  uint32_t image_width;
  uint32_t image_height;
  uint16_t color_planes;
  uint16_t bits_per_pixel;
  uint32_t compression_method;
  uint32_t image_size;
  uint32_t horizontal_resolution;
  uint32_t vertical_resolution;
  uint32_t colors_in_palette;
  uint32_t important_colors;
};


/******************************************************
/   Parse Bitmap on SD Card to get width and height
******************************************************/
void gfxButton::setBitmapDimensions(const char* filename) {
  File bmpImage = s_sd->open(filename);
  bmpImage.seek(0x12);
  m_w = read32(bmpImage);  // BMP width is 32-bit little-endian at offset 0x12
  bmpImage.seek(0x16);
  int32_t h = read32(bmpImage);  // BMP height is 32-bit LE at 0x16, can be negative (top-down)
  m_h = (h < 0) ? -h : h;
  bmpImage.close();
}
