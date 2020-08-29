#ifndef GUICALCSCREEN_H
#define GUICALCSCREEN_H

#include "Arduino.h"

namespace calc_screen {
  void initCalcButtons();
  void populateCalcScreen();
  void checkCalcButtons(int touch_x, int touch_y);
  void func_Distance(bool active);
  void func_Number(char* label);
  void incrementIndex();
  void decrementIndex();
  void func_Back(bool active);
  void func_Run(bool active);
  void checkCalcNav();
  void checkCalcNavInput();
  int setIndex(String dimension, int index, int direction);
}
#endif
