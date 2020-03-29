#include "Arduino.h"
#include "gfxButton.h"
#include "Adafruit_GFX.h"
#include "SPI.h"
#include "MCUFRIEND_kbv.h"
#include "TouchScreen.h"


// constructor
gfxButton::gfxButton() {};


/******************************************************
/              Create a Button Instance
/ Creates a button instance for GFX shapes that will allow
/ you to add touch functionality for using the shape
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(String _screen, String _buttonType, int _x, int _y, int _w, int _h, int _r, unsigned long _defaultColour) {
  screen = _screen;
  buttonType = _buttonType;
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  r = _r;
  defaultColour = _defaultColour;
}


/******************************************************
/           Create a Bitmap Button Instance
/ Creates a button instance for bitmaps that will allow
/ you to add touch functionality for using the bitmap
/ as a touch screen button.
******************************************************/
gfxButton::gfxButton(String _screen, const unsigned char* _bitmap, int _x, int _y, int _w, int _h, unsigned long _defaultColour) {
  screen = _screen;
  bitmap = _bitmap;
  buttonType = "bitmap";
  x = _x;
  y = _y;
  w = _w;
  h = _h;
  r = 0;
  defaultColour = _defaultColour;
}


/******************************************************
/                Init a new Button
/ Initiates a button instance for GFX shapes, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initButton(String screen, String buttonType, int x, int y, int w, int h, int r, unsigned long defaultColour) {
  return gfxButton(screen, buttonType, x, y, w, h, r, defaultColour);
}


/******************************************************
/             Init a new Bitmap Button
/ Initiates a button instance for bitmaps, returns input
/ values to instance constructor.
******************************************************/
gfxButton gfxButton::initBitmapButton(String screen, const unsigned char* bitmap, int x, int y, int w, int h, unsigned long defaultColour) {
  return gfxButton(screen, bitmap, x, y, w, h, defaultColour);
}


// TODO can drawButton be one function with button colour property as default?

/******************************************************
/               Draw Button Shapes
/ Draws a button based on the GFX Library commands.
/ Can draw different types of buttons based on the
/ buttonType parameter set for the button.
******************************************************/
void gfxButton::drawButton(MCUFRIEND_kbv _tft, unsigned long _colour) {
  if (buttonType == "drawRect") {
    _tft.drawRect(x, y, w, h, _colour);
  }
  else if (buttonType == "fillRect") {
    _tft.fillRect(x, y, w, h, _colour);
  }
  else if (buttonType == "drawRoundRect") {
    _tft.drawRoundRect(x, y, w, h, r, _colour);
  }
  else if (buttonType == "fillRoundRect") {
    _tft.fillRoundRect(x, y, w, h, r, _colour);
  }
  else if (buttonType == "drawCircle") {
    _tft.drawCircle(x, y, r, _colour);
  }
  else if (buttonType == "fillCircle") {
    _tft.fillCircle(x, y, r, _colour);
  }
  else if (buttonType == "fillCircle") {
    _tft.fillCircle(x, y, r, _colour);
  }
  else if (buttonType == "bitmap") {
    _tft.drawBitmap(x, y, bitmap, w, h, _colour);
  }

  // store button colour, used for overwriting text
  setButtonColour(_colour);

  // TODO support triangles
  // else if (button.buttonType == "drawTriangle") {
  //   _tft.drawTriangle(button.x, button.y, button.w, button.h, colour);
  // }
  // else if (button.buttonType == "fillTriangle") {
  //   _tft.fillTriangle(button.x, button.y, button.w, button.h, colour);
  // }
}


