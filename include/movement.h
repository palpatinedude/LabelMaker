#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "motor.h"
#include "pins.h"
#include <Arduino.h>


// function prototypes for movement operations
void checkTapeRotation();
void checkHoming();
void homing();
void testMotor(Motor &motor, int steps);
void penControl(bool down);

#endif // MOVEMENT_H