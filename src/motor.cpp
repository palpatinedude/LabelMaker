#include "../include/motor.h"

// pinMode is a function that sets the mode of a pin to either input or output
// digitalWrite is a function that writes a high or low value to a digital pin 
 


// motor constructor initialization
Motor::Motor(int enPin, int stepPin, int dirPin) 
  : stepper(AccelStepper::DRIVER, stepPin, dirPin) {
  this->enPin = enPin;
  this->stepPin = stepPin;
  this->dirPin = dirPin;

  // motor pins as outputs
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, HIGH);  // when high the motor is disabled
  pinMode(dirPin, OUTPUT);    // set direction pin as output
}

// move a given number of steps
void Motor::moveSteps(int steps) {
  stepper.move(steps); 
}

// do i need that??
// set direction: true or false
void Motor::setDirection(bool direction) { 
  digitalWrite(dirPin, direction ? HIGH : LOW);
}

// enable or disable the motor
void Motor::enableMotor(bool enable) { 
  digitalWrite(enPin, enable ? LOW : HIGH);  // enable (LOW) or disable (HIGH)
}

// set speed in steps per second
void Motor::setSpeed(float speed) {
  stepper.setMaxSpeed(speed);  // set t maximum speed
}

// set acceleration for the motor that means how fast the motor will reach the maximum speed
void Motor::setAcceleration(float acceleration) {
  stepper.setAcceleration(acceleration); 
}

// move to a specific target position
void Motor::moveTo(int targetPosition) {
  stepper.moveTo(targetPosition);  // set target position
  stepper.runToPosition();  // block until  motor reaches target
}

void Motor::stop() {
  stepper.stop();
}

// run motor that means continuously move if needed
void Motor::run() {
  stepper.run();  
}

// getter for accelstepper 
AccelStepper& Motor::getStepper() {
  return stepper;  
}
