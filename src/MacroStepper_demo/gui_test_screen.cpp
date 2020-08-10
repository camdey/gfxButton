#include "gui_control.h"
#include "gui_test_screen.h"
#include "extern_vars.h"

namespace test_screen {
  #define num_btns 9
  #define totalRows 3
  #define totalCols 3
  
  String stepNr;
  String railPos;
  int movementCount	= 0;
  bool areArrowsEnabled = false;
  bool canEditMovementDistance = false;
  bool isShutterEnabled = false;
  int stepsPerMovement = 0;
  float distancePerMovement;
  long currentPosition = 0;
  int rowNr = 0; // keep track of row
  int colNr = 0; // keep track of column


  gfxButton btn_StepSize    =   btn.initButton("Step Size", "fillRoundRect", 0,   20,  160,  80,  15,  DARKGRAY, true  );
  gfxButton btn_StepNr      =   btn.initButton("Step Nr.",  "fillRoundRect", 0,  120,  160,  80,  15,  DARKGRAY, false );
  gfxButton btn_RailPos     =   btn.initButton("Rail Pos.", "fillRoundRect", 0,  220,  160,  80,  15,  DARKGRAY, false );
  gfxButton btn_Flash       =   btn.initBitmapButton(flashOff,   220,  20,   80,   80,   CUSTOM_RED,   true  );
  gfxButton btn_Reset       =   btn.initBitmapButton(cancel,     220,  120,  80,   80,   WHITE,        true  );
  gfxButton btn_Back        =   btn.initBitmapButton(backArrow,  220,  220,  80,   80,   WHITE,        true  );
  gfxButton btn_ArrowUp     =   btn.initBitmapButton(arrowUp,    350,  20,   120,  120,  CUSTOM_GREEN, true  );
  gfxButton btn_ArrowDown   =   btn.initBitmapButton(arrowDown,  350,  180,  120,  120,  CUSTOM_RED,   true  );
  gfxButton btn_vacant      =   btn.initVacantButton();


  gfxButton *btn_array[num_btns];
  gfxButton *nav_array[totalRows][totalCols] = {
    // three rows, three columns
    {&btn_StepSize,  &btn_Flash, &btn_ArrowUp},   // top row
    {&btn_StepNr,    &btn_Reset, &btn_vacant},    // middle row
    {&btn_RailPos,   &btn_Back,  &btn_ArrowDown}  // bottom row
  };


  void initTestButtons() {
    btn_array[0] = &btn_StepSize;
    btn_array[1] = &btn_Flash;
    btn_array[2] = &btn_ArrowUp;
    btn_array[3] = &btn_StepNr;
    btn_array[4] = &btn_Reset;
    btn_array[5] = &btn_vacant;
    btn_array[6] = &btn_RailPos;
    btn_array[7] = &btn_Back;
    btn_array[8] = &btn_ArrowDown;

    btn_StepSize.addToggle(func_StepDistance, 0);
    btn_Flash.addToggle(func_Flash, 0);
    btn_Reset.addMomentary(func_Reset, 0);
    btn_Back.addMomentary(func_Back, 0);
    btn_ArrowUp.addMomentary(func_ArrowUp, 0);
    btn_ArrowDown.addMomentary(func_ArrowDown, 0);

    btn_StepSize.addBorder(3, WHITE);
    btn_StepNr.addBorder(3, WHITE);
    btn_RailPos.addBorder(3, WHITE);

  }


  void populateTestScreen() {
    setCurrentScreen("Test");
    stepNr = String(movementCount);
    railPos = String(currentPosition*(microstepLength/1000), 5);

    // draw buttons
    for (int i=0; i < num_btns; i++) {
      btn_array[i]->drawButton();
    }
    // if (!isShutterEnabled) {
    //   btn_Flash.drawButton(CUSTOM_RED);
    // }
    // else if (isShutterEnabled) {
    //   btn_Flash.drawNewBitmap(flashOn, CUSTOM_GREEN);
    // }

    // draw text
    btn_StepSize.writeTextTopCentre(Arimo_Regular_30, WHITE);
    btn_StepSize.writeTextBottomCentre(Arimo_Bold_30, WHITE, String(distancePerMovement, 4));
    btn_StepNr.writeTextTopCentre(Arimo_Regular_30, WHITE);
    btn_StepNr.writeTextBottomCentre(Arimo_Bold_30, WHITE, stepNr);
    btn_RailPos.writeTextTopCentre(Arimo_Regular_30, WHITE);
    btn_RailPos.writeTextBottomCentre(Arimo_Bold_30, WHITE, railPos);

    // always start from first button when loading page
    rowNr = 0;
    colNr = 0;
    nav_array[rowNr][colNr]->drawBorder(3, CUSTOM_YELLOW);
  }


