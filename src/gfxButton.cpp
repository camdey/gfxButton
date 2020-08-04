#include "Arduino.h"
#include "gfxButton.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"


/******************************************************
/              Create a Button Instance
/ Creates a button instance for GFX shapes that will allow
/ you to add touch functionality for using the shape
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton() {};


gfxButton::gfxButton(String drawType, int x, int y, int w, int h, int r, unsigned long defaultColour, String screen) {
  m_drawType = drawType;
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = r;
  m_defaultColour = defaultColour;
  m_screen = screen;
  m_isBitmapButton = false;
}


/******************************************************
/          Create a blank Button Instance
/ Creates a button instance for GFX shapes that will allow
/ you to add touch functionality for using the shape
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(int x, int y, int w, int h, String screen) {
  m_drawType = "blank";
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = 0;
  m_defaultColour = 0;
  m_screen = screen;
  m_isBitmapButton = false;
}


/******************************************************
/           Create a Bitmap Button Instance
/ Creates a button instance for bitmaps that will allow
/ you to add touch functionality for using the bitmap
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, String screen) {
  m_bitmap = bitmap;
  m_drawType = "bitmap";
  m_x = x;
  m_y = y;
  m_w = w;
  m_h = h;
  m_r = 0;
  m_defaultColour = defaultColour;
  m_screen = screen;
  m_isBitmapButton = true;
}


/******************************************************
/                    Init a Button
/ Initiates a button instance for GFX shapes, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initButton(String drawType, int x, int y, int w, int h, int r, unsigned long defaultColour, String screen) {
  return gfxButton(drawType, x, y, w, h, r, defaultColour, screen);
}


/******************************************************
/                Init a blank Button
/ Initiates a button instance for GFX shapes, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initBlankButton(int x, int y, int w, int h, String screen) {
  return gfxButton(x, y, w, h, screen);
}


/******************************************************
/               Init a bitmap Button
/ Initiates a button instance for bitmaps, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initBitmapButton(const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour, String screen) {
  return gfxButton(bitmap, x, y, w, h, defaultColour, screen);
}


/******************************************************
/               Draw Button Shapes
/ Draws a button based on the GFX Library commands.
/ Can draw different types of buttons based on the
/ m_drawType parameter set for the button.
******************************************************/
void gfxButton::drawButton(MCUFRIEND_kbv tft) {
  if (m_drawType == "drawRect") {
    tft.drawRect(m_x, m_y, m_w, m_h, m_defaultColour);
  }
  else if (m_drawType == "fillRect") {
    tft.fillRect(m_x, m_y, m_w, m_h, m_defaultColour);
  }
  else if (m_drawType == "drawRoundRect") {
    tft.drawRoundRect(m_x, m_y, m_w, m_h, m_r, m_defaultColour);
  }
  else if (m_drawType == "fillRoundRect") {
    tft.fillRoundRect(m_x, m_y, m_w, m_h, m_r, m_defaultColour);
  }
  else if (m_drawType == "drawCircle") {
    tft.drawCircle(m_x, m_y, m_r, m_defaultColour);
  }
  else if (m_drawType == "fillCircle") {
    tft.fillCircle(m_x, m_y, m_r, m_defaultColour);
  }
  else if (m_drawType == "bitmap") {
    tft.drawBitmap(m_x, m_y, m_bitmap, m_w, m_h, m_defaultColour);
  }
  // TODO support triangles
  // else if (button.m_drawType == "drawTriangle") {
  //   tft.drawTriangle(button.m_x, button.m_y, button.m_w, button.m_h, button.m_defaultColour);
  // }
  // else if (button.m_drawType == "fillTriangle") {
  //   tft.fillTriangle(button.m_x, button.m_y, button.m_w, button.m_h, button.m_defaultColour);
  // }

  // store button colour, used for overwriting text
  setButtonColour(m_defaultColour);

  if (m_hasBorder == true) {
    drawBorder(tft, m_borderWidth, m_borderColour);
  }
}


