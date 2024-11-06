// moveTo() --> target position
// runToPosition() --> block operation
// write() --> set angle of servo


#include <Arduino.h>
#include "../lib/header.h"

// ######################## FUNCTIONS DEFINITIONS ########################

// motor's constructor initialization
Motor::Motor(int enPin, int stepPin, int dirPin)
    : enPin(enPin), stepPin(stepPin), dirPin(dirPin), stepper(AccelStepper::DRIVER, stepPin, dirPin) {
  
    // set motor pins as outputs
    pinMode(enPin, OUTPUT);
    pinMode(stepPin, OUTPUT);
    pinMode(dirPin, OUTPUT);

    // initially enable the motor (LOW)
    digitalWrite(enPin, LOW);

    // initial direction 
    digitalWrite(dirPin, LOW);
}

// move the motor by a certain number of steps
void Motor::moveSteps(int steps) {
    for (int i = 0; i < steps; i++) {
        digitalWrite(stepPin, !digitalRead(stepPin));  // toggle the step pin
        delayMicroseconds(microSecondsDelay);  
    }
}

// set the direction of the motor (true = forward, false = backward)
void Motor::setDirection(bool direction) {
    digitalWrite(dirPin, direction ? HIGH : LOW);
}

// enable or disable the motor
void Motor::enableMotor(bool enable) {
    digitalWrite(enPin, enable ? LOW : HIGH);  // LOW = enable, HIGH = disable
}


void setupPins() {
     // initialize pin modes for all motors and control pins
    pinMode(BUTTON_PIN, INPUT_PULLUP);  
    pinMode(PEN_PIN, OUTPUT);           

    // motors are enabled at the start
    motorX.enableMotor(true);
    motorY.enableMotor(true);
    penServo.attach(PEN_PIN); 
}

//  draw the letter based on input
void drawLetter(char letter) {
    letter = toupper(letter);  // convert to uppercase
    if (letter >= 'A' && letter <= 'Z') {
        int index = letter - 'A';  // convert letter to array index (0 for 'A', 1 for 'B', etc.)
        const Letter& movements = letterMovements[index];
        
        penControl(false);  // lift the pen initially
        motorX.moveSteps(movements.xSteps[0]);  // move tfrom start position
        motorY.moveSteps(movements.ySteps[0]);
        
        penControl(true);   // lower the pen to draw
        for (int i = 1; i < movements.numSteps; i++) {
            motorX.moveSteps(movements.xSteps[i]);  // move according to x and y steps
            motorY.moveSteps(movements.ySteps[i]);
        }
        penControl(false);  // lift the pen after drawing
    }
}

/*
void penControl(bool down) {
    if (down) {
        digitalWrite(PEN_PIN, HIGH);  // pen down (servo active)
    } else {
        digitalWrite(PEN_PIN, LOW);   // pen up (servo inactive)
    }
}*/
// or

void penControl(bool down) {
    if (down) {
        penServo.write(90);  // lower the pen
    } else {
        penServo.write(0);   // raise the pen
    }
}

// ####################### VARIABLES DEFINITIONS #######################    
const Letter letterMovements[26] = {
    {{0, 50, 100, 50, 0}, {0, 100, 200, 300, 400}, 5},  // 'A'
    {{0, 50, 100}, {0, 100, 200}, 3},  // 'B' 
    // others
};