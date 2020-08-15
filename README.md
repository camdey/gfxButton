# gfxButton

gfxButton is an Arduino library for easily creating multi-screen User Interfaces with interactive buttons and components with multiple states or updating values. Functions can be associated with buttons so that they are called automatically on input or state change.

## Intro
Each button is intialised as an instance of the gfxButton class with parameters for the button dimension, its shape/draw style, a default button colour, a button label, and whether the button is interactive (tactile) or not.

```
gfxButton btn_StepSize = btn.initButton("Step Size", "fillRoundRect", 0, 20, 160, 80, 15, DARKGRAY, true);
```

If the button is tactile, you can add two types of interaction to the button: momentary or toggle. A momentary button has a defined on/off state and can't be triggered multiple times from touch or other input without first being released. A momentary button can be triggered continuously as long as it is touched or interacted with.  

## Multiple pages
gfxButton makes it easy to have multiple different pages/screens of your UI without having the code all in one place. It is recommended to use namespaces to clearly demarcate which buttons belong to which "screen" of your UI as you may use similar button or function names for other screens.
  
## Detecting touches
The easiest way to detect a touch on a specific button from a specific screen is to store the buttons for each page in an array and loop over that array for that page when it is active.

```
if (millis() - prevButtonCheck >= 100) {
    checkTouch(getCurrentScreen());
    prevButtonCheck = millis();
}
```
From loop() you can run the above with a predetermined frequency to check for touch inputs on a specific screen:
```
void checkTouch(String screen) {
  TSPoint point = ts.getPoint();

  // reset pinModes for tft (otherwise can't draw!)
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  int touch_z = point.z;

  int touch_x = map(point.y, TS_MINY, TS_MAXY, 0, tft.width());
  int touch_y = map(point.x, TS_MINX, TS_MAXX, 0, tft.height());

  
  if (touch_z >= 50 && touch_z <= 1000) {
    if (screen == "Foo") {
        foo_screen::checkFootButtons(touch_x, touch_y);
    }
    else if (screen == "Bar") {
        bar_screen::checkBartButtons(touch_x, touch_y);
    }
  }
}
```
This can then call a function for that specific screen to loop through the array of buttons:
```
void checkTestButtons(int touch_x, int touch_y) {
    for (int i=0; i < num_btns; i++) {
        if (btn_array[i]->isTactile()) {
            btn_array[i]->contains(touch_x, touch_y);
        }
    }
}
```

## Button properties
Buttons can have have the following properties:

- Label: default text for the button that should not change frequently
- Shape: shape of button / draw type as used in Adafruit's GFX library (e.g. drawRect() and fillRect())
- Dimensions: x, y, w, h, and r for rounded shapes including circles
- Default colour: default colour of the button
- isTacticle: can the button change state / be interactive, if not it can still have text or colours updated but not store a function or be included in navigation

You can also add additional properties to the buttons such as a border or interactive type (toggle / momentary). When adding an interactive type, you can specify a function that should be called when the button state changes.

## Button interaction
Add the function to be called on state change when intialising the interaction type (e.g. addToggle, addMomentary)
```
btn_StepSize.addToggle(func_StepDistance, 0);
```
The only functions currently supported are those that do not return any value and take as an argument a bool, which is used by the library to send the current state of the button.

You can also change the touch-sensitive area of a button by providing an optional padding value in percent. A value of 10 would increase the button's dimensions by 10% and any touches in that boundary will trigger the button.

## Non-Touch Navigation
It is also possible to interact with the buttons via input from a joystick or similar. You can have both touch and joystick capable interaction simultaneously or one or the other. When controlled with a joystick, a border is drawn around each button to signal the currently selected button. You can then have a separate digital input (e.g. a button) to act as the "press" or "touch" to interact with that button.

Navigation with a joystick takes directional input to determine which button the "cursor" should move to next. You could also use a series of buttons in an arrow-key configuration instead.

To aid in navigating through the buttons it's best to define your button layout as a 2-dimensional array. Buttons will be referenced by a row and column index that reflects the actual order of buttons as drawn on your screen:
```
gfxButton *nav_array[totalRows][totalCols] = {
    // three rows, three columns
    {&btn_StepSize,  &btn_Flash, &btn_ArrowUp},   // top row
    {&btn_StepNr,    &btn_Reset, &btn_vacant},    // middle row
    {&btn_RailPos,   &btn_Back,  &btn_ArrowDown}  // bottom row
};
```

The arrangement of buttons in this 2D array should also be the same as the order of your buttons in your button array, though it is possible to use only one array for both purposes.

A `btn_vacant` button can be intialised to fill in gaps where you may have a lesser number of buttons in a particular row or column. This prevents the cursor from getting "stuck" in a gap in the array. Non-tactile buttons are also ignored.

Detecting interaction with non-Touch navigation is largely the same as with touch navigation:

loop() function
```
if (millis() - prevJoystickCheck >= 50) {
    checkNavigationInput(getCurrentScreen());
    prevJoystickCheck = millis();
}
```
determine which "screen" is active and then check the buttons on that screen
```
void checkNavigation(String screen) {
    readXStick();
    readYStick();

    if (screen == "Test" && millis() - lastNavUpdate >= navDelay) {
        test_screen::checkTestNav();
    }
}
```
See `checkTestNav()` in `gui_test_screen.cpp` to see an example of how to determine where next to draw the cursor border.

## Icons or Bitmaps as Buttons
gfxButton supports creating buttons from a bitmap image or icon. These buttons work largely the same as regular buttons except that they do not have a text label or button shape. It's not recommended to draw text with bitmap buttons but it is possible.

These buttons are intialised the same way as regular buttons:
```
gfxButton btn_Back = btn.initBitmapButton(backArrow, 220, 220, 80, 80, WHITE, true);
```

## Button functions
These should be kept very simple and be declared as follows: `void func_name(bool active){...}` where the name of the function and parameter can be changed as needed.

For a toggle button, the function should do one thing when the button is active and do another thing when it is in-active. For momentary buttons, the function should execute the same thing each time and the function parameter is not necessary.

```
void func_Flash(bool active) {
if (active) {
    isShutterEnabled = true;
    btn_Flash.drawNewBitmap(flashOn, CUSTOM_GREEN);
}
else if (!active) {
    isShutterEnabled = false;
    // use drawNewButton so previous bitmap is filled over
    btn_Flash.drawNewBitmap(flashOff, CUSTOM_RED);
}
Serial.println("flash btn");
}
```

## More info
See the provided example under "MacroStepper_demo" for an example implementation for a single page UI, though easily adaptable to multi-page, with touch and joystick navigation.

Otherwise https://github.com/camdey/MacroStepper provides a more complete demonstration of the library with six different UI screens and button states and values linked across multiple functions.