/******************************************************
/               Draw Button Shapes
/ Draws a button based on the GFX Library commands.
/ Can draw different types of buttons based on the
/ m_drawType parameter set for the button.
******************************************************/
void gfxButton::drawButton(MCUFRIEND_kbv tft, unsigned long colour) {
  if (m_drawType == "drawRect") {
    tft.drawRect(m_x, m_y, m_w, m_h, colour);
  }
  else if (m_drawType == "fillRect") {
    tft.fillRect(m_x, m_y, m_w, m_h, colour);
  }
  else if (m_drawType == "drawRoundRect") {
    tft.drawRoundRect(m_x, m_y, m_w, m_h, m_r, colour);
  }
  else if (m_drawType == "fillRoundRect") {
    tft.fillRoundRect(m_x, m_y, m_w, m_h, m_r, colour);
  }
  else if (m_drawType == "drawCircle") {
    tft.drawCircle(m_x, m_y, m_r, colour);
  }
  else if (m_drawType == "fillCircle") {
    tft.fillCircle(m_x, m_y, m_r, colour);
  }
  else if (m_drawType == "bitmap") {
    tft.drawBitmap(m_x, m_y, m_bitmap, m_w, m_h, colour);
  }
  // TODO support triangles
  // else if (button.m_drawType == "drawTriangle") {
  //   tft.drawTriangle(button.m_x, button.m_y, button.m_w, button.m_h, colour);
  // }
  // else if (button.m_drawType == "fillTriangle") {
  //   tft.fillTriangle(button.m_x, button.m_y, button.m_w, button.m_h, colour);
  // }

  // store button colour, used for overwriting text
  setButtonColour(colour);

  if (m_hasBorder == true) {
    drawBorder(tft, m_borderWidth, m_borderColour);
  }
}


/******************************************************
/               Draw New Bitmap
/ Draws a new bitmap image for an existing button
/ Allows you to change the bitmap image depending on
/ the state of the button.
******************************************************/
void gfxButton::drawNewBitmap(MCUFRIEND_kbv tft, const unsigned char* bitmap, unsigned long colour) {
  // fill over previous bitmap/button
  tft.fillRect(m_x, m_y, m_w, m_h, getBackgroundColour());
  // draw new bitmap
  tft.drawBitmap(m_x, m_y, bitmap, m_w, m_h, colour);

  // store button colour, used for overwriting text
  setButtonColour(colour);
}


void gfxButton::addBorder(int width, unsigned long colour) {
  if (m_drawType == "fillRect" || m_drawType == "fillRoundRect" || m_drawType == "fillCircle") {
    m_hasBorder = true;
    m_borderWidth = width;
    m_borderColour = colour;
  }
}


void gfxButton::drawBorder(MCUFRIEND_kbv tft, int width, unsigned long colour) {
  if (!m_isBitmapButton) {
    for (int i = 0; i < width; i++) {
      int x = m_x + i;
      int y = m_y + i;
      int w = m_w - i*2;
      int h = m_h - i*2;
      int r = m_r - i;

      if (m_drawType == "fillRect") {
        tft.drawRect(x, y, w, h, colour);
      }
      else if (m_drawType == "fillRoundRect") {
        tft.drawRoundRect(x, y, w, h, r, colour);
      }
      else if (m_drawType == "fillCircle") {
        tft.drawCircle(m_x, m_y, r, colour);
      }
    }
  }
  else if (m_isBitmapButton) {
    int borderX = m_x - 5;
    int borderY = m_y - 5;
    int borderW = m_w + 5*2;
    int borderH = m_h + 5*2;
    tft.drawRect(borderX, borderY, borderW, borderH, colour);
  }
}


void gfxButton::drawBorder(MCUFRIEND_kbv tft, int width) {
  // if no colour specified use background colour
  unsigned long colour = getBackgroundColour();
  // but if button has a border use default values
  if (m_hasBorder) {
    colour = m_borderColour;
    width = m_borderWidth;
  }

  drawBorder(tft, width, colour);
}


