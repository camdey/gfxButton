#ifndef GUICONTROL_H
#define GUICONTROL_H

#include "Arduino.h"

void initButtons(unsigned long toggleDebounce, unsigned long momentaryDebounce);
void populateScreen(String screen);
void checkTouch(String screen);
void checkNavigation(String screen);
void checkNavigationInput(String screen);
void readXStick();
void readYStick();
void readZStick();
int getDirection(int val);
void setCurrentScreen(String screen);
String getCurrentScreen();

#endif
