#include "gui_control.h"
#include "gui_calc_screen.h"
#include "extern_vars.h"

namespace calc_screen {
  #define num_btns 17
  #define totalRows 4
  #define totalCols 4
 
  
  String stepNr;
  String railPos;
  String distanceValue;
  char inputValues[7] = {'0'};
  int inputIndex = 0;
  int maxInputIndex = 5;
  bool canEditDistance = false;
  float distanceMillimetres = 0.0000;
  int rowNr = 0; // keep track of row
  int colNr = 0; // keep track of column


  gfxButton btn_Distance  =   btn.initButton("Dist. steps", "fillRoundRect", 0,   20,  160,  80,  15,  DARKGRAY, true   );
  gfxButton btn_Steps     =   btn.initButton("Dist. mm",    "fillRoundRect", 0,  120,  160,  80,  15,  DARKGRAY, true   );
  gfxButton btn_Actual    =   btn.initButton("Actual",      "fillRoundRect", 0,  220,  160,  80,  15,  DARKGRAY, false  );
  gfxButton btn_Cancel    =   btn.initButton("X",  "fillRoundRect", 264,  238,  60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Minus     =   btn.initButton("-",  "fillRoundRect", 336,  238,  60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Zero      =   btn.initButton("0",  "fillRoundRect", 408,  238,  60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_One       =   btn.initButton("1",  "fillRoundRect", 264,  166,  60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Two       =   btn.initButton("2",  "fillRoundRect", 336,  166,  60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Three     =   btn.initButton("3",  "fillRoundRect", 408,  166,  60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Four      =   btn.initButton("4",  "fillRoundRect", 264,  94,   60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Five      =   btn.initButton("5",  "fillRoundRect", 336,  94,   60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Six       =   btn.initButton("6",  "fillRoundRect", 408,  94,   60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Seven     =   btn.initButton("7",  "fillRoundRect", 264,  22,   60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Eight     =   btn.initButton("8",  "fillRoundRect", 336,  22,   60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Nine      =   btn.initButton("9",  "fillRoundRect", 408,  22,   60, 60,  5,   CUSTOM_BLUE,  true  );
  gfxButton btn_Back      =   btn.initBitmapButton(backArrow,       172,  220,  80, 80,       WHITE,        true  );
  gfxButton btn_Run       =   btn.initBitmapButton(rocket,          172,  20,   80, 80,       WHITE,        true  );
  gfxButton btn_vacant    =   btn.initVacantButton();


  gfxButton *btn_array[num_btns];
  gfxButton *nav_array[totalRows][totalCols] = {
    // three rows, three columns
    {&btn_Distance, &btn_Seven,   &btn_Eight, &btn_Nine},   // top row
    {&btn_Steps,    &btn_Four,    &btn_Five,  &btn_Six},    // middle row
    {&btn_Actual,   &btn_One,     &btn_Two,   &btn_Three},  // bottom row
    {&btn_vacant,   &btn_Cancel,  &btn_Minus, &btn_Zero}  // bottom row
  };


  void initCalcButtons() {
    btn_array[0] = &btn_Distance;
    btn_array[1] = &btn_Seven;
    btn_array[2] = &btn_Eight;
    btn_array[3] = &btn_Nine;
    btn_array[4] = &btn_Steps;
    btn_array[5] = &btn_Four;
    btn_array[6] = &btn_Five;
    btn_array[7] = &btn_Six;
    btn_array[8] = &btn_Actual;
    btn_array[9] = &btn_One;
    btn_array[10] = &btn_Two;
    btn_array[11] = &btn_Three;
    btn_array[12] = &btn_Cancel;
    btn_array[13] = &btn_Minus;
    btn_array[14] = &btn_Zero;
    btn_array[15] = &btn_Back;
    btn_array[16] = &btn_Run;

    btn_Distance.addToggle(func_Distance, 0);
    // btn_Steps.addToggle(func_Flash, 0);
    btn_Cancel.addInputKey(func_Number, 0);
    btn_Minus.addInputKey(func_Number, 0);
    btn_Zero.addInputKey(func_Number, 0);
    btn_One.addInputKey(func_Number, 0);
    btn_Two.addInputKey(func_Number, 0);
    btn_Three.addInputKey(func_Number, 0);
    btn_Four.addInputKey(func_Number, 0);
    btn_Five.addInputKey(func_Number, 0);
    btn_Six.addInputKey(func_Number, 0);
    btn_Seven.addInputKey(func_Number, 0);
    btn_Eight.addInputKey(func_Number, 0);
    btn_Nine.addInputKey(func_Number, 0);
    btn_Back.addMomentary(func_Back, 0);
    btn_Run.addMomentary(func_Run, 0);

    btn_Distance.addBorder(3, WHITE);
    btn_Steps.addBorder(3, WHITE);
    btn_Actual.addBorder(3, WHITE);
  }


  void populateCalcScreen() {
    setCurrentScreen("Calc");

    // draw buttons
    for (int i=0; i < num_btns; i++) {
      btn_array[i]->drawButton();
    }

    // draw text
    btn_Distance.writeTextTopCentre(Arimo_Regular_30, WHITE);
    btn_Distance.writeTextBottomCentre(Arimo_Bold_30, WHITE, String(0, 4));
    btn_Steps.writeTextTopCentre(Arimo_Regular_30, WHITE);
    btn_Steps.writeTextBottomCentre(Arimo_Bold_30, WHITE, String(0, 4));
    btn_Actual.writeTextTopCentre(Arimo_Regular_30, WHITE);
    btn_Actual.writeTextBottomCentre(Arimo_Bold_30, WHITE, String(0, 4));
    btn_Cancel.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Minus.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Zero.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_One.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Two.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Three.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Four.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Five.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Six.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Seven.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Eight.writeTextCentre(Arimo_Bold_30, WHITE);
    btn_Nine.writeTextCentre(Arimo_Bold_30, WHITE);

    // always start from first button when loading page
    rowNr = 0;
    colNr = 0;
    nav_array[rowNr][colNr]->drawBorder(3, CUSTOM_YELLOW);
  }


  void checkCalcButtons(int touch_x, int touch_y) {
    for (int i=0; i < num_btns; i++) {
      if (btn_array[i]->isTactile()) {
        btn_array[i]->contains(touch_x, touch_y);
      }
    }
  }


  void func_Distance(bool active) {
    if (active) {
      canEditDistance = true;
      btn_Distance.writeTextTopCentre(Arimo_Regular_30, YELLOW);
      btn_Distance.writeTextBottomCentre(Arimo_Bold_30, YELLOW, inputValues);
      btn_Steps.writeTextBottomCentre(Arimo_Bold_30, YELLOW, String(distanceMillimetres, 4));
    }
    else {
      canEditDistance = false;
      btn_Distance.writeTextTopCentre(Arimo_Regular_30, WHITE);
      btn_Distance.writeTextBottomCentre(Arimo_Bold_30, WHITE, inputValues);
      btn_Steps.writeTextBottomCentre(Arimo_Bold_30, WHITE, String(distanceMillimetres, 4));
    }
    Serial.println("step dist btn");
  }


  void func_Number(char* label) {
    if (canEditDistance) {
      // if input starts with negative, increase max index
      maxInputIndex = inputValues[0] == '-' ? 6 : 5;
      // if input is numeric value, add to array
      if (label[0] != 'X' && label[0] != '-') {
        inputValues[inputIndex] = label[0];
        incrementIndex();                       // increment on valid input
      }
      // else delete value
      else if (label[0] == 'X') {
        if (inputValues[inputIndex] == '\0') {  // decrement then delete
          decrementIndex();
          inputValues[inputIndex] = '\0';
        }
        else {                                  // delete then decrement
          inputValues[inputIndex] = '\0';
          decrementIndex();
        }
      }
      // or add negative if first value in array
      else if (label[0] == '-'&& inputIndex == 0) {
        inputValues[inputIndex] = label[0];
        incrementIndex();                       // increment on valid input
      }
      // if last value is empty, set to 0
      if (inputValues[0] == '\0') {
        inputValues[0] = '0';
      }

      // calculate distance in mm
      distanceMillimetres = atoi(inputValues)*(microstepLength/1000.0000);
      btn_Distance.writeTextBottomCentre(Arimo_Bold_30, YELLOW, inputValues);
      btn_Steps.writeTextBottomCentre(Arimo_Bold_30, YELLOW, String(distanceMillimetres, 4));
    }
  }


  void incrementIndex() {
    inputIndex++;
    if (inputIndex > maxInputIndex) {
      inputIndex = maxInputIndex;
    }
  }


  void decrementIndex() {
    inputIndex--;
    if (inputIndex < 0) {
      inputIndex = 0;
    }
  }


  void func_Back(bool active) {
    if (active && !canEditDistance) {
      populateScreen("Test");
    }
  }


  void func_Run(bool active) {
    if (active && !canEditDistance) {
      // do stuff
    }
  }


  void checkCalcNav() {
    if (yDirection != 0 || xDirection != 0) {
      int newRowNr = 0; int newColNr = 0;
      
      newRowNr = setIndex("row", rowNr, yDirection);
      newColNr = setIndex("col", colNr, xDirection);

      // if not tactile button, skip
      if (!nav_array[newRowNr][newColNr]->isTactile()) {
        newRowNr = rowNr;
        newColNr = colNr;
      }

      if (newRowNr != rowNr || newColNr != colNr) {
        // change current button's border back to default
        nav_array[rowNr][colNr]->drawBorder(3);

        nav_array[newRowNr][newColNr]->drawBorder(3, CUSTOM_YELLOW);
        rowNr = newRowNr;
        colNr = newColNr;

        lastNavUpdate = millis();
      }
    }
  }


  void checkCalcNavInput() {
    int index = (rowNr * totalRows) + colNr;
    btn_array[index]->actuateButton(zState);
  }


  int setIndex(String dimension, int index, int direction) {
    int maxVal = 0;
    if (dimension == "row") {
      maxVal = totalRows-1;
    }
    else if (dimension == "col") {
      maxVal = totalCols-1;
    }

    if (index + direction < 0) {
      return maxVal;
    }
    else if (index + direction > maxVal) {
      return 0;
    }
    else {
      return (index + direction);
    }
  }
}
