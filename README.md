# gfxButton

gfxButton is an Arduino library for building button-based user interfaces on
Adafruit GFX-compatible displays driven by `MCUFRIEND_kbv`. It provides shape,
transparent, monochrome bitmap, RGB bitmap, and SD-card bitmap buttons with:

- touch and non-touch actuation
- toggle, momentary, and input-key callbacks
- configurable global or per-button debounce intervals
- labels and dynamically updated, aligned text
- borders for focus/navigation feedback
- visibility control that also disables hidden buttons
- helpers for arranging buttons across multiple screens

The repository includes a two-screen calculator/MacroStepper demo with touch
and joystick navigation in
[`examples/MacroStepper_demo`](examples/MacroStepper_demo).

## Requirements

The included PlatformIO environments target the Arduino Due and Adafruit Grand
Central M4. The library currently depends on:

- Arduino framework
- [Adafruit GFX Library](https://github.com/adafruit/Adafruit-GFX-Library)
- [MCUFRIEND_kbv](https://github.com/prenticedavid/MCUFRIEND_kbv)
- [Adafruit TouchScreen](https://github.com/adafruit/Adafruit_TouchScreen)
- [Adafruit BusIO](https://github.com/adafruit/Adafruit_BusIO)
- [Adafruit's SdFat fork](https://github.com/adafruit/SdFat)

The exact versions used by this project are listed in
[`examples/MacroStepper_demo/platformio.ini`](examples/MacroStepper_demo/platformio.ini).

## Installation

For PlatformIO, clone the repository and build the included demo:

```sh
git clone https://github.com/camdey/gfxButton.git
cd gfxButton
cd examples/MacroStepper_demo
pio run
```

## Typed shapes

Shape buttons use the `gfxButton::Shape` enum rather than string primitive
names:

```cpp
gfxButton btn_StepSize = btn.initButton(
    "Step Size",
    gfxButton::Shape::FillRoundRect,
    0, 20, 160, 80, 15,
    DARKGRAY,
    true
);
```

The default environment is `adafruit_grandcentral_m4`. To build for Arduino
Due instead:

```sh
cd examples/MacroStepper_demo
pio run -e due
```

To use gfxButton in another project, copy `src/gfxButton.h` and
`src/gfxButton.cpp` into that project and install the dependencies above.

## Quick start

Create one controller object, initialize it with the display, then use it to
create and configure buttons. Display, background, screen-size, and global
debounce settings are shared by all button instances.

```cpp
#include <gfxButton.h>
#include <Fonts/FreeSans12pt7b.h>

MCUFRIEND_kbv tft;
gfxButton ui;

gfxButton powerButton = ui.initButton(
    "Power",          // label (must remain valid for the button's lifetime)
    "fillRoundRect",  // Adafruit GFX drawing primitive
    20, 20,           // x, y
    140, 60,          // width, height
    10,               // corner radius
    0x39E7,           // RGB565 default colour
    true              // tactile/interactable
);

void onPowerChanged(bool active) {
  powerButton.drawButton(active ? 0x07E0 : 0x39E7);
  powerButton.writeTextCentre(FreeSans12pt7b, 0xFFFF);
}

void setup() {
  tft.reset();
  tft.begin(tft.readID());
  tft.setRotation(1);

  ui.begin(&tft);
  ui.setScreenSize(tft.width(), tft.height());
  ui.setBackgroundColour(0x0000);
  ui.setToggleDelay(200);
  ui.setMomentaryDelay(75);

  powerButton.addToggle(onPowerChanged, 0);
  powerButton.drawButton();
  powerButton.writeTextCentre(FreeSans12pt7b, 0xFFFF);
}
```

Pass mapped display coordinates to `contains()` while a touch is active. A
toggle uses a shared press latch so one physical press only changes state once;
reset that latch when all touch/press input has been released:

```cpp
if (touchIsActive) {
  powerButton.contains(touchX, touchY);
} else if (ui.isToggleActive()) {
  ui.setToggleActive(false);
}
```

The demo's
[`checkTouch()`](examples/MacroStepper_demo/gui_control.cpp) shows a complete
example using `TouchScreen`, including restoring shared TFT pins after a touch
read.

## Creating buttons

The `init...` helpers return a configured `gfxButton` object.

| Button type | Initializer | Notes |
| --- | --- | --- |
| GFX shape | `initButton(label, shape, x, y, w, h, r, colour, tactile)` | Supports `drawRect`, `fillRect`, `drawRoundRect`, `fillRoundRect`, `drawCircle`, and `fillCircle` |
| Transparent | `initTransparentButton(x, y, w, h, tactile)` | Defines a text/touch region without drawing a shape |
| Labeled transparent | `initTransparentButton(label, x, y, w, h, tactile)` | Transparent region with a default label |
| Monochrome bitmap | `initBitmapButton(bitmap, x, y, w, h, colour, bg, tactile)` | Uses Adafruit GFX `drawBitmap()` data |
| RGB bitmap | `initRGBBitmapButton(bitmap, x, y, w, h, tactile)` | Uses RGB565 `uint16_t` data |
| SD-card BMP | `initSDBitmapButton(filename, x, y, tactile)` | Reads dimensions from the BMP file; requires the two-argument `begin()` |
| Vacant | `initVacantButton()` | Non-tactile placeholder for rectangular navigation grids |

Rectangle coordinates use the top-left corner. For circle shapes, `x` and `y`
are the centre and `r` is the radius; pass zero for `w` and `h`.

Labels and SD filenames are stored as non-owning `const char*` pointers. String
literals, global/static character arrays, or other storage that outlives the
button are safe. Do not pass a pointer to a temporary or short-lived buffer.
New buttons start visible and inactive; a vacant button is non-tactile.

## Drawing and updating

Call `drawButton()` to draw the default state or `drawButton(colour, bg)` to
draw with a state-specific colour. The current draw colour is remembered so
later text updates erase old text using the correct button colour.

```cpp
statusButton.drawButton(0xF800);
statusButton.updateColour(0x07E0);  // change the default for future draws
statusButton.updateLabel("Ready");
```

`updateColour()`, `updateLabel()`, `updateBitmap()`, and `updateRGBBitmap()`
only change the stored value; call `drawButton()` afterward to redraw. In
contrast, `drawNewBitmap()` stores and immediately draws a replacement bitmap:

```cpp
flashButton.drawNewBitmap(flashOn, 0x07E0, 0x0000); // monochrome
photoButton.drawNewBitmap(activePhoto);              // RGB565
```

Set the UI background with `setBackgroundColour()` before hiding buttons or
updating text on outline/transparent buttons. The library uses this colour to
erase previous content.

## Text and labels

Text methods take an Adafruit GFX `GFXfont`, an RGB565 colour, and an optional
`String`. When the text argument is omitted, the button label is used.

```cpp
valueButton.writeTextTopCentre(FreeSans12pt7b, 0xFFFF);          // label
valueButton.writeTextBottomCentre(FreeSans12pt7b, 0xFFE0, "42"); // value
```

Available layouts are:

- `writeTextCentre()`
- `writeTextTopCentre()` and `writeTextBottomCentre()`
- `writeTextLeft()` and `writeTextRight()`
- `writeTextTopLeft()` and `writeTextBottomLeft()`
- `writeTextCircle()`

The library tracks the previous dynamic text and erases it before drawing a
different value. Drawing a button or a new bitmap clears that text history.

## Interaction modes

Only tactile buttons respond to `contains()` or `actuateButton()`. Configure an
interaction mode before reading input:

```cpp
toggleButton.addToggle(onToggle, 0);
repeatButton.addMomentary(onRepeat, 10);
keyButton.addInputKey(onKey, 0);
```

The final argument is touch padding as a percentage. Positive values enlarge
the hit area around the button, subject to the dimensions set with
`setScreenSize()`.

### Toggle

```cpp
void onToggle(bool active) {
  // active is the button's new on/off state
}
```

A toggle changes its stored state once per press and calls the callback with
that new state. The client must call `setToggleActive(false)` after input is
released, as shown in Quick start. You may also inspect or set a button's state
with `isButtonActive()` and `setButtonActive()`.

### Momentary

```cpp
void onRepeat(bool active) {
  if (active) {
    // Runs on every accepted actuation while the button is held.
  }
}
```

Momentary callbacks receive `true`. If input is polled continuously while held,
they repeat at the configured momentary delay.

### Input key

```cpp
void onKey(const char* label) {
  // A keyboard/keypad can route every key to this one callback.
}
```

`addInputKey()` behaves like a momentary button but passes the button's label to
a `void(const char*)` callback. See the calculator keypad in
[`gui_calc_screen.cpp`](examples/MacroStepper_demo/gui_calc_screen.cpp).

## Debouncing

Global debounce intervals, in milliseconds, apply to every button of the
corresponding type:

```cpp
ui.setToggleDelay(200);
ui.setMomentaryDelay(75);
```

The latest release also supports per-button overrides:

```cpp
repeatButton.setButtonMomentaryDelay(25);
slowToggle.setButtonToggleDelay(500);
```

An override of `0` uses the global value. Each button tracks its own last state
change, so interacting with one button does not debounce another.

## Visibility

`hideButton()` disables a button's touch and direct actuation, then redraws its
shape in the configured background colour. Filled shapes, bitmaps, and
transparent regions are cleared; outline shapes are redrawn in the background
colour, so clear any separately rendered label/value yourself if needed.

`showButton()` calls `drawButton()`, redrawing the base button with its stored
default colour and bitmap. It does not restore separately drawn text or a
state-specific colour supplied only to `drawButton(colour, bg)`; redraw those
after showing the button. `setVisible(bool)` changes visibility only when
necessary, avoiding redundant display writes in frequently evaluated UI logic:

```cpp
endButton.setVisible(canEndCurrentStack);

if (!endButton.isHidden()) {
  // The button is displayed and can accept input.
}
```

Calls to `contains()` and `actuateButton(true)` are ignored for hidden or
non-tactile buttons.

## Borders and non-touch navigation

Buttons can also be actuated from a joystick, encoder button, keypad, or other
input by calling `actuateButton(true)`. `drawBorder()` can indicate keyboard or
joystick focus:

```cpp
currentButton->drawBorder(3, 0xFFE0); // focused
currentButton->actuateButton(pressIsActive);
```

For persistent borders on filled shape buttons, configure one with
`addBorder(width, colour)` before drawing. Calling `drawBorder(width)` restores
the configured border colour. Bitmap borders are drawn outside the image.

For grid navigation, arrange pointers in a two-dimensional array that mirrors
the display layout. Use a vacant button where a row has no selectable item:

```cpp
gfxButton *navButtons[3][3] = {
  {&stepSize, &flash, &up},
  {&stepCount, &reset, &vacant},
  {&position, &back, &down}
};
```

The full navigation implementation is in
[`gui_test_screen.cpp`](examples/MacroStepper_demo/gui_test_screen.cpp).

## SD-card BMP buttons

Pass an initialized `SdFat` instance when using BMP files:

```cpp
SdFat sd;
gfxButton ui;

ui.begin(&tft, &sd);
gfxButton logo = ui.initSDBitmapButton("logo.bmp", 20, 20, true);
logo.addMomentary(onLogoPressed, 0); // dimensions are read for the hit area
logo.drawButton();
```

The BMP reader supports 16-bit and 24-bit BMP pixel data and crops images at
the display edge. Width and height are read as 32-bit little-endian values;
negative top-down BMP heights are handled when determining the button
dimensions.

## Multi-screen interfaces

A convenient pattern is to keep each screen in its own namespace, store its
buttons in an array, and only check the active screen's array:

```cpp
void checkButtons(gfxButton *buttons[], size_t count, int x, int y) {
  for (size_t i = 0; i < count; ++i) {
    buttons[i]->contains(x, y);
  }
}
```

`contains()` already ignores non-tactile and hidden buttons, so callers do not
need a separate `isTactile()` guard.

## Public API summary

- Setup: `begin()`, `setScreenSize()`, `setBackgroundColour()`,
  `getBackgroundColour()`
- Creation: `initButton()`, `initTransparentButton()`,
  `initBitmapButton()`, `initRGBBitmapButton()`, `initSDBitmapButton()`,
  `initVacantButton()`
- Drawing: `drawButton()`, `drawNewBitmap()`, `addBorder()`, `drawBorder()`
- Content: `updateLabel()`, `updateColour()`, `updateBitmap()`,
  `updateRGBBitmap()`, `setButtonColour()`, `getButtonColour()`, and the
  `writeText...()` methods
- Interaction: `addToggle()`, `addMomentary()`, `addInputKey()`, `contains()`,
  `actuateButton()`, `setTactile()`, `isTactile()`
- State: `setButtonActive()`, `isButtonActive()`, `setToggleActive()`,
  `isToggleActive()`
- Timing: `setToggleDelay()`, `setMomentaryDelay()`,
  `setButtonToggleDelay()`, `setButtonMomentaryDelay()`
- Visibility: `hideButton()`, `showButton()`, `setVisible()`, `isHidden()`

## Examples

The included demo starts in the calculator screen and demonstrates:

- multiple screen namespaces
- touch and joystick input
- toggle, momentary, and keypad callbacks
- dynamic labels/values and text alignment
- monochrome bitmap buttons
- focus borders and vacant navigation cells

See [`examples/MacroStepper_demo/main.cpp`](examples/MacroStepper_demo/main.cpp) for setup
and [MacroStepper](https://github.com/camdey/MacroStepper) for a larger project
using the library across several UI screens.
