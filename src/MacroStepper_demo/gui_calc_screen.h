#ifndef GUICALCSCREEN_H
#define GUICALCSCREEN_H

#include "Arduino.h"

namespace calc_screen {
  void initCalcButtons();
  void populateCalcScreen();
  void checkCalcButtons(int touch_x, int touch_y);
  void func_StepDistance(bool active);
  void func_Number(String label);
  // void func_Reset(bool active);
  // void func_Back(bool active);
  // void printPosition();
  // void updateMovementCount();
  void checkCalcNav();
  void checkCalcNavInput();
  int setIndex(String dimension, int index, int direction);
}
#endif
