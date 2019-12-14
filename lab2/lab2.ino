#include "button.h"
#include <Servo.h>
#include "LedControl.h"

#define BUTTON_PIN 22
#define SERVO_PIN 7
#define MAX_POWER 64
#define MAX_DELAY_FOR_SWING 16
#define DELAY_FOR_SWING_STEP 4
#define RANDOM_PULSE_THRESHOLD 20
#define SWING_ANGLE 90

Servo servo;
Button button(BUTTON_PIN);
bool wasButtonDown = false;
int buttonDownForAccumulated = 0;
const int servoInitialPosition = 0;
const int dataPin = 12;
const int clkPin = 10;
const int csPin = 11;
LedControl lc = LedControl(dataPin, clkPin, csPin, 1);

void setup()
{
  lc.shutdown(0, false);
  lc.setIntensity(0, 16);
  lc.clearDisplay(0);
  servo.attach(SERVO_PIN);
  servo.write(servoInitialPosition);
}

void loop()
{
  int iteration = 0;
  int power = 0;
  int buttonDownFor = button.downForMilliseconds();

  while (buttonDownFor >= RANDOM_PULSE_THRESHOLD)
  {
    buttonDownForAccumulated = buttonDownFor;
    resetDisplay();
    power = iteration % MAX_POWER + 1;
    print(power);
    iteration++;
    buttonDownFor = button.downForMilliseconds();
    delay(5);
  }

  if (buttonDownForAccumulated < RANDOM_PULSE_THRESHOLD)
  {
    return;
  }
  buttonDownForAccumulated = 0;

  hit(power);
  resetServo();
  resetDisplay();
}

void hit(int power)
{
  for (int i = 0; i < SWING_ANGLE; i++)
  {
    servo.write(i);
    delay(MAX_DELAY_FOR_SWING - power / DELAY_FOR_SWING_STEP);
  }
}

void resetServo()
{
  for (int i = 0; i < SWING_ANGLE; i++)
  {
    servo.write(SWING_ANGLE - 1 - i);
    delay(40);
  }
}

void print(int power)
{
  int columns = power / 8;
  for (int i = 0; i < columns; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      lc.setLed(0, i, j, true);
    }
  }
  int left_to_print = power - (power / 8) * 8;
  if (left_to_print > 0)
  {
    for (int k = 0; k < left_to_print; k++)
    {
      lc.setLed(0, columns, k, true);
    }
  }
}

void resetDisplay()
{
  lc.clearDisplay(0);
}
