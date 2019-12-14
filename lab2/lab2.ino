#include "button.h"
#include <Servo.h>
#include "LedControl.h"

#define BUTTON_PIN 10
#define SERVO_PIN


Servo servo;
Button button(BUTTON_PIN);
bool wasButtonDown = false;
int buttonDownFor = -1;
const int servoInitialPosition = 0;

void setup()
{
  servo.attach(SERVO_PIN);
  servo.write(servoInitialPosition);
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
  
  hit(buttonDownFor % 100);
  //reset servo
  //reset display
}

void hit(int power)
{
  //todo
  servo.write(90);
}

void resetServo()
{
  servo.write(servoInitialPosition);
}

void print(int power)
{
  //todo
}

void resetDisplay()
{
  //todo
}
