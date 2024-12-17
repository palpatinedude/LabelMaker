#ifndef INIT_H
#define INIT_H

#include <ESP32Servo.h>
#include "motor.h"

// function prototypes
void firstHoming();
void initialization();
void setupMotors(Motor &motorX, Motor &motorY);
void setupServo(Servo &penServo);
void setMotorParameters(Motor &motor, int speed, int acceleration);

#endif // INIT_H