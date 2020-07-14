// #include "gfxButton.h"
// #include "MCUFRIEND_kbv.h"
// #include "TouchScreen.h"
// #include "Arimo_Regular_24.h"
// #include "Aperture_Icon.h"
//
// #define LCD_CS A3 // Chip Select goes to Analog 3
// #define LCD_CD A2 // Command/Data goes to Analog 2
// #define LCD_WR A1 // LCD Write goes to Analog 1
// #define LCD_RD A0 // LCD Read goes to Analog 0
// #define LCD_RESET A4 // Can alternately just connect to Arduino's reset pin
// #define	BLACK   						0x0000
// #define	WHITE   						0xFFFF
// #define CUSTOM_GREEN_LITE		0x9736
// #define CUSTOM_GREEN				0x4ECC
// #define CUSTOM_RED					0xFBCC
// #define CUSTOM_RED_LITE			0xFCD1
// #define CUSTOM_BLUE					0x4EDE
// #define CUSTOM_GREY					0xCE7A
// #define CUSTOM_GREY_LITE		0xDEFB
//
// // grand central M4 + 3.5" TFT
// // #define TS_MINX 					846
// // #define TS_MAXX 					148
// // #define TS_MINY 					937
// // #define TS_MAXY 					140
//
// // grand central M4 + 2.8" TFT
// #define TS_MINX 					320
// #define TS_MAXX 					760
// #define TS_MINY 					235
// #define TS_MAXY 					810
//
// // pin definitions for touch inputs
// #define YP 								A3 						// must be an analog pin, use "An" notation!
// #define XM 								A2            // must be an analog pin, use "An" notation!
// #define YM 								9             // can be a digital pin
// #define XP 								8             // can be a digital pin
//
// // TouchDisplay td = TouchDisplay();
// gfxButton gfxB;
// gfxTouch gfxT;
// MCUFRIEND_kbv tft;
// TouchScreen	ts = TouchScreen(XP, YP, XM, YM, 200);
// void initButtons();
// void drawButtons();
// void fontSize();
// void placeText();
// void buttonCheck(String screen);
// void testFunction1(bool btnActive);
// void testFunction2(bool btnActive);
// void testFunction3(bool btnActive);
// void testFunction4(bool btnActive);
// void testFunction5(bool btnActive);
//
// long timer = 0;
// bool buttonState = false;
// int counter = 0;
//
// // gfxButton newButton1   =   gfxB.initButton("testPage", "drawRoundRect", 100, 110, 50, 40, 5, CUSTOM_RED);
// // gfxButton newButton2  =   gfxB.initButton("testPage", "fillRoundRect", 200, 110, 175, 40, 5, CUSTOM_RED);
// // gfxButton newButton3  =   gfxB.initButton("testPage", "fillCircle", 350, 250, 0, 0, 50, CUSTOM_BLUE);
// // gfxTouch  newTouch1    =   gfxT.addToggle(newButton, testFunction, "newButton", 20);
// // gfxTouch  newTouch2   =   gfxT.addMomentary(newButton2, testFunction2, "newButton2", 20);
// // gfxTouch  newTouch3   =   gfxT.addMomentary(newButton3, testFunction3, "newButton3", 20);
//
// gfxButton newButton1  =   gfxB.initButton("testPage", "fillRoundRect", 10,  10, 150, 60, 5, CUSTOM_RED);
// gfxButton newButton1a =   gfxB.initButton("testPage", "fillRoundRect", 10,  10, 150, 60, 5, CUSTOM_RED);
// gfxButton newButton2  =   gfxB.initButton("testPage", "fillRoundRect", 10,  90, 150, 60, 5, CUSTOM_BLUE);
// gfxButton newButton3  =   gfxB.initButton("testPage", "fillRoundRect", 10, 170, 150, 60, 5, CUSTOM_GREEN);
// gfxButton newButton4  =   gfxB.initButton("testPage", "fillRoundRect", 10, 250, 150, 60, 5, CUSTOM_GREY);
// gfxButton newBitmap1  =   gfxB.initBitmapButton("testPage", aperture, 200, 150, 50, 50, CUSTOM_RED);
// gfxTouch  newTouch1   =   gfxT.addMomentary(newButton1a, testFunction1, "newButton1", 20);
// gfxTouch  newTouch2   =   gfxT.addMomentary(newButton2, testFunction2, "newButton2", 20);
// gfxTouch  newTouch3   =   gfxT.addToggle(newButton3, testFunction3, "newButton3", 20);
// gfxTouch  newTouch4   =   gfxT.addToggle(newButton4, testFunction4, "newButton4", 20);
// gfxTouch  newTouch5   =   gfxT.addMomentary(newBitmap1, testFunction5, "newBitmap1", 20);
// #define arrayElements 5
// gfxButton buttonArray[arrayElements];
// gfxTouch touchArray[arrayElements];
//
//               // xPos  yPos icon    w     h   color
// // tft.drawBitmap(155, 95, cogWheel, 50, 50, GRAY);
//
// bool setupFlag = false;
//
// void setup(void) {
//   Serial.begin(9600);
//   tft.reset();
//   uint16_t ID = tft.readID(); //
//   tft.begin(ID);
//   tft.fillScreen(0x0000);
//   tft.setRotation(1);
//
//   gfxT.setToggleDebounce(250);
//   gfxT.setMomentaryDebounce(50);
//
//   // initButtons();
//   // drawButtons();
//   // newButton2.writeText(tft, Arimo_Regular_24, String("Test Text"), WHITE, "c");
//   // newButton3.writeText(tft, Arimo_Regular_24, String("Circle"), WHITE);
//   // newButton1.writeTextTopCentre(tft, Arimo_Regular_24, String("Step Dist."), WHITE);
//   // newButton2.writeTextCentre(tft, Arimo_Regular_24, String("Step Nr"), WHITE);
//   // newButton3.writeTextCentre(tft, Arimo_Regular_24, String("Rail Pos"), WHITE);
//   // newButton4.writeTextCentre(tft, Arimo_Regular_24, String("Flash"), BLACK);
//
//   // tft.drawBitmap(200, 150, newBitmap1.bitmap, 50, 50, CUSTOM_RED);
// }
//
//
// void loop() {
//   if (setupFlag == false) {
//     // delay(2000);
//     initButtons();
//     drawButtons();
//     newButton1.writeTextTopCentre(tft, Arimo_Regular_24, String("Step Dist."), WHITE);
//     newButton1a.writeTextBottomCentre(tft, Arimo_Regular_24, String(counter), WHITE);
//     newButton2.writeTextLeft(tft, Arimo_Regular_24, String("Step Nr"), WHITE);
//     newButton3.writeTextRight(tft, Arimo_Regular_24, String("Rail Pos"), WHITE);
//     newButton4.writeTextBottomCentre(tft, Arimo_Regular_24, String("Flash"), BLACK);
//
//     setupFlag = true;
//   }
//   if (millis() - timer >= 10) {
//     buttonCheck("testPage");
//     timer = millis();
//   }
// }
//
//
// void initButtons() {
//   buttonArray[0] = newButton1;
//   buttonArray[1] = newButton2;
//   buttonArray[2] = newButton3;
//   buttonArray[3] = newButton4;
//   buttonArray[4] = newBitmap1;
//
//   touchArray[0] = newTouch1;
//   touchArray[1] = newTouch2;
//   touchArray[2] = newTouch3;
//   touchArray[3] = newTouch4;
//   touchArray[4] = newTouch5;
// }
//
//
// void drawButtons() {
//   // for(int i=0; i < arrayElements; i++) {
//   //   if (buttonArray[i].screen == "testPage") {
//   //     buttonArray[i].drawButton(tft); // calling btn via array creates new scope :|
//   //     // newButton1.drawButton(tft);
//   //   }
//   // }
//
//   tft.drawRect(160, 120, 100, 60, CUSTOM_RED);
// }
//
//
// void buttonCheck(String currentScreen) {
//   TSPoint point = ts.getPoint();
//
//   // reset pinmodes for tft
//   pinMode(XM, OUTPUT);
//   pinMode(YP, OUTPUT);
//
//
//   int touch_x = map(point.y, TS_MINY, TS_MAXY, 0, tft.width());
//   int touch_y = map(point.x, TS_MINX, TS_MAXX, 0, tft.height());
//   int touch_z = point.z;
//
//   if (touch_z >= 50 && touch_z <= 1000) {
//
//     Serial.print("point.y: "); Serial.print(point.y);
//     Serial.print("   touch.x: ");Serial.println(touch_x);
//     Serial.print("point.x: "); Serial.print(point.x);
//     Serial.print("   touch.y: ");Serial.println(touch_y);
//
//     // for (int i=0; i < arrayElements; i++) {
//     //   touchArray[i].checkButton(currentScreen, touch_x, touch_y);
//     // }
//   }
//   // allow toggling button again once touch pressure zeroed
//   // if (touch_z == 0) {
//   //   for (int i=0; i < arrayElements; i++) {
//   //     if (touchArray[i].touchType == "toggle") {
//   //       touchArray[i].toggleCoolOff();
//   //     }
//   //   }
//   // }
// }
//
//
// void testFunction1(bool btnActive) {
//   if (btnActive == true) {
//     // newButton1.drawButton(tft, CUSTOM_GREEN);
//     counter++;
//     // newButton1.writeTextTopCentre(tft, Arimo_Regular_24, String("Step Dist."), WHITE);
//     newButton1a.writeTextBottomCentre(tft, Arimo_Regular_24, String(counter), WHITE);
//   }
//   // else {
//     // newButton1.drawButton(tft, CUSTOM_RED);
//     // newButton1.writeTextTopCentre(tft, Arimo_Regular_24, String("Step Dist."), WHITE);
//     // newButton1a.writeTextBottomCentre(tft, Arimo_Regular_24, String(counter), WHITE);
//   // }
// }
//
//
// void testFunction2(bool btnActive) {
//   Serial.println("test function 2");
//
//   if (btnActive == true) {
//     // newButton2.drawButton(tft, CUSTOM_GREEN);
//     newButton2.writeTextLeft(tft, Arimo_Regular_24, String("Test Text"), WHITE);
//   }
//   else {
//     // newButton2.drawButton(tft, CUSTOM_RED);
//     newButton2.writeTextLeft(tft, Arimo_Regular_24, String("Button Text"), WHITE);
//   }
// }
//
//
// void testFunction3(bool btnActive) {
//   Serial.println("test function 3");
//
//   if (btnActive == true) {
//     newButton3.drawButton(tft, CUSTOM_GREEN);
//     newButton3.writeTextRight(tft, Arimo_Regular_24, String("Circle"), WHITE);
//   }
//   else {
//     newButton3.drawButton(tft, CUSTOM_BLUE);
//     newButton3.writeTextRight(tft, Arimo_Regular_24, String("Circle"), WHITE);
//   }
// }
//
//
// void testFunction4(bool btnActive) {
//   Serial.println("test function 4");
//
//   if (btnActive == true) {
//     newButton4.drawButton(tft, CUSTOM_GREEN);
//     newButton4.writeTextBottomCentre(tft, Arimo_Regular_24, String("Circle"), WHITE);
//   }
//   else {
//     newButton4.drawButton(tft, CUSTOM_BLUE);
//     newButton4.writeTextBottomCentre(tft, Arimo_Regular_24, String("Circle"), WHITE);
//   }
// }
//
//
// void testFunction5(bool btnActive) {
//   Serial.println("test function 5");
//
//   if (btnActive == true) {
//     newBitmap1.drawButton(tft, CUSTOM_GREEN);
//   }
//   else {
//     newBitmap1.drawButton(tft, CUSTOM_BLUE);
//   }
// }
