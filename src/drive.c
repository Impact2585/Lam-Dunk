#include "main.h"

#define JOYSTICK_DEADZONE 15 // deadzone per channel

void driveSet(int Y, int X);
void driveSetLeft(int speed);
void driveSetRight(int speed);

// linearizing array, goes to 256 to save CPU cycles; xmax + ymax = 256
const unsigned int TrueSpeed[256] = {
  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
  0, 21, 21, 21, 22, 22, 22, 23, 24, 24,
  25, 25, 25, 25, 26, 27, 27, 28, 28, 28,
  28, 29, 30, 30, 30, 31, 31, 32, 32, 32,
  33, 33, 34, 34, 35, 35, 35, 36, 36, 37,
  37, 37, 37, 38, 38, 39, 39, 39, 40, 40,
  41, 41, 42, 42, 43, 44, 44, 45, 45, 46,
  46, 47, 47, 48, 48, 49, 50, 50, 51, 52,
  52, 53, 54, 55, 56, 57, 57, 58, 59, 60,
  61, 62, 63, 64, 65, 66, 67, 67, 68, 70,
  71, 72, 72, 73, 74, 76, 77, 78, 79, 79,
  80, 81, 83, 84, 84, 86, 86, 87, 87, 88,
  88, 89, 89, 90, 90, 127, 127, 127,

  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127, 127, 127,
  127, 127, 127, 127, 127, 127, 127, 127
};

int X = 0, Y = 0;
int tempX = 0;
int tempY = 0;
int tempXPartner = 0;
int tempYPartner = 0;

void DriveTask(void *ignore) {
  while (1) {
    tempX = joystickGetAnalog(1, 1);
    tempY = joystickGetAnalog(1, 3);
    tempXPartner = joystickGetAnalog(2, 1);
    tempYPartner = joystickGetAnalog(2, 3);

    if (abs(tempYPartner) > JOYSTICK_DEADZONE) { // check if partner overrides Y
      Y = -tempYPartner / 2;
    } else {
      Y = -tempY;
    }

    if (abs(tempXPartner) > JOYSTICK_DEADZONE) { // check if partner overrides X
      X = tempXPartner / 2;
    } else {
      X = tempX;
    }

    driveSet(Y, X);

    taskDelay(25);
  }
}

void driveSet(int Y, int X) {
  // set drive speed to linearized PWM
  driveSetLeft(signum(Y - X) * TrueSpeed[abs(Y - X)]);
  driveSetRight(signum(Y + X) * TrueSpeed[abs(Y + X)]);
}

void driveSetLeft(int speed) {
  motorSet(8, speed);
  motorSet(9, -speed);
}

void driveSetRight(int speed) {
  motorSet(2, speed);
  motorSet(3, -speed);
}
