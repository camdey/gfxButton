#ifndef GUITESTSCREEN_H
#define GUITESTSCREEN_H

#include "Arduino.h"

namespace test_screen {
  void initTestButtons();
  void populateTestScreen();
  void checkTestButtons(int touch_x, int touch_y);
  void func_StepDistance(bool btnActive);
  void func_Flash(bool btnActive);
  void func_Reset(bool btnActive);
  void func_Back(bool btnActive);
  void func_ArrowUp(bool btnActive);
  void func_ArrowDown(bool btnActive);
  void printPosition();
  void updateMovementCount();
}
#endif
