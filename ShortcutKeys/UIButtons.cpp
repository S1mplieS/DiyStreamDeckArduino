#include "UIButtons.h"

UIButton::UIButton(
  Elegoo_TFTLCD* lcdDisplay, 
  const char* descr, 
  const char* str, 
  Point pos, 
  Point objSize, 
  uint16_t backColor, 
  uint16_t foreColor, 
  ButtonTypes type)
{
  this->lcdDisplay = lcdDisplay;

  int index = 0;
  while(str[index] != '\0' || index == 32)
  {
    this->strText[index] = str[index];
    index++;
  }
  this->strText[index] = '\0';

  index = 0;
  while(descr[index] != '\0' || descr == 4)
  {
    this->strDescr[index] = descr[index];
    index++;
  }
  this->strDescr[index] = '\0';
  
  this->objPos = pos;
  this->objSize = objSize;
  this->backColor = backColor;
  this->foreColor = foreColor;
  this->bttnType = type;
}

void UIButton::Draw(void)
{
  switch(bttnType)
  {
    case Flat:
      lcdDisplay->fillRect(objPos.x, objPos.y, objSize.x, objSize.y, backColor);
      break;
    case Rounded:
      lcdDisplay->fillRoundRect(objPos.x, objPos.y, objSize.x, objSize.y, 10, backColor);
      break;
    case Circle:
      lcdDisplay->fillCircle(objPos.x, objPos.y, objSize.x, backColor);
      break;
  }
  
  int linesFound = 1;
  for(int i = 0; i < strlen(strText); i++)
  {
    if(strText[i] == '\n')
    {
      linesFound++;
    }
  }

  lcdDisplay->setTextSize(2);
  lcdDisplay->setTextColor(foreColor);
  
  uint16_t margin_top = (objSize.y - (linesFound * (CHARACTER_HEIGHT + (linesFound - 1)))) / 2;
  uint8_t textIndex = 0;
  for(int lines = 0; lines < linesFound; lines++)
  {
    char currentLine[32];
    int index = 0;
    
    while(strText[textIndex] != '\n' && strText[textIndex] != '\0')
    {
      currentLine[index++] = strText[textIndex++];
    }
    currentLine[index] = '\0';
    textIndex++;

    uint16_t objLength = bttnType == ButtonTypes::Circle ? objSize.x * 2 : objSize.x;
    uint16_t margin_left = (objLength - ((index + 1) * CHARACTER_WIDTH)) / 2;
    margin_left = (margin_left == 0 || margin_left >= 320) ? objPos.x : margin_left;
    
    uint16_t margin_top_tmp = margin_top + (lines * (CHARACTER_HEIGHT + 3));
    margin_top_tmp = (margin_top_tmp == 0 || margin_top_tmp >= 240) ? objPos.y : margin_top_tmp;

    uint16_t txtPosX = bttnType == ButtonTypes::Circle ? (objPos.x + margin_left) - objSize.x : objPos.x + margin_left;
    uint16_t txtPosY = bttnType == ButtonTypes::Circle ? (objPos.y + margin_top_tmp) - objSize.x : objPos.y + margin_top_tmp;
    
    lcdDisplay->setCursor(txtPosX, txtPosY);
    lcdDisplay->println(currentLine);
  }

  if(strlen(strDescr) != 0)
  {
    lcdDisplay->setCursor(objPos.x + 5, objPos.y + 5);
    lcdDisplay->setTextSize(1);
    lcdDisplay->setTextColor(0xFFFF);
    lcdDisplay->println(strDescr);
  }
}

void UIButton::SetClickedFunction(void (*function)())
{
  this->clickedFunction = function;
}

bool UIButton::Clicked(uint16_t x, uint16_t y)
{
  uint16_t objX = bttnType == ButtonTypes::Circle ? objPos.x - objSize.x : objPos.x;
  uint16_t objY = bttnType == ButtonTypes::Circle ? objPos.y - objSize.x : objPos.y;

  uint16_t objLen = bttnType == ButtonTypes::Circle ? objSize.y : objSize.x;
  
  if((x >= objX && x <= (objX + objLen)) && (y >= objY && y <= (objY + objSize.y)))
  {
    if(clickedFunction != nullptr)
    {
      clickedFunction();
    }

    return true;
  }
  
  return false;
}