/******************************************************
/               Draw Button Shapes
/ Draws a button based on the GFX Library commands.
/ Can draw different types of buttons based on the
/ buttonType parameter set for the button.
******************************************************/
void gfxButton::drawButton(MCUFRIEND_kbv _tft) {
  if (buttonType == "drawRect") {
    _tft.drawRect(x, y, w, h, defaultColour);
  }
  else if (buttonType == "fillRect") {
    _tft.fillRect(x, y, w, h, defaultColour);
  }
  else if (buttonType == "drawRoundRect") {
    _tft.drawRoundRect(x, y, w, h, r, defaultColour);
  }
  else if (buttonType == "fillRoundRect") {
    _tft.fillRoundRect(x, y, w, h, r, defaultColour);
  }
  else if (buttonType == "drawCircle") {
    _tft.drawCircle(x, y, r, defaultColour);
  }
  else if (buttonType == "fillCircle") {
    _tft.fillCircle(x, y, r, defaultColour);
  }
  else if (buttonType == "bitmap") {
    _tft.drawBitmap(x, y, bitmap, w, h, defaultColour);
  }

  // store button colour, used for overwriting text
  setButtonColour(defaultColour);

  // TODO support triangles
  // else if (button.buttonType == "drawTriangle") {
  //   _tft.drawTriangle(button.x, button.y, button.w, button.h, button.defaultColour);
  // }
  // else if (button.buttonType == "fillTriangle") {
  //   _tft.fillTriangle(button.x, button.y, button.w, button.h, button.defaultColour);
  // }
}


// TODO support text alignment for triangles
/******************************************************
/          Write Text for Buttons
/ Calculates the x,y,w,h dimensions for a piece of text
/ based on font and size and uses this to find the closest
/ centre/left/right aligned point within a button's
/ dimensions to print the text.
******************************************************/
void gfxButton::writeTextCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour) {
  int _btnX = x;
  int _btnY = y + h; // text is printed from bottom left so add height value to y
  int _btnW = w;
  int _btnH = h;

  int16_t _textX, _textY;
  uint16_t _textW, _textH;
  // set font to get text size
  _tft.setFont(&_font);
  // set cursor to 0 as only text box dimensions required
  _tft.getTextBounds(_btnText, 0, 0, &_textX, &_textY, &_textW, &_textH);

  int _xPad;
  int _yPad;
  int _xPos;
  int _yPos;

  // find space left over after text added
  // divide by two to get x and y padding
  _xPad = (_btnW - _textW) / 2;
  _yPad = (_btnH - _textH) / 2;

  // centre align text
  _xPos = _btnX + _xPad;
  _yPos = _btnY - _yPad;

  replaceButtonText(_tft, _btnText, "centre", _btnX, _btnY, _textW, _btnH);
  setPreviousText(_btnText);

  _tft.setTextColor(_colour);
  _tft.setCursor(_xPos, _yPos);
  _tft.print(_btnText);
}


/******************************************************
/          Top centre align text on button
******************************************************/
void gfxButton::writeTextTopCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour) {
  int _btnX = x;
  int _btnY = y + (h / 2);  // text is printed from bottom left so add half height value to y
  int _btnW = w;
  int _btnH = (h / 2);      // treat button as if it is only half the height

  int16_t _textX, _textY;
  uint16_t _textW, _textH;
  // set font to get text size
  _tft.setFont(&_font);
  // set cursor to 0 as only text box dimensions required
  _tft.getTextBounds(_btnText, 0, 0, &_textX, &_textY, &_textW, &_textH);

  int _xPad, _yPad, _xPos, _yPos;

  // find space left over after text added
  // divide by two to get x and y padding
  _xPad = (_btnW - _textW) / 2;
  _yPad = (_btnH - _textH) / 2;

  // centre align text
  _xPos = _btnX + _xPad;
  _yPos = _btnY - _yPad;

  replaceButtonText(_tft, _btnText, "centre", _btnX, _btnY, _btnW, _btnH);
  setPreviousText(_btnText);

  _tft.setTextColor(_colour);
  _tft.setCursor(_xPos, _yPos);
  _tft.print(_btnText);
}


/******************************************************
/          Bottom centre align text on button
******************************************************/
void gfxButton::writeTextBottomCentre(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour) {
  int _btnX = x;
  int _btnY = y + h;    // text is printed from bottom left so add height value to y
  int _btnW = w;
  int _btnH = (h / 2);  // treat button as if it is only half the height

  int16_t _textX, _textY;
  uint16_t _textW, _textH;
  // set font to get text size
  _tft.setFont(&_font);
  // set cursor to 0 as only text box dimensions required
  _tft.getTextBounds(_btnText, 0, 0, &_textX, &_textY, &_textW, &_textH);

  int _xPad, _yPad, _xPos, _yPos;

  // find space left over after text added
  // divide by two to get x and y padding
  _xPad = (_btnW - _textW) / 2;
  _yPad = (_btnH - _textH) / 2;

  // centre align text
  _xPos = _btnX + _xPad;
  _yPos = _btnY - _yPad;

  replaceButtonText(_tft, _btnText, "centre", _btnX, _btnY, _btnW, _btnH);
  setPreviousText(_btnText);

  _tft.setTextColor(_colour);
  _tft.setCursor(_xPos, _yPos);
  _tft.print(_btnText);
}