// TODO support text alignment for triangles
/******************************************************
/          Write Text for Buttons
/ Calculates the m_x,y,w,h dimensions for a piece of text
/ based on font and size and uses this to find the closest
/ centre/left/right aligned point within a button's
/ dimensions to print the text.
******************************************************/
void gfxButton::writeTextCentre(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + m_h; // text is printed from bottom left so add height value to y
  int btnW = m_w;
  int btnH = m_h;

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int xPad;
  int yPad;
  int xPos;
  int yPos;

  // find space left over after text added
  // divide by two to get x and y padding
  xPad = (btnW - textW) / 2;
  yPad = (btnH - textH) / 2;

  // centre align text
  xPos = btnX + xPad;
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "centre", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/          Top centre align text on button
******************************************************/
void gfxButton::writeTextTopCentre(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + (m_h / 2);  // text is printed from bottom left so add half height value to y
  int btnW = m_w;
  int btnH = (m_h / 2);      // treat button as if it is only half the height

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int xPad, yPad, xPos, yPos;

  // find space left over after text added
  // divide by two to get x and y padding
  xPad = (btnW - textW) / 2;
  yPad = (btnH - textH) / 2;

  // centre align text
  xPos = btnX + xPad;
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "centre", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/          Bottom centre align text on button
******************************************************/
void gfxButton::writeTextBottomCentre(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + m_h;    // text is printed from bottom left so add height value to y
  int btnW = m_w;
  int btnH = (m_h / 2);  // treat button as if it is only half the height

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int xPad, yPad, xPos, yPos;

  // find space left over after text added
  // divide by two to get x and y padding
  xPad = (btnW - textW) / 2;
  yPad = (btnH - textH) / 2;

  // centre align text
  xPos = btnX + xPad;
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "centre", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/          Top left align text on button
******************************************************/
void gfxButton::writeTextTopLeft(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + (m_h / 2);  // text is printed from bottom left so add half height value to y
  int btnW = m_w;
  int btnH = (m_h / 2);      // treat button as if it is only half the height

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int yPad, xPos, yPos;

  // find space left over after text added
  // divide by two to ge y padding
  yPad = (btnH - textH) / 2;

  // left align text, padded by 5% of button width
  xPos = btnX + ceil(btnW * 0.05);
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "left", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/          Bottom centre align text on button
******************************************************/
void gfxButton::writeTextBottomLeft(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + m_h;    // text is printed from bottom left so add height value to y
  int btnW = m_w;
  int btnH = (m_h / 2);  // treat button as if it is only half the height

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int yPad, xPos, yPos;

  // find space left over after text added
  // divide by two to get y padding
  yPad = (btnH - textH) / 2;

  // left align text, padded by 5% of button width
  xPos = btnX + ceil(btnW * 0.05);
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "left", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/           Left align text on button
******************************************************/
void gfxButton::writeTextLeft(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + m_h; // text is printed from bottom left so add height value to y
  int btnW = m_w;
  int btnH = m_h;

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int yPad, xPos, yPos;

  // find space left over after text added
  // divide by two to y padding
  yPad = (btnH - textH) / 2;

  // left align text, padded by 5% of button width
  xPos = btnX + ceil(btnW * 0.05);
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "left", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/           Right align text on button
******************************************************/
void gfxButton::writeTextRight(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + m_h; // text is printed from bottom left so add height value to y
  int btnW = m_w;
  int btnH = m_h;

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int yPad, xPos, yPos;

  // find space left over after text added
  // divide by two to get y padding
  yPad = (btnH - textH) / 2;

  // right align text
  xPos = (btnX + btnW) - (textW + ceil(btnW * 0.05));
  yPos = btnY - yPad;

  replaceButtonText(tft, btnText, "right", btnX, btnY, btnW, btnH);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}


/******************************************************
/         Centre align text on circle button
******************************************************/
void gfxButton::writeTextCircle(MCUFRIEND_kbv tft, GFXfont font, String btnText, unsigned long colour) {
  int btnX = m_x;
  int btnY = m_y + m_h; // text is printed from bottom left so add height value to y

  int16_t textX, textY;
  uint16_t textW, textH;
  // set font to get text size
  tft.setFont(&font);
  // set cursor to 0 as only text box dimensions required
  tft.getTextBounds(btnText, 0, 0, &textX, &textY, &textW, &textH);

  int xPad, yPad, xPos, yPos;

  // for cicles, x and y define centre so divide
  // text w/h by two to offset centre point
  xPad = (textW / 2);
  yPad = (textH / 2);

  xPos = btnX - xPad;
  yPos = btnY + yPad;

  replaceButtonText(tft, btnText, "centre", btnX, btnY);
  setPreviousText(btnText);

  tft.setTextColor(colour);
  tft.setCursor(xPos, yPos);
  tft.print(btnText);
}

// TODO - unsure if supports left/right aligned text buttons
/******************************************************
/               Replace Button Text
/ Replaces the previous text on a button with the
/ colour of the button before new text is written to it
******************************************************/
void gfxButton::replaceButtonText(MCUFRIEND_kbv tft, String newText, String aligned, int btnX, int btnY, int btnW, int btnH) {
  // get previous text string and colour for this button
  String _prevText = getPreviousText();

  // only replace if there is text to replace and it's different from current text
  if (_prevText.length() > 0 && _prevText != newText) {
    unsigned long m_buttonColour = getButtonColour();
    unsigned long _backgroundColour = getBackgroundColour();
    int16_t textX, textY;
    uint16_t textW, textH;
    // get size of previous text string
    tft.getTextBounds(_prevText, 0, 0, &textX, &textY, &textW, &textH);
    // calculate previous text x,y co-ordinates
    int _prevXPos = 0, _prevYPos = 0;
    if (aligned == "centre") {
      _prevXPos = btnX + (abs(btnW - textW) / 2) + textX;
      _prevYPos = btnY - (abs(btnH - textH) / 2) + textY;
    }
    else if (aligned == "left") {
      _prevXPos = btnX + ceil(btnW * 0.05) + textX;
      _prevYPos = btnY - (abs(btnH - textH) / 2) + textY;
    }
    else if (aligned == "right") {;
      _prevXPos = (btnX + btnW) - (textW + ceil(btnW * 0.05)) + textX;
      _prevYPos = btnY - (abs(btnH - textH) / 2) + textY;
    }

    int btn_x_right = btnX + btnW;
    int txt_x_right = _prevXPos + textW;
    int btn_y_bottom = btnY + btnH;
    int txt_y_bottom = _prevYPos + textH;
    // if box fill larger than btn dimensions, fix
    if (txt_x_right > btn_x_right) {
      textW = textW - (txt_x_right - btn_x_right);
    }
    if (txt_y_bottom > btn_y_bottom) {
      textH = textH - (txt_y_bottom - btn_y_bottom);
    }

    // if button type not a fill, use specified background colour to fill over previous text
    if (m_drawType == "blank" || m_drawType == "drawRect" || m_drawType == "drawRoundRect" || m_drawType == "drawCircle") {
      tft.fillRect(_prevXPos, _prevYPos, textW, textH, _backgroundColour);
    }
    else {
      tft.fillRect(_prevXPos, _prevYPos, textW, textH, m_buttonColour);
    }
  }
}


String gfxButton::getPreviousText() {
  return m_previousText;
}


void gfxButton::setPreviousText(String _text) {
  m_previousText = _text;
}


unsigned long gfxButton::getButtonColour() {
  if (m_buttonColour == 0) {
    m_buttonColour = m_defaultColour;
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

unsigned long gfxButton::getBackgroundColour() {
  return g_backgroundColour;
}


void gfxButton::setBackgroundColour(unsigned long colour) {
  g_backgroundColour = colour;
}


/******************************************************
/         Constructor for gfxTouch instance
/ Takes gfxButton instance as argument and calculates
/ min/max boundaries for touch registration. Also takes
/ an pointer to a function that should be caLled when
/ the button is pressed.
******************************************************/
gfxTouch::gfxTouch() {};

gfxTouch::gfxTouch(String screen, int xMin, int xMax, int yMin, int yMax, String touchType, void (*btnFunction)(bool state)) {
  m_screen = screen;
  m_xMin = xMin;
  m_xMax = xMax;
  m_yMin = yMin;
  m_yMax = yMax;
  m_touchType = touchType;
  m_lastStateChange = 0UL;
  m_btnFunc = *btnFunction;
}


/******************************************************
/                Init new Toggle
/ Initiates a toggle type instance based on a
/ previously  created button instance. Will allow
/ triggering that button with toggle functionality
/ and call a function on button state change
******************************************************/
gfxTouch gfxTouch::addToggle(gfxButton &button, void (*btnFunction)(bool state), int percent) {
  String screen = button.m_screen;
  String touchType = "toggle";

  // set m_xMin, m_xMax, m_yMin, m_yMax
  setTouchBoundary(button.m_x, button.m_y, button.m_w, button.m_h, button.m_r, percent);
  // initialise button as off
  setButtonActive(false);

  return gfxTouch(screen, vals.xMin, vals.xMax, vals.yMin, vals.yMax, touchType, *btnFunction);
}


/******************************************************
/                Init new Momentary
/ Initiates a momentary type instance based on a
/ previously  created button instance. Will allow
/ triggering that button with momentary functionality
/ and call a function on button state change
******************************************************/
gfxTouch gfxTouch::addMomentary(gfxButton &button, void (*btnFunction)(bool state), int percent) {
  String screen = button.m_screen;
  String touchType = "momentary";

  // set m_xMin, m_xMax, m_yMin, m_yMax
  setTouchBoundary(button.m_x, button.m_y, button.m_w, button.m_h, button.m_r, percent);
  // initialise button as off
  setButtonActive(false);
  
  return gfxTouch(screen, vals.xMin, vals.xMax, vals.yMin, vals.yMax, touchType, *btnFunction);
}


/******************************************************
/         Set Touch Boundary for Button
/ Determines min and max XY values for where a
/ touch needs to register to trigger the button
/ Boundary size can be modified by percent value
******************************************************/
void gfxTouch::setTouchBoundary(int x, int y, int w, int h, int r, int percent) {
  // if w and h dimensions are zero and radius > 0, then button is circle
  if (w == 0 && h == 0 && r > 0) {
    // get new padded radius dimension
    int _pad_r = ceil(r * (100 + percent)/100);
    // circles are drawn from the centre point
    m_xMin = x - _pad_r;
    m_xMax = x + _pad_r;
    m_yMin = y - _pad_r;
    m_yMax = y + _pad_r;
  }
  // else button must be a rectangle
  else {
    // get new w,h dimensions
    int _pad_w = ceil((w * (100 + percent))/100);
    int _pad_h = ceil((h * (100 + percent))/100);
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
void gfxTouch::checkTouchInput(String currentScreen, int touch_x, int touch_y) {
  // if no screen value provided, use currentScreen to bypass check
  m_screen = (m_screen == "") ? currentScreen : m_screen;

  if (m_screen == currentScreen) {
    if ((touch_x >= m_xMin && touch_x <= m_xMax) && (touch_y >= m_yMin && touch_y <= m_yMax)) {
      if (m_touchType == "momentary") {
        if (millis() - m_lastStateChange >= g_momentaryDelay) {
          m_lastStateChange = millis();
          // set button state
          setButtonActive(true); // momentary buttons are always active when pressed
          // run function tied to button
          runButtonFunction();
        }
      }
      else if (m_touchType == "toggle" && isToggleActive() == false) {
        if (millis() - m_lastStateChange >= g_toggleDelay) {
          m_lastStateChange = millis();
          // set button state
          setButtonActive(!isButtonActive());
          // set toggle flag state
          // reset on client side when no touch detected
          setToggleActive(true);
          // run function tied to button
          runButtonFunction();
        }
      }
    }
  }
}


void gfxTouch::checkDigitalInput(String currentScreen, bool isActive) {
  // if no screen value provided, use currentScreen to bypass check
  m_screen = (m_screen == "") ? currentScreen : m_screen;

  if (m_screen == currentScreen && isActive) {
    if (m_touchType == "momentary") {
      if (millis() - m_lastStateChange >= g_momentaryDelay) {
        m_lastStateChange = millis();
        // set button state
        setButtonActive(true); // momentary buttons are always active when pressed
        // run function tied to button
        runButtonFunction();
      }
    }
    else if (m_touchType == "toggle" && isToggleActive() == false) {
      if (millis() - m_lastStateChange >= g_toggleDelay) {
        m_lastStateChange = millis();
        // set button state
        setButtonActive(!isButtonActive());
        // set toggle flag state
        // reset on client side when no touch detected
        setToggleActive(true);
        // run function tied to button
        runButtonFunction();
      }
    }
  }
}


/******************************************************
/            Run function tied to Button
/ Run the function assigned to that button when it
/ has been triggered by a touch.
******************************************************/
void gfxTouch::runButtonFunction() {
  m_btnFunc(isButtonActive());
}


/******************************************************
/               Get Button State
/ Get the latest state of the button, false if inactive.
******************************************************/
bool gfxTouch::isButtonActive() {
  return m_buttonActive;
}


/******************************************************
/               Set Button State
/ Set the latest state of the button, false if inactive.
******************************************************/
void gfxTouch::setButtonActive(bool active) {
  m_buttonActive = active;
}

/******************************************************
/           Declare Debouncing Delay Variables
/ Declare variables for debouncing toggle and momentary
/ buttons. These values are shared across instances and
/ will be used by all buttons of that type.
******************************************************/
unsigned long gfxTouch::g_toggleDelay = 0;
unsigned long gfxTouch::g_momentaryDelay = 0;


/******************************************************
/              Set Debouncing Delay Values
/ Set debouncing delay for toggle buttons.
******************************************************/
void gfxTouch::setToggleDelay(unsigned long delay) {
  g_toggleDelay = delay;
}


/******************************************************
/              Set Debouncing Delay Values
/ Set debouncing delay for momentary buttons.
******************************************************/
void gfxTouch::setMomentaryDelay(unsigned long delay) {
  g_momentaryDelay = delay;
}

// delcare and initialise global variable for toggle state
bool gfxTouch::g_toggleActive = false;

/******************************************************
/              Set Toggle Flag
/ Set debouncing delay for toggle buttons.
******************************************************/
void gfxTouch::setToggleActive(bool active) {
  g_toggleActive = active;
}


/******************************************************
/              Get Toggle Flag
/ Get state of toggle flag. Set when a toggle button
/ is active and needs to be reset by 0 touch reading.
******************************************************/
bool gfxTouch::isToggleActive() {
  return g_toggleActive;
}

/******************************************************
/           Declare Screen Dimensions
******************************************************/
int gfxTouch::g_screenWidth = 480;
int gfxTouch::g_screenHeight = 320;

void gfxTouch::setScreenSize(int width, int height) {
  g_screenWidth = width;
  g_screenHeight = height;
}