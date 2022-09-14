#include "UIWindow.h"

// LCD Pins
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Touch Screen Pins
#define YP A3
#define XM A2
#define YM 9
#define XP 8

// Touch Screen Constants
#define TS_MINX 120
#define TS_MAXX 900
#define TS_MINY 70
#define TS_MAXY 920

#define MINPRESSURE 10
#define MAXPRESSURE 1000

Elegoo_TFTLCD lcdDisplay(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen touchScreen = TouchScreen(XP, YP, XM, YM, 300);

//std::vector<UIWindow*> windows;
//uint8_t currentIndex = 0;
std::vector<UIButton*> buttons;

void DrawScreenNew()
{
  // Mute or Unmute Button (TeamSpeak)
  UIButton* bttnMtNmtTs = new UIButton(&lcdDisplay, "TS", "Mute\nor\nUnmute", Point(5, 5), Point(100, 75), 0xDF1E, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnMtNmtTs->SetClickedFunction([]{Serial.println("mtntmts");});
  bttnMtNmtTs->Draw();
  buttons.push_back(bttnMtNmtTs);

  // Mute or Unmute Button (Discord)
  UIButton* bttnMtNmtDc = new UIButton(&lcdDisplay, "DC", "Mute\nor\nUnmute", Point(110, 5), Point(100, 75), 0xEFFD, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnMtNmtDc->SetClickedFunction([]{Serial.println("mtntmdc");});
  bttnMtNmtDc->Draw();
  buttons.push_back(bttnMtNmtDc);

  // Play Valorant Button
  UIButton* bttnPlyVlrnt = new UIButton(&lcdDisplay, "", "Play\nValo", Point(215, 5), Point(100, 75), 0xEFBF, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnPlyVlrnt->SetClickedFunction([]{Serial.println("plyvlrnt");});
  bttnPlyVlrnt->Draw();
  buttons.push_back(bttnPlyVlrnt);

  // Shutdown PC Button
  UIButton* bttnShtdwnPc = new UIButton(&lcdDisplay, "", "PC\nShutdown", Point(5, 85), Point(100, 75), 0xFEB6, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnShtdwnPc->SetClickedFunction([]{Serial.println("pcshtdwn");});
  bttnShtdwnPc->Draw();
  buttons.push_back(bttnShtdwnPc);

  // Clip Capture Button
  UIButton* bttnClpCptr = new UIButton(&lcdDisplay, "", "Clip\nCapture", Point(110, 85), Point(100, 75), 0xFF1B, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnClpCptr->SetClickedFunction([]{Serial.println("clpcptr");});
  bttnClpCptr->Draw();
  buttons.push_back(bttnClpCptr);

  // Silent Mode Button
  UIButton* bttnslntMd = new UIButton(&lcdDisplay, "", "Silent\nMode", Point(215, 85), Point(100, 75), 0xEFFE, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnslntMd->SetClickedFunction([]{Serial.println("slntmd");});
  bttnslntMd->Draw();
  buttons.push_back(bttnslntMd);

  // Global Mute Button
  UIButton* bttnGlblMt = new UIButton(&lcdDisplay, "", "Global\nMute", Point(110, 165), Point(100, 75), 0xE41C, 0xFFFF, UIButton::ButtonTypes::Rounded);
  bttnGlblMt->SetClickedFunction([]{Serial.println("glblmt");});
  bttnGlblMt->Draw();
  buttons.push_back(bttnGlblMt);

  // Skip Song Button
  UIButton* bttnNxt = new UIButton(&lcdDisplay, "", ">>", Point(50, 202), Point(37, 75), 0x7BEF, 0xFFFF, UIButton::ButtonTypes::Circle);
  bttnNxt->SetClickedFunction([]{Serial.println("skpsng");});
  bttnNxt->Draw();
  buttons.push_back(bttnNxt);

  // Play Pause Button
  UIButton* bttnPlyPs = new UIButton(&lcdDisplay, "", "[]/||", Point(265, 202), Point(37, 75), 0x7BEF, 0xFFFF, UIButton::ButtonTypes::Circle);
  bttnPlyPs->SetClickedFunction([]{Serial.println("plyps");});
  bttnPlyPs->Draw();
  buttons.push_back(bttnPlyPs);
}

void setup()
{
  Serial.begin(9600);
  Serial.println("[INFO] Device started!\n");
  
  // Get Id from Display
  lcdDisplay.reset();
  uint16_t id = lcdDisplay.readID();
  //Serial.print("LCD Driver found! ID: ");
  //Serial.println(id, HEX);

  lcdDisplay.begin(id == 0x101 ? 0x9341 : id);
  lcdDisplay.setRotation(3);
  lcdDisplay.fillScreen(0x0000);

  //DrawScreen();
  DrawScreenNew();

  pinMode(13, OUTPUT);
  pinMode(XM, OUTPUT);
  pinMode(YP, OUTPUT);

  Serial.println("dvcrdy");
}

void loop()
{
  digitalWrite(13, HIGH);
  TSPoint tsPoint = touchScreen.getPoint();
  digitalWrite(13, LOW);

  if(tsPoint.z > MINPRESSURE && tsPoint.z < MAXPRESSURE)
  {
    uint16_t y = map(tsPoint.x, TS_MINX, TS_MAXX, 0, lcdDisplay.height());
    uint16_t x = map(tsPoint.y, TS_MINY, TS_MAXY, 0, lcdDisplay.width());
    
    //Serial.print("Touch Pos: X = ");
    //Serial.print(x);
    //Serial.print(" Y = ");
    //Serial.println(y);
    
    for(int i = 0; i < buttons.size(); i++)
    {
      buttons[i]->Clicked(x, y);
    }

    delay(1000);
  }
}
