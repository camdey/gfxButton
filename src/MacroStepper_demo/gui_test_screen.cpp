#include "gui_control.h"
#include "gui_test_screen.h"
#include "extern_vars.h"

namespace test_screen {
  #define num_btns 10
  #define num_tchs 6
  gfxButton *btn_array[num_btns];
  gfxTouch  *tch_array[num_tchs];
  // gfxButton *nav_array[3][3];

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


  gfxButton btn_StepDistance =   gfxB.initButton(       "fillRoundRect",     0,   20,  160,   80,  15,  DARKGRAY, true  );
  gfxButton btn_DistanceVal  =   gfxB.initButton(       "fillRoundRect",     0,   20,  160,   80,  15,  DARKGRAY, true  );
  gfxButton btn_StepNr       =   gfxB.initButton(       "fillRoundRect",     0,  120,  160,   80,  15,  DARKGRAY, false );
  gfxButton btn_StepNrVal    =   gfxB.initButton(       "fillRoundRect",     0,  120,  160,   80,  15,  DARKGRAY, false );
  gfxButton btn_RailPos      =   gfxB.initButton(       "fillRoundRect",     0,  220,  160,   80,  15,  DARKGRAY, false );
  gfxButton btn_RailPosVal   =   gfxB.initButton(       "fillRoundRect",     0,  220,  160,   80,  15,  DARKGRAY, false );
  // don't add to array as bitmap depends on state
  gfxButton btn_Flash        =   gfxB.initBitmapButton( flashOff,          220,   20,   80,   80,       CUSTOM_RED,   true  );
  gfxButton btn_Reset        =   gfxB.initBitmapButton( cancel,            220,  120,   80,   80,       WHITE,        true  );
  gfxButton btn_Back         =   gfxB.initBitmapButton( backArrow,         220,  220,   80,   80,       WHITE,        true  );
  gfxButton btn_ArrowUp      =   gfxB.initBitmapButton( arrowUp,           350,   20,  120,  120,       CUSTOM_GREEN, true  );
  gfxButton btn_ArrowDown    =   gfxB.initBitmapButton( arrowDown,         350,  180,  120,  120,       CUSTOM_RED,   true  );

  gfxTouch  tch_StepDistance =   gfxT.addToggle(    btn_DistanceVal,  func_StepDistance, 0 );
  gfxTouch  tch_Flash        =   gfxT.addToggle(    btn_Flash,        func_Flash,        0 );
  gfxTouch  tch_Reset        =   gfxT.addMomentary( btn_Reset,        func_Reset,        0 );
  gfxTouch  tch_Back         =   gfxT.addMomentary( btn_Back,         func_Back,         0 );
  gfxTouch  tch_ArrowUp      =   gfxT.addMomentary( btn_ArrowUp,      func_ArrowUp,      0 );
  gfxTouch  tch_ArrowDown    =   gfxT.addMomentary( btn_ArrowDown,    func_ArrowDown,    0 );

  #define totalRows 3
  #define totalCols 3

  // gfxButton *nav_array[totalRows][totalCols] = {
  //   // three rows, three columns
  //   {&btn_DistanceVal,  &btn_Flash, &btn_ArrowUp  },    // top row
  //   {&btn_StepNrVal,    &btn_Reset,               },    // middle row
  //   {&btn_RailPosVal,   &btn_Back,  &btn_ArrowDown}     // bottom row
  // };

  gfxButton *nav_array[totalRows][totalCols] = {
    // three rows, three columns
    {&btn_DistanceVal,  &btn_Flash, &btn_ArrowUp  },    // top row
    {&btn_StepNrVal,    &btn_Reset, &btn_StepNrVal},    // middle row
    {&btn_RailPosVal,   &btn_Back,  &btn_ArrowDown}     // bottom row
  };
  int nav_array_pos[3][3] = {
    {0, 1, 2},    // top row
    {-1, 3, -1},  // middle row
    {-1, 4, 5}    // bottom row
  };


  void initTestButtons() {
    btn_array[0] = &btn_StepDistance;
    btn_array[1] = &btn_DistanceVal;
    btn_array[2] = &btn_StepNr;
    btn_array[3] = &btn_StepNrVal;
    btn_array[4] = &btn_RailPos;
    btn_array[5] = &btn_RailPosVal;
    btn_array[6] = &btn_Reset;
    btn_array[7] = &btn_Back;
    btn_array[8] = &btn_ArrowUp;
    btn_array[9] = &btn_ArrowDown;

    tch_array[0] = &tch_StepDistance;
    tch_array[1] = &tch_Flash;
    tch_array[2] = &tch_ArrowUp;
    tch_array[3] = &tch_Reset;
    tch_array[4] = &tch_Back;
    tch_array[5] = &tch_ArrowDown;

    btn_array[1]->addBorder(3, WHITE);
    btn_array[3]->addBorder(3, WHITE);
    btn_array[5]->addBorder(3, WHITE);
  }


