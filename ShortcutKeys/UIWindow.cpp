#include "UIWindow.h"

UIWindow::UIWindow(uint8_t index)
{
  this->windowIndex = index;
}

void UIWindow::Draw(void)
{
  for(int i = 0; i < windowButtons.size(); i++)
  {
    windowButtons[i]->Draw();
  }
}

void UIWindow::ListenToClicks(uint16_t x, uint16_t y)
{
  for(int i = 0; i < windowButtons.size(); i++)
  {
    if(windowButtons[i]->Clicked(x, y))
    {
      break;
    }
  }
}

void UIWindow::AddElement(UIButton* element)
{
  windowButtons.push_back(element);
}
