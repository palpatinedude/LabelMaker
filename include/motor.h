#ifndef MOTOR_H_
#define MOTOR_H_

#include <AccelStepper.h>

class Motor {
public:
    // constructor
    Motor(int enPin, int stepPin, int dirPin);
  
    // functions
    void moveSteps(int steps);  // move a given number of steps
    void setDirection(bool direction);  // set direction: true or false
    void enableMotor(bool enable);  // enable or disable the motor
    void setSpeed(float speed);  // set speed in steps per second
    void setAcceleration(float acceleration);  // set acceleration for the motor
    void moveTo(int targetPosition);  // move to a specific target position
    void run();  // run motor (continuously move if needed)
    void stop();  // stop the motor
    AccelStepper& getStepper();  // getter for AccelStepper

private:
    // motor pins
    int enPin, stepPin, dirPin;
    
    AccelStepper stepper;
};

extern Motor motorX;
extern Motor motorY;

#endif    // MOTOR_H_
