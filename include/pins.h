#ifndef LABELMAKER_H
#define LABELMAKER_H

#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "motor.h"
#include "symbols.h"

// power and control 
#define BUTTON_PIN 4  // button with pull-up
#define PEN_PIN 13        // servo s for pen control

// stepper drivers for motors
// pen stepper x
#define X_EN_PIN 12       // motor enable : LOW to enable, HIGH to disable
#define X_STEP_PIN 26      // step : each rising edge takes the motor one step
#define X_DIR_PIN 25       // direction : controls the direction of the motor

// tape stepper y
#define Y_EN_PIN 33       // motor enable : LOW to enable, HIGH to disable
#define Y_STEP_PIN 22     // step : for Y-axis motor
#define Y_DIR_PIN 23      // direction:   for Y-axis motor


extern Motor motorX;
extern Motor motorY;
extern Servo penServo;
extern int currentPosition;

const int HOME_POSITION = 9200;   
const int MAX_POSITION = 27600;  

// distance per step for each axis 
const float X_DISTANCE_PER_STEP = 0.01178;  // mm per step for X-axis (12mm pulley)
const float Y_DISTANCE_PER_STEP = 0.07265;  // mm per step for Y-axis (74mm tape roller)

//extern const Letter letterMovements[26]; // array of letter movements (all the letters)

// function prototypes
void setupPins(Motor &motorX, Motor &motorY,Servo  &penServo);
void setMotorParameters(Motor &motor, int speed, int acceleration);
void testMotor(Motor &motor , int steps);
void penControl(bool down);
void drawLetter(char letter);
void drawSquare(int squareSideLength);
void drawHorizontalLine(int lineLength);
void drawVerticalLine(int lineLength);  
void initialization();
void homing();

//void setupWiFiAndServer();

#endif // LABELMAKER_H