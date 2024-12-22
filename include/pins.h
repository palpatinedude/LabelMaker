#ifndef LABELMAKER_H
#define LABELMAKER_H

#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "motor.h"

// power and control pins
#define BUTTON_PIN 4          // button with pull-up
#define PEN_PIN 13            // servo for pen control
#define PEN_DOWN_ANGLE 180    // angle for pen up
#define PEN_UP_ANGLE 110      // angle for pen down

// define steps per 1 cm for each motor
#define X_per_cm 4250         // X-axis steps per cm
#define Y_per_cm 235          // Y-axis steps per cm

// stepper drivers for motors
// X-axis motor pins
#define X_EN_PIN 12           // motor enable: LOW to enable, HIGH to disable
#define X_STEP_PIN 26         // step: each rising edge moves the motor one step
#define X_DIR_PIN 25          // direction: controls the motor direction

// Y-axis motor pins
#define Y_EN_PIN 33           // motor enable: LOW to enable, HIGH to disable
#define Y_STEP_PIN 22         // step: Y-axis motor
#define Y_DIR_PIN 23          // direction: Y-axis motor

// motor instances
extern Motor motorX;            // X-axis motor instance
extern Motor motorY;            // Y-axis motor instance

// servo instance for pen control
extern Servo penServo;          // pen servo control

// current positions and rotation count
extern int currentPositionX;    // current position of X-axis motor
extern int currentPositionY;    // current position of Y-axis motor
extern int rotations;           // number of tape rotations completed

// full rotation of the tape 
const float TAPE_CIRCUMFERENCE = 28.0;  // circumference of the tape in cm
const int stepsFullRotationY = round(TAPE_CIRCUMFERENCE * Y_per_cm); // total steps for one full rotation of the tape

// motor home and max positions
extern int HOME_POSITION;       // initial home position for X-axis motor
const int MAX_POSITION = 14875; // maximum position for the X-axis motor

// function prototypes
/*
void setupMotors(Motor &motorX, Motor &motorY);        // setup motors
void setupServo(Servo &penServo);                      // setup servo for pen control
void setMotorParameters(Motor &motor, int speed, int acceleration);  // set motor speed and acceleration
void firstHoming();    
*/

                        // control pen up or down

/*
void drawLetter(char letter);                          // draw a letter
void drawSquare(int squareSideLength);                 // draw a square with specified side length
void drawHorizontalLine(int lineLength);               // draw a horizontal line with specified length
void drawVerticalLine(int lineLength);                 // draw a vertical line with specified length
                        */
/*
void testMotor(Motor &motor, int steps);               // test motor movement by a specified number of steps
void penControl(bool down);                           
void homing();                                         // home the motors to their initial positions
void checkHoming();                                    // check if homing is complete
void checkTapeRotation();                              // check the tape rotation status
*/
// void setupWiFiAndServer();                         // future Wi-Fi and server setup (optional)

#endif // LABELMAKER_H
