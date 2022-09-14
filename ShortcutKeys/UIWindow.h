#include "UIButtons.h"

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

class UIWindow
{
  public:
    UIWindow(uint8_t index);
    void Draw(void);
    void ListenToClicks(uint16_t x, uint16_t y);
    void AddElement(UIButton* element);

  protected:
    uint8_t windowIndex;
    std::vector<UIButton*> windowButtons;
};

#endif
