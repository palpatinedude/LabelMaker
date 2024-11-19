#ifndef LABELMAKER_H
#define LABELMAKER_H

#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "motor.h"
#include "symbols.h"

// power and control 
#define BUTTON_PIN 19     // button with pull-up
#define PEN_PIN 25        // servo s for pen control

// stepper drivers X-axis ,Y-axis
#define X_EN_PIN 15       // motor enable : LOW to enable, HIGH to disable
#define X_STEP_PIN 2      // step : each rising edge takes the motor one step
#define X_DIR_PIN 4       // direction : controls the direction of the motor
#define Y_EN_PIN 13       // motor enable : LOW to enable, HIGH to disable
#define Y_STEP_PIN 12     // step : for Y-axis motor
#define Y_DIR_PIN 14      // direction:   for Y-axis motor

// Motion Configuration
const int noOfSteps = 250;  // # of steps to move in each direction
const int microSecondsDelay = 1000;  // delay in microseconds between each step



extern Motor motorX;
extern Motor motorY;
extern Servo penServo;
//extern const Letter letterMovements[26]; // array of letter movements (all the letters)

// function prototypes
void setupPins();
void penControl(bool down);
void moveTo(int dx, int dy, bool penDown);
void drawLetter(char letter);

#endif // LABELMAKER_H