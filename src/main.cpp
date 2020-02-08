#include "gfxButton.h"
#include "MCUFRIEND_kbv.h"

#define LCD_CS A3 // Chip Select goes to Analog 3
#define LCD_CD A2 // Command/Data goes to Analog 2
#define LCD_WR A1 // LCD Write goes to Analog 1
#define LCD_RD A0 // LCD Read goes to Analog 0
#define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
#define	BLACK   						0x0000
#define CUSTOM_RED          0xFBCC

// TouchDisplay td = TouchDisplay();
gfxButton gfx;
MCUFRIEND_kbv tft;
void addButton();

void setup(void) {
  Serial.begin(9600);
  uint32_t when = millis();
  //    while (!Serial) ;   //hangs a Leonardo until you connect a Serial
  if (!Serial) delay(5000);           //allow some time for Leonardo
  Serial.println("Serial took " + String((millis() - when)) + "ms to start");
  //    tft.reset();                 //hardware reset
  uint16_t ID = tft.readID(); //
  Serial.print("ID = 0x");
  Serial.println(ID, HEX);
  if (ID == 0xD3D3) ID = 0x9481; // write-only shield
  //    ID = 0x9329;                             // force ID
  tft.begin(ID);
  tft.fillScreen(0x0000);

  gfx.begin(tft);
  addButton();
}


void loop() {

}


void addButton() {
  gfxButton newButton = gfx.initButton("testPage", 100, 110, 50, 40, true, 5);
  gfx.drawButton(newButton, CUSTOM_RED);
  gfxButton newButton2 = gfx.initButton("testPage2", 200, 110, 50, 40, true, 5);
  gfx.drawButton(newButton2, CUSTOM_RED);
  // tft.fillRoundRect(newButton.x, newButton.y, newButton.w, newButton.h, newButton.radius, CUSTOM_RED);
  gfxButton myArray[] = {newButton, newButton2};
  Serial.print("array: ");
  Serial.println(myArray[0].x);

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
