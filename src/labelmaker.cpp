// moveTo() --> target position
// runToPosition() --> block operation
// write() --> set angle of servo
// 4550 steps approximately  1 cm stepper X
// 215 steps approximately 1 cm stepper Y
// reference point 0 where the button is pressed
// variable tape diameter circumference=28.5cm  ,outer diameter=9.07cm

#include <Arduino.h>
#include "../include/motor.h"
#include "../include/pins.h"


// ######################## FUNCTIONS DEFINITIONS ########################


/*
void setupMotors(Motor &motorX, Motor &motorY) {
    motorX.enableMotor(true);
    motorY.enableMotor(true);
    Serial.println("Motors setup complete.");
}

void setupServo(Servo &penServo) {
    penServo.attach(PEN_PIN);
    penControl(true);
    Serial.println("Servo setup complete.");
}


void initialization(){
    penControl(true); 
    while (digitalRead(BUTTON_PIN) == HIGH) {
        motorX.moveSteps(-3000);
        motorX.run();
    }
    motorX.stop(); // Stop motor after pressing the buttoSSn
    currentPositionX = 0; // Update current position
    motorX.getStepper().setCurrentPosition(0);  // Update current position
}

// set speed and acceleration parameters
void setMotorParameters(Motor &motor, int speed, int acceleration) {
    Serial.println("Setting motor parameters...");
    motor.setSpeed(speed);
    motor.setAcceleration(acceleration);
    Serial.println("Motor parameters set.");
}


//  draw the letter based on input
void drawLetter(char letter) {
    if (letter >= 'A' && letter <= 'Z') {
        int index = letter - 'A';  // convert letter to array index (0 for 'A', 1 for 'B', etc.)
        const Letter& movements = letterMovements[index];
        
        penControl(false);  // lift the pen initially
        motorX.moveSteps(movements.xSteps[0]);  // move from start position
        motorY.moveSteps(movements.ySteps[0]);
        
        penControl(true);   // lower the pen to draw
        for (int i = 1; i < movements.numSteps; i++) {
            motorX.moveSteps(movements.xSteps[i]);  // move according to x and y steps
            motorY.moveSteps(movements.ySteps[i]);
        }
        penControl(false);  // lift the pen after drawing
    }
}

void drawHorizontalLine(int lineLength) {
    Serial.println("Starting vertical line..."); 
    penControl(false); 
    // draw the upper horizontal line
    delay(1000);
    motorY.moveSteps(lineLength);  

    while (motorY.getStepper().isRunning()) {
        motorY.run();  
        currentPositionY = motorY.getStepper().currentPosition();
    }
    penControl(true);  
    Serial.println("Vertical line complete.");
}

void drawVerticalLine(int lineLength) {
    Serial.println("Starting vertical line..."); 
    penControl(false); 
  
    delay(1000);
    motorX.moveSteps(lineLength);  
    while (motorX.getStepper().isRunning()) {
        motorX.run();  
        currentPositionX = motorX.getStepper().currentPosition();
    }

    penControl(true);  
    Serial.println("Vertical line complete.");
}



void drawSquare(int squareSideLength) {
    // four sides of the square

    drawHorizontalLine(235*squareSideLength); 
    delay(1000);
    drawVerticalLine(4250*squareSideLength); 
    delay(1000);
    drawHorizontalLine(-235*squareSideLength);
    delay(1000);
    drawVerticalLine(-4250*squareSideLength);
    delay(1000);
}
*/

/*

// Check if tape (Y-axis) has done one full rotation
void checkTapeRotation() {
    currentPositionY = motorY.getStepper().currentPosition(); // Track Y-axis position
    Serial.print("Current position Y: ");
    Serial.println(currentPositionY);
    
    // Check if a full rotation is completed
    if (abs(currentPositionY) >= stepsFullRotationY) {
        rotations++;
        Serial.print("Tape motor completed 1 full rotation. Total rotations: ");
        Serial.println(rotations);
        
        // Reset the Y-axis position tracker
        motorY.getStepper().setCurrentPosition(0); // Reset position for next rotation
        currentPositionY = 0;
        
        // Lift the home position of X by 1 cm (4250 steps)
        HOME_POSITION += X_per_cm;
        Serial.print("New home position: ");
        Serial.println(HOME_POSITION);
        
        // Move the X-axis to the new home position
        motorX.moveTo(HOME_POSITION); 
        motorX.getStepper().runToPosition(); // Block until motor reaches the target
        Serial.println("Moved X-axis to new home position.");
    }
}

// Check if motor has reached the home position or the max position
void checkHoming() {
    // Get the current position of the motor
    currentPositionX = motorX.getStepper().currentPosition();
    
    // If at max position (27600 steps), perform homing
    if (currentPositionX >= MAX_POSITION) {
        Serial.println("Max position reached, performing homing...");
        homing();  // Perform homing when max position is reached
    }
    // If at min position (0), perform homing
    else if (currentPositionX <= 0) {
        Serial.println("Min position reached, performing homing...");
        homing();  // Perform homing when min position is reached
    }
}

void homing() {
    Serial.println("Homing: Moving stepper motors to home position...");

    if (currentPositionX >= MAX_POSITION) {
        motorX.moveTo(MAX_POSITION - 10625);  // Move to 18200 steps (27600 - 9700)
        motorX.getStepper().runToPosition();  // Block until the motor reaches the target
        Serial.println("At max position (27600), moving to home position.");
    } else if (currentPositionX == 0) {
        motorX.moveTo(HOME_POSITION);  // Move to 9500 steps forward from point 0
        motorX.getStepper().runToPosition();  // Block until the motor reaches the target
        Serial.println("At min position (0), moving to home position.");
    }

    currentPositionX = motorX.getStepper().currentPosition();  // Update current position
    Serial.println("Motor X reached home position.");
}


void penControl(bool down) {  
    penServo.write(down ? PEN_DOWN_ANGLE : PEN_UP_ANGLE);
}


// test the rotation of the motor
void testMotor(Motor &motor, int steps) {
    Serial.println("Testing motor  forward and backward...");
    motor.moveSteps(steps);  
    while (motor.getStepper().isRunning()) {
        motor.run();  
    }
    delay(500);  

    motor.moveSteps(-steps); 
    while (motor.getStepper().isRunning()) {
        motor.run(); 
    }
    delay(500); 

}
*/