/******************************************************
/           Left align text on button
******************************************************/
void gfxButton::writeTextLeft(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour) {
  int _btnX = x;
  int _btnY = y + h; // text is printed from bottom left so add height value to y
  int _btnW = w;
  int _btnH = h;

  int16_t _textX, _textY;
  uint16_t _textW, _textH;
  // set font to get text size
  _tft.setFont(&_font);
  // set cursor to 0 as only text box dimensions required
  _tft.getTextBounds(_btnText, 0, 0, &_textX, &_textY, &_textW, &_textH);

  int _yPad, _xPos, _yPos;

  // find space left over after text added
  // divide by two to y padding
  _yPad = (_btnH - _textH) / 2;

  // left align text
  _xPos = _btnX + ceil(_btnW * 0.05);
  _yPos = _btnY - _yPad;

  replaceButtonText(_tft, _btnText, "left", _btnX, _btnY, _btnW, _btnH);
  setPreviousText(_btnText);

  _tft.setTextColor(_colour);
  _tft.setCursor(_xPos, _yPos);
  _tft.print(_btnText);
}


/******************************************************
/           Right align text on button
******************************************************/
void gfxButton::writeTextRight(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour) {
  int _btnX = x;
  int _btnY = y + h; // text is printed from bottom left so add height value to y
  int _btnW = w;
  int _btnH = h;

  int16_t _textX, _textY;
  uint16_t _textW, _textH;
  // set font to get text size
  _tft.setFont(&_font);
  // set cursor to 0 as only text box dimensions required
  _tft.getTextBounds(_btnText, 0, 0, &_textX, &_textY, &_textW, &_textH);

  int _yPad, _xPos, _yPos;

  // find space left over after text added
  // divide by two to get y padding
  _yPad = (_btnH - _textH) / 2;

  // right align text
  _xPos = (_btnX + _btnW) - (_textW + ceil(_btnW * 0.05));
  _yPos = _btnY - _yPad;

  replaceButtonText(_tft, _btnText, "right", _btnX, _btnY, _btnW, _btnH);
  setPreviousText(_btnText);

  _tft.setTextColor(_colour);
  _tft.setCursor(_xPos, _yPos);
  _tft.print(_btnText);
}


/******************************************************
/         Centre align text on circle button
******************************************************/
void gfxButton::writeTextCircle(MCUFRIEND_kbv _tft, GFXfont _font, String _btnText, unsigned long _colour) {
  int _btnX = x;
  int _btnY = y + h; // text is printed from bottom left so add height value to y

  int16_t _textX, _textY;
  uint16_t _textW, _textH;
  // set font to get text size
  _tft.setFont(&_font);
  // set cursor to 0 as only text box dimensions required
  _tft.getTextBounds(_btnText, 0, 0, &_textX, &_textY, &_textW, &_textH);

  int _xPad, _yPad, _xPos, _yPos;

  // for cicles, x and y define centre so divide
  // text w/h by two to offset centre point
  _xPad = (_textW / 2);
  _yPad = (_textH / 2);

  _xPos = _btnX - _xPad;
  _yPos = _btnY + _yPad;

  replaceButtonText(_tft, _btnText, "centre", _btnX, _btnY);
  setPreviousText(_btnText);

  _tft.setTextColor(_colour);
  _tft.setCursor(_xPos, _yPos);
  _tft.print(_btnText);
}