  void checkTestButtons(int touch_x, int touch_y) {
    for (int i=0; i < num_btns; i++) {
      if (btn_array[i]->isTactile()) {
        btn_array[i]->contains(touch_x, touch_y);
      }
    }
  }


  void func_StepDistance(bool active) {
    if (active) {
      areArrowsEnabled = true;
      canEditMovementDistance = true;

      btn_StepSize.writeTextTopCentre(Arimo_Regular_30, YELLOW);
      btn_StepSize.writeTextBottomCentre(Arimo_Bold_30, YELLOW, String(distancePerMovement, 4));
    }
    else {
      areArrowsEnabled = false;
      canEditMovementDistance = false;

      // TODO would be nice to not re-write the top line on every arrow press
      btn_StepSize.writeTextTopCentre(Arimo_Regular_30, WHITE);
      btn_StepSize.writeTextBottomCentre(Arimo_Bold_30, WHITE, String(distancePerMovement, 4));
    }
    Serial.println("step dist btn");
  }


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


  void func_Reset(bool active) {
    if (active) {
      movementCount = 0; // reset
      stepNr = String(movementCount); // get latest value
      btn_StepNr.writeTextBottomCentre(Arimo_Bold_30, WHITE, stepNr);
      Serial.println("reset btn");
    }
  }


  void func_Back(bool active) {
    if (active && !areArrowsEnabled) {
      // populateScreen("Test");
    }
    Serial.println("back btn");
  }


  void func_ArrowUp(bool active) {
    if (active) {
      // if setting step size
      if (canEditMovementDistance && areArrowsEnabled) {
        stepsPerMovement++;
        distancePerMovement = microstepLength * stepsPerMovement;
        btn_StepSize.writeTextBottomCentre(Arimo_Bold_30, YELLOW, String(distancePerMovement, 4));
      }
      // if not setting step size, move the stepper forward
      else if (!canEditMovementDistance) {
        // take photo if shutter enabled
        if (isShutterEnabled) {
          // triggerShutter();
        }
        currentPosition += distancePerMovement;
        printPosition();
        updateMovementCount();
      }
    }
    Serial.println("arrow up btn");
  }


  void func_ArrowDown(bool active) {
    if (active) {
      // if setting step size
      if (canEditMovementDistance && areArrowsEnabled) {
        stepsPerMovement--;
        distancePerMovement = microstepLength * stepsPerMovement;
        btn_StepSize.writeTextBottomCentre(Arimo_Bold_30, YELLOW, String(distancePerMovement, 4));
      }
      // if not setting step size, move the stepper forward
      else if (!canEditMovementDistance) {
        // take photo if shutter enabled
        if (isShutterEnabled) {
          // triggerShutter();
        }
        currentPosition -= distancePerMovement;
        printPosition();
        updateMovementCount();
      }
    }
    Serial.println("arrow down btn");
  }


  // print new position of rail
  void printPosition() {
    // print new position of rail
    railPos = String(currentPosition*(microstepLength/1000), 5);
    btn_RailPos.writeTextBottomCentre(Arimo_Bold_30, WHITE, railPos);
  }


  // print new movementCount
  void updateMovementCount() {
    // increment movementCount and print to screen
    movementCount++;
    stepNr = String(movementCount);
    btn_StepNr.writeTextBottomCentre(Arimo_Bold_30, WHITE, stepNr);
  }


  void checkTestNav() {
    if (yDirection != 0 || xDirection != 0) {
      int newRowNr = 0; int newColNr = 0;
      
      newRowNr = setIndex("row", rowNr, yDirection);
      newColNr = setIndex("col", colNr, xDirection);

      // newRowNr = skipButtonGap(rowNr, colNr, newRowNr, newColNr);

      // if (newRowNr == 1 && newColNr == 2) {
      //   newRowNr = 2;
      // }

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


  void checkTestNavInput() {
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


  int skipButtonGap(int row, int col, int newRow, int newCol) {
    int diff = (newRow + newCol) - (row + col);
    // if array position empty
    if (nav_array[newRow][newCol]->isTactile()) {
      newRow += diff;
      if (newRow > totalRows-1) {
        newRow = totalRows-1;
      }
    }
    return newRow;
  }

}
