/*
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

void setup() {
    setupPins(motorX, motorY, penServo);  // Setup pins for motors and servo
    setMotorParameters(motorX, 3000, 500); 
    setMotorParameters(motorY, 3000, 2000); 
    
 
}

void loop() {
    // Step 1: Move motor in negative steps until button is pressed
    while (digitalRead(BUTTON_PIN) == HIGH) {  // While the button is not pressed
        motorX.getStepper().move(-100);  // Move motorX one step in the negative direction
        motorX.getStepper().run();       // Run the motor
    }

    homing();  // Home the motor
}

void homing() {
    // Move motorX to the home position (negative direction until the button is pressed)
    while (digitalRead(BUTTON_PIN) == HIGH) {
        motorX.moveSteps(-100);
        motorX.run();
    }
    motorX.stop(); // Stop motor after pressing the button
    motorX.getStepper().setCurrentPosition(0); // Set home position

    
}
*/