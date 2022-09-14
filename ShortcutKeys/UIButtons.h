#include "Arduino.h"
#include "Arduino_AVRSTL.h"
#include <Elegoo_GFX.h>
#include <Elegoo_TFTLCD.h>
#include <TouchScreen.h>

#ifndef UI_BUTTON_H
#define UI_BUTTON_H

#define CHARACTER_WIDTH 10
#define CHARACTER_HEIGHT 15



class Point
{
  public:
    uint16_t x, y;

    Point(void) : x(0), y(0) {}
    Point(uint16_t x, uint16_t y) : x(x), y(y) {}

    bool operator==(Point p)
    {
      return ((p.x == x) && (p.y == y));
    }

    bool operator!=(Point p)
    {
      return ((p.x != x) || (p.y != y));
    }
};

class UIButton
{
  public:
    enum ButtonTypes { Flat, Rounded, Circle };
  
    UIButton(
      Elegoo_TFTLCD* lcdDisplay, 
      const char* descr, 
      const char* str, 
      Point pos, 
      Point objSize, 
      uint16_t backColor, 
      uint16_t foreColor, 
      ButtonTypes type);
    void Draw(void);
    void SetClickedFunction(void (*function)());
    bool Clicked(uint16_t x, uint16_t y);

  protected:
    ButtonTypes bttnType;
    Elegoo_TFTLCD* lcdDisplay;
    Point objPos, objSize;
    uint16_t backColor, foreColor;
    char strText[32];
    char strDescr[4];
    void (*clickedFunction)();
};


#endif