// TODO - unsure if supports left/right aligned text buttons
/******************************************************
/               Replace Button Text
/ Replaces the previous text on a button with the
/ colour of the button before new text is written to it
******************************************************/
void gfxButton::replaceButtonText(MCUFRIEND_kbv _tft, String _newText, String _aligned, int _btnX, int _btnY, int _btnW, int _btnH) {
  // get previous text string and colour for this button
  String _prevText = getPreviousText();

  // only replace if there is text to replace and it's different from current text
  if (_prevText.length() > 0 && _prevText != _newText) {
    unsigned long _buttonColour = getButtonColour();
    Serial.print("color: ");
    Serial.println(_buttonColour);
    int16_t _textX, _textY;
    uint16_t _textW, _textH;
    // get size of previous text string
    _tft.getTextBounds(_prevText, 0, 0, &_textX, &_textY, &_textW, &_textH);

    // calculate previous text x,y co-ordinates
    int _prevXPos, _prevYPos;
    if (_aligned == "centre") {
      _prevXPos = _btnX + (abs(_btnW - _textW) / 2) + _textX;
      _prevYPos = _btnY - (abs(_btnH - _textH) / 2) + _textY;
    }
    else if (_aligned == "left") {
      _prevXPos = _btnX + ceil(_btnW * 0.05) + _textX;
      _prevYPos = _btnY - (abs(_btnH - _textH) / 2) + _textY;
    }
    else if (_aligned == "right") {;
      _prevXPos = (_btnX + _btnW) - (_textW + ceil(_btnW * 0.05)) + _textX;
      _prevYPos = _btnY - (abs(_btnH - _textH) / 2) + _textY;
    }

    int btn_x_right = (_btnX + _btnW);
    int txt_x_right = (_prevXPos + _textW);
    int btn_y_bottom = (_btnY + _btnH);
    int txt_y_bottom = (_prevYPos + _textH);
    // if box fill larger than btn dimensions, fix
    if (txt_x_right > btn_x_right) {
      _textW = _textW - (txt_x_right - btn_x_right);
    }
    if (txt_y_bottom > btn_y_bottom) {
      _textH = _textH - (txt_y_bottom - btn_y_bottom);
    }

    // fill over previous text value
    _tft.fillRect(_prevXPos, _prevYPos, _textW, _textH, _buttonColour);
  }
}


String gfxButton::getPreviousText() {
  return _previousText;
}


void gfxButton::setPreviousText(String _text) {
  _previousText = _text;
}


int gfxButton::getButtonColour() {
  if (_buttonColour == 0) {
    _buttonColour = defaultColour;
  }
  return _buttonColour;
}


void gfxButton::setButtonColour(unsigned long _colour) {
  _buttonColour = _colour;
}



gfxTouch::gfxTouch() {};


/******************************************************
/         Constructor for gfxTouch instance
/ Takes gfxButton instance as argument and calculates
/ min/max boundaries for touch registration. Also takes
/ an pointer to a function that should be caLled when
/ the button is pressed.
******************************************************/
gfxTouch::gfxTouch(String _screen, String _name, int _xMin, int _xMax, int _yMin, int _yMax, String _touchType, void (*btnFunction)(bool state)) {
  screen = _screen;
  name =_name;
  xMin = _xMin;
  xMax = _xMax;
  yMin = _yMin;
  yMax = _yMax;
  touchType = _touchType;
  lastTouched = 0UL;
  btnFunc = *btnFunction;
}


/******************************************************
/                Init new Toggle
/ Initiates a toggle type instance based on a
/ previously  created button instance. Will allow
/ triggering that button with toggle functionality
/ and call a function on button state change
******************************************************/
gfxTouch gfxTouch::addToggle(gfxButton &button, void (*btnFunction)(bool state), String name, int percent) {
  String _screen = button.screen;
  String _name = name;
  String _touchType = "toggle";

  // set xMin, xMax, yMin, yMax
  setTouchBoundary(button.x, button.y, button.w, button.h, button.r, percent);
  // initialise button as off
  setState(false);

  return gfxTouch(_screen, _name, _xMin, _xMax, _yMin, _yMax, _touchType, *btnFunction);
}


/******************************************************
/                Init new Momentary
/ Initiates a momentary type instance based on a
/ previously  created button instance. Will allow
/ triggering that button with momentary functionality
/ and call a function on button state change
******************************************************/
gfxTouch gfxTouch::addMomentary(gfxButton &button, void (*btnFunction)(bool state), String name, int percent) {
  String _screen = button.screen;
  String _name = name;
  String _touchType = "momentary";

  // set xMin, xMax, yMin, yMax
  setTouchBoundary(button.x, button.y, button.w, button.h, button.r, percent);
  // initialise button as off
  setState(false);

  return gfxTouch(_screen, _name, _xMin, _xMax, _yMin, _yMax, _touchType, *btnFunction);
}


