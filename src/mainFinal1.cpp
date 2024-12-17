
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"   // custom library
#include "draw.h"  // custom library
#include "motor.h" // custom library
#include "init.h"  // custom library
#include "movement.h" // custom library
#include <Arduino.h>


// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control  
Servo penServo;

// initialize current position of the motor
// Global variable definitions
int currentPositionX = 0;  // Current position of X-axis
int currentPositionY = 0; // Current position of Y-axis
int rotations = 0;        // Number of tape rotations completed
int HOME_POSITION = 4250; // Initial home position for X-axis (can increase by 4250 steps after each tape rotation)


void setup() {
    Serial.begin(115200); 
    Serial.println("Starting setup...");
    initialization();
    Serial.println("Setup complete.");
}

void loop() {

    checkHoming();
    checkTapeRotation();
    drawLetter('A');
    delay(2000);
   
}

//  ----------------- DEFINED FUNCTIONS -----------------
