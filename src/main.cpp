#include "gfxButton.h"

TouchDisplay td = TouchDisplay();

void setup(void) {
  Serial.begin(9600);
}


void loop() {
  addButton();
  delay(2000);
}


void addButton() {
  gfxButton newButton = td.initButton(100, 110, 50, 40, true, 0);

  Serial.print("x: ");
  Serial.println(newButton.x);
  Serial.print("y: ");
  Serial.println(newButton.y);
  Serial.print("w: ");
  Serial.println(newButton.w);
  Serial.print("h: ");
  Serial.println(newButton.h);
  Serial.print("roundedRect: ");
  Serial.println(newButton.roundedRect);
  Serial.print("radius: ");
  Serial.println(newButton.radius);
}
