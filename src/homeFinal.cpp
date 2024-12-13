#include <AccelStepper.h>
#include <ESP32Servo.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include "motor.h"
#include "pins.h"
#include "symbols.h"

// Motors instances to control tape and pen
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);  // Motor X instance
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);  // Motor Y instance
Servo penServo;  // Servo instance for pen control 

int currentPosition = 0;


void setup() {
    Serial.begin(115200);  // Start serial communication
    setupPins(motorX, motorY, penServo);  // Setup pins for motors and servo
    setMotorParameters(motorX, 3000, 500); 
    setMotorParameters(motorY, 3000, 2000); 
    initialization();
    homing();   
    
 
}

void loop() {
    // Trigger homing whenever the button is pressed or motor reaches max position
    if (digitalRead(BUTTON_PIN) == LOW || currentPosition >= MAX_POSITION) {
        homing();  
    }

    // Example action: Move motor by some steps (for testing)
    int stepsToMove = 5000; // Number of steps to move forward
    motorX.moveSteps(stepsToMove);  // Move motor by 'stepsToMove' 
    motorX.getStepper().runToPosition();  // Wait until the motor reaches the target position
    currentPosition += stepsToMove;  // Update current position relative to reference point (0)
    Serial.print("Current Position: ");
    Serial.println(currentPosition);  // Print current position
    delay(1000);  // Delay for 1 second
}

