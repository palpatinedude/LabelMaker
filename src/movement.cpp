#include "movement.h"
#include "motor.h"
#include "pins.h"
#include <Arduino.h>



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