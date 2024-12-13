// moveTo() --> target position
// runToPosition() --> block operation
// write() --> set angle of servo
// 4700 steps approximately  1 cm stepper X
// 235 steps approximately 1 cm stepper Y
// reference point 0 where the button is pressed

#include <Arduino.h>
#include "../include/motor.h"
#include "../include/pins.h"
#include "../include/symbols.h"


// ######################## FUNCTIONS DEFINITIONS ########################
/*
void homing() {
    Serial.println("Homing: Moving stepper motor X to home position...");
    penControl(true);  // Lower the pen (if necessary)

    // Slow down the motor for precise homing
    motorX.enableMotor(true);  // Enable motor
    motorX.setSpeed(800);  // Slow speed for accurate homing
    motorX.setAcceleration(400);  // Slow acceleration for smooth approach
  

    // Move the motor in the negative direction towards home
    motorX.moveSteps(-100000);  // Move a large number of steps to ensure it reaches the home position

    while (true) {
        motorX.run();  // Continuously run the motor
        if (digitalRead(BUTTON_PIN) == LOW) {  // If the button is pressed (LOW), stop the motor
            motorX.getStepper().stop();  // Immediately stop the motor
            motorX.getStepper().setCurrentPosition(0);  // Set the current position as 0 (home)
            break;  // Exit the loop
        }
    }

    Serial.println("X Motor homing complete. Current position set to 0.");
}
void homing() {
   // motorX.moveSteps(HOME_POSITION);  
    
    motorX.moveTo(HOME_POSITION);
    //while (motorX.getStepper().isRunning()) {
      //  motorX.run();  
    //}
    Serial.println("Motor reached home position (9200 steps from reference point).");
}

void homing() {
    Serial.println("Homing: Moving stepper motor X to home position...");

    // Check if the motor has reached max position (27600 steps from 0)
    if (currentPosition >= MAX_POSITION) {
        // If at max position, home at 8400 steps from the max position
        motorX.moveTo(MAX_POSITION - HOME_POSITION);  // Move 8400 steps from max position
        Serial.println("At max position, moving to home position 8400 steps from max.");
    } else {
        // Otherwise, home at 9200 steps from reference point (0)
        motorX.moveTo(HOME_POSITION);  // Move 9200 steps from 0
        Serial.println("Moving to home position 9200 steps from reference point.");
    }

    // Wait for the motor to reach the home position
    while (motorX.getStepper().isRunning()) {
        motorX.run();  // Continuously run the motor until it reaches the target
    }

    currentPosition = motorX.getStepper().currentPosition();  // Update current position
    Serial.println("Motor reached home position.");
}

void homing() {
    Serial.println("Homing: Moving stepper motor X to home position...");

    if (currentPosition == 0) {
        // If the current position is 0 (reference point)
        motorX.moveTo(HOME_POSITION);  // Move to 9200 steps (home position from reference point)
        Serial.println("At reference point (0), moving 9200 steps to home position.");
    }
    else if (currentPosition >= MAX_POSITION) {
        // If the current position is the max position (27600 steps from reference point)
        motorX.moveTo(currentPosition - 9200);  // Move 18400 steps back to home position
        Serial.println("At max position (27600), moving 18400 steps back to home position.");
    }

   // motorX.runToPosition();  // Block and wait until the motor reaches the home position

    currentPosition = motorX.getStepper().currentPosition();  // Update the current position
    Serial.println("Motor reached home position.");
}
*/
void homing() {
    Serial.println("Homing: Moving stepper motor X to home position...");

    if (currentPosition == 0) {
        // If the current position is 0 (reference point)
        motorX.moveTo(HOME_POSITION);  // Move 9200 steps from reference point (0)
        Serial.println("At reference point (0), moving 9200 steps to home position.");
    } 
    else if (currentPosition >= MAX_POSITION) {
        // If the current position is at or past the max position (27600 steps from reference point)
        motorX.moveTo(currentPosition - 18400);  // Move 18400 steps back to home position
        Serial.println("At max position (27600), moving 18400 steps back to home position.");
    }

    // Wait for the motor to reach the home position
  //  while (motorX.getStepper().isRunning()) {
        motorX.run();  
    //}

    currentPosition = motorX.getStepper().currentPosition();  // Update the current position
    Serial.println("Motor reached home position.");
}
void penControl(bool down) {  
    if (down) {
        penServo.write(180);  // further the tape true
    } else {
        penServo.write(120);   // close to tape false
    }
}

void setupPins(Motor &motorX,Motor &motorY,Servo &penServo) {

    Serial.println("Setting up pins...");
    pinMode(BUTTON_PIN, INPUT);   
    pinMode(PEN_PIN, OUTPUT);            
  
    motorX.enableMotor(true);  
    motorY.enableMotor(true);  
    
   // motorX.moveTo(0);
    penServo.attach(PEN_PIN); 

    penControl(true);  
    Serial.println("Pins setup complete.");
  
}

void initialization(){
    penControl(true); 
    while (digitalRead(BUTTON_PIN) == HIGH) {
        motorX.moveSteps(-3000);
        motorX.run();
    }
    motorX.stop(); // Stop motor after pressing the buttoSSn
    currentPosition = 0; // Update current position
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
    }

    penControl(true);  
    Serial.println("Vertical line complete.");
}



void drawSquare(int squareSideLength) {
    // four sides of the square

    drawHorizontalLine(235*squareSideLength); // for 2 cm
    delay(1000);
    drawVerticalLine(4700*squareSideLength); // for 2 cm
    delay(1000);
    drawHorizontalLine(-235*squareSideLength); // for 2 cm
    delay(1000);
    drawVerticalLine(-4700*squareSideLength); // for 2 cm
    delay(1000);
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


/*
void homeMotors() {
    motorX.moveTo(0);
    motorY.moveTo(0);
    motorX.runToPosition();
    motorY.runToPosition();
    Serial.println("Motors homed.");
}
*/