  void populateTestScreen() {
    setCurrentScreen("Test");
    stepNr = String(movementCount);
    railPos = String(currentPosition*(microstepLength/1000), 5);

    // draw buttons
    for (int i=0; i < num_btns; i++) {
      btn_array[i]->drawButton(tft);
    }
    if (!isShutterEnabled) {
      btn_Flash.drawButton(tft, CUSTOM_RED);
    }
    else if (isShutterEnabled) {
      btn_Flash.drawNewBitmap(tft, flashOn, CUSTOM_GREEN);
    }

    // draw text
    btn_StepDistance.writeTextTopCentre(tft, Arimo_Regular_30, String("Step Size"),  WHITE);
    btn_DistanceVal.writeTextBottomCentre(tft, Arimo_Bold_30, String(distancePerMovement, 4),  WHITE);
    btn_StepNr.writeTextTopCentre(tft, Arimo_Regular_30, String("Step Nr."),    WHITE);
    btn_StepNrVal.writeTextBottomCentre(tft, Arimo_Bold_30, stepNr,    WHITE);
    btn_RailPos.writeTextTopCentre(tft, Arimo_Regular_30, String("Rail Pos."),   WHITE);
    btn_RailPosVal.writeTextBottomCentre(tft, Arimo_Bold_30, railPos,   WHITE);

    // always start from first button when loading page
    rowNr = 0;
    colNr = 0;
    nav_array[rowNr][colNr]->drawBorder(tft, 3, CUSTOM_YELLOW);

    // tch_array[2].m_button->drawButton(tft, CUSTOM_BLUE);
    // tch_array[2]->m_button.drawButton(tft, CUSTOM_BLUE);
    // btn_Reset.drawButton(tft, CUSTOM_BLUE);
  }


  void checkTestButtons(int touch_x, int touch_y) {
    for (int i=0; i < num_tchs; i++) {
      tch_array[i]->checkTouchInput("Test", touch_x, touch_y);
    }
  }


  void func_StepDistance(bool active) {
    if (active) {
      areArrowsEnabled = true;
      canEditMovementDistance = true;

      btn_StepDistance.writeTextTopCentre(tft, Arimo_Regular_30, String("Step Size"), YELLOW);
      btn_DistanceVal.writeTextBottomCentre(tft, Arimo_Bold_30, String(distancePerMovement, 4), YELLOW);
    }
    else {
      areArrowsEnabled = false;
      canEditMovementDistance = false;

      // TODO would be nice to not re-write the top line on every arrow press
      btn_StepDistance.writeTextTopCentre(tft, Arimo_Regular_30, String("Step Size"), WHITE);
      btn_DistanceVal.writeTextBottomCentre(tft, Arimo_Bold_30, String(distancePerMovement, 4), WHITE);
    }
    Serial.println("step dist btn");
  }


  void func_Flash(bool active) {
    if (!isShutterEnabled) {
      isShutterEnabled = true;
      btn_Flash.drawNewBitmap(tft, flashOn, CUSTOM_GREEN);
    }
    else if (isShutterEnabled) {
      isShutterEnabled = false;
      // use drawNewButton so previous bitmap is filled over
      btn_Flash.drawNewBitmap(tft, flashOff, CUSTOM_RED);
    }
    Serial.println("flash btn");
  }


  void func_Reset(bool active) {
    if (active) {
      movementCount = 0; // reset
      stepNr = String(movementCount); // get latest value
      btn_StepNrVal.writeTextBottomCentre(tft, Arimo_Bold_30, stepNr, WHITE);
      Serial.println("reset btn");
    }
  }

  gfxButton arrayTest[1][2] = {btn_DistanceVal, btn_DistanceVal};

  void func_Back(bool active) {
    if (active && !areArrowsEnabled) {
      // populateScreen("Test");
    }
    Serial.println("back btn");
    gfxT.initNavigationLayout((gfxButton**)&arrayTest, 3, 3);
  }


  void func_ArrowUp(bool active) {
    if (active) {
      // if setting step size
      if (canEditMovementDistance && areArrowsEnabled) {
        stepsPerMovement++;
        distancePerMovement = microstepLength * stepsPerMovement;
        btn_DistanceVal.writeTextBottomCentre(tft, Arimo_Bold_30, String(distancePerMovement, 4), YELLOW);
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
        btn_DistanceVal.writeTextBottomCentre(tft, Arimo_Bold_30, String(distancePerMovement, 4), YELLOW);
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
    btn_RailPosVal.writeTextBottomCentre(tft, Arimo_Bold_30, railPos, WHITE);
  }


  // print new movementCount
  void updateMovementCount() {
    // increment movementCount and print to screen
    movementCount++;
    stepNr = String(movementCount);
    btn_StepNrVal.writeTextBottomCentre(tft, Arimo_Bold_30, stepNr, WHITE);
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
        nav_array[rowNr][colNr]->drawBorder(tft, 3);

        nav_array[newRowNr][newColNr]->drawBorder(tft, 3, CUSTOM_YELLOW);
        rowNr = newRowNr;
        colNr = newColNr;

        lastNavUpdate = millis();
      }
    }
  }


  void checkTestNavInput() {
    tch_array[nav_array_pos[rowNr][colNr]]->checkDigitalInput("Test", zState);
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
