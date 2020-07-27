#ifndef GUICONTROL_H
#define GUICONTROL_H

#include "Arduino.h"

void initButtons(unsigned long toggleDebounce, unsigned long momentaryDebounce);
void populateScreen(String screen);
void checkButtons(String screen);
void setCurrentScreen(String screen);
String getCurrentScreen();

#endif
