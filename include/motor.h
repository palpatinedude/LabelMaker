#include <AccelStepper.h>

// motor class 
class Motor {
public:
    // constructor
    Motor(int enPin, int stepPin, int dirPin);
  
    // functions
    void moveSteps(int steps);
    void setDirection(bool direction);
    void enableMotor(bool enable);
    //void moveTo(int targetPosition);  // Move to a target position
   // void runToPosition();  // Block until the motor reaches the target position
  
   // variables
private:
    // motor pins
    int enPin, stepPin, dirPin;
  
    // AccelStepper instance
    AccelStepper stepper;
};
