# gfxButton

gfxButton is an Arduino library for easily creating multi-screen User Interfaces with interactive buttons and components with multiple states or updating values. Functions can be associated with buttons so that they are called automatically on input or state change.

## Intro
Each button is intialised as an instance of the gfxButton class with parameters for the button dimension, its shape/draw style, a default button colour, a button label, and whether the button is interactive (tactile) or not. 

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