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
}

bool Button::isDown()
{
  int actualState = digitalRead(pin);
  if (actualState == HIGH)
  {
    if (downStart == 0)
    {
      downStart = millis(); 
      state = HIGH;
    }
    
    return true; 
  }
  
  if (state == HIGH && actualState == LOW)
  {
    state = LOW;
    downStart = 0;  
  }
  
  return false;
}

int Button::downForMilliseconds(){
  return state == HIGH ? (int)(millis() - downStart) : 0;
}

Button::~Button()
{
}
