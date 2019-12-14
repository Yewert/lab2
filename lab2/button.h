#pragma once

class Button
{
private:
  int pin;
  int state;
  unsigned long downStart;
public:
  bool isDown();
  int downForMilliseconds();
  Button(int _pin);
  ~Button();
};

Button::Button(int _pin)
{
  pin = _pin;
  state = LOW;
  downStart = 0;
  pinMode(pin, INPUT_PULLUP);
}

bool Button::isDown()
{
  int actualState = digitalRead(pin);
  if (actualState == LOW)
  {
    if (downStart == 0)
    {
      downStart = millis(); 
      state = LOW;
    }
    
    return true; 
  }
    
  state = HIGH;
  downStart = 0;
  
  return false;
}

int Button::downForMilliseconds(){
  return isDown() ? (int)(millis() - downStart) : 0;
}

Button::~Button()
{
}