/******************************************************
/         Set Touch Boundary for Button
/ Determines min and max XY values for where a
/ touch needs to register to trigger the button
/ Boundary size can be modified by percent value
******************************************************/
void gfxTouch::setTouchBoundary(int _x, int _y, int _w, int _h, int _r, int _percent) {
  // if w and h dimensions are zero and radius > 0, then button is circle
  if (_w == 0 && _h == 0 && _r > 0) {
    // get new padded radius dimension
    int _pad_r = ceil(_r * (100 + _percent)/100);
    // circles are drawn from the centre point
    _xMin = _x - _pad_r;
    _xMax = _x + _pad_r;
    _yMin = _y - _pad_r;
    _yMax = _y + _pad_r;
  }
  // else button must be a rectangle
  else {
    // get new w,h dimensions
    int _pad_w = ceil((_w * (100 + _percent))/100);
    int _pad_h = ceil((_h * (100 + _percent))/100);
    // offset xy position by half the difference between original dimensions and padded dimensions
    _xMin = _x - (_pad_w - _w)/2;
    _yMin = _y - (_pad_h - _h)/2;
    // add the padded dimensions to the new xy positions
    _xMax = _xMin + _pad_w;
    _yMax = _yMin + _pad_h;
  }

  // limit possible boundary values by screen size
  // TODO include screen size parameter - maybe in begin()?
  _xMin = _xMin >= 0 ? _xMin : 0;
  _yMin = _yMin >= 0 ? _yMin : 0;
  _xMax = _xMax <= 480 ? _xMax : 480;
  _yMax = _yMax <= 320 ? _yMax : 320;
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
void gfxTouch::checkButton(String currentScreen, int touch_x, int touch_y) {
  unsigned long currentTime = millis();

  if (touchType == "momentary") {
    if (screen == currentScreen && (currentTime - lastTouched >= g_momentary_delay)) {
      if ((touch_x >= xMin && touch_x <= xMax) && (touch_y >= yMin && touch_y <= yMax)) {
        Serial.print("touch detected on button: ");
        Serial.println(name);
        lastTouched = currentTime;
        // set button state
        setState(!getState());
        // run function tied to button
        runButtonFunction();
      }
    }
  }
  else if (touchType == "toggle" && _coolOff == false) {
    if (screen == currentScreen && (currentTime - lastTouched >= g_toggle_delay)) {
      if ((touch_x >= xMin && touch_x <= xMax) && (touch_y >= yMin && touch_y <= yMax)) {
        Serial.print("touch detected on button: ");
        Serial.println(name);
        lastTouched = currentTime;
        // set button state
        setState(!getState());
        // don't allow toggle again until touch pressure is zeroed
        _coolOff = true;
        // run function tied to button
        runButtonFunction();
      }
    }
  }
}


/******************************************************
/            Cool Off Period for Toggles
/ Toggle buttons require a pressure reading of 0 before
/ the user can toggle that button again.
******************************************************/
void gfxTouch::toggleCoolOff() {
  _coolOff = false;
}


/******************************************************
/            Run function tied to Button
/ Run the function assigned to that button when it
/ has been triggered by a touch.
******************************************************/
void gfxTouch::runButtonFunction() {
  btnFunc(getState());
}


/******************************************************
/               Get Button State
/ Get the latest state of the button, false if inactive.
******************************************************/
bool gfxTouch::getState() {
  return _btnActive;
}


/******************************************************
/               Set Button State
/ Set the latest state of the button, false if inactive.
******************************************************/
void gfxTouch::setState(bool btnActive) {
  _btnActive = btnActive;
}

/******************************************************
/           Declare Debouncing Delay Variables
/ Declare variables for debouncing toggle and momentary
/ buttons. These values are shared across instances and
/ will be used by all buttons of that type.
******************************************************/
unsigned long gfxTouch::g_toggle_delay = 0;
unsigned long gfxTouch::g_momentary_delay = 0;


/******************************************************
/              Set Debouncing Delay Values
/ Set debouncing delay for toggle buttons.
******************************************************/
void gfxTouch::setToggleDebounce(unsigned long toggle_delay) {
  g_toggle_delay = toggle_delay;
}


/******************************************************
/              Set Debouncing Delay Values
/ Set debouncing delay for momentary buttons.
******************************************************/
void gfxTouch::setMomentaryDebounce(unsigned long momentary_delay) {
  g_momentary_delay = momentary_delay;
}
