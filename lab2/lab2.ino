#include "button.h"

#define BUTTON_PIN 10

Button button(BUTTON_PIN);
bool wasButtonDown = false;
int buttonDownFor = -1;

void setup()
{
  
}

void loop()
{
  buttonDownFor = 0;
  while (button.isDown())
  {
    buttonDownFor = button.downForMilliseconds();
    //print on display
  }
  
  if (buttonDownFor == 0)
  {
    return;
  }
  
  //hit
  //reset servo
  //reset display
}
