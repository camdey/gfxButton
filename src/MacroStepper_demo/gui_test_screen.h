#ifndef GUITESTSCREEN_H
#define GUITESTSCREEN_H

#include "Arduino.h"

namespace test_screen {
  void initTestButtons();
  void populateTestScreen();
  void checkTestButtons(int touch_x, int touch_y);
  void func_StepDistance(bool active);
  void func_Flash(bool active);
  void func_Reset(bool active);
  void func_Back(bool active);
  void func_ArrowUp(bool active);
  void func_ArrowDown(bool active);
  void printPosition();
  void updateMovementCount();
  void testScreenNav();
  int setIndex(String dimension, int index, int direction);
  int skipButtonGap(int row, int col, int newRow, int newCol);
}
#endif
