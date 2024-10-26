
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "label.h"  // Include your custom library

//  stepper motor connections and motor interface type
#define STEP_PIN_X 32  
#define DIR_PIN_X 33   
#define STEP_PIN_Y 25  
#define DIR_PIN_Y 26   
#define SERVO_PIN 27   

// stepper motor objects
AccelStepper stepperX(AccelStepper::DRIVER, STEP_PIN_X, DIR_PIN_X);
AccelStepper stepperY(AccelStepper::DRIVER, STEP_PIN_Y, DIR_PIN_Y);
Servo pen;

void setup() {
    Serial.begin(115200);
    
    // Initialize motors
    stepperX.setMaxSpeed(1000);
    stepperY.setMaxSpeed(1000);
    
    // Initialize the drawing setup
    initDrawing(stepperX, stepperY, pen);
}

void loop() {
    // Placeholder for your main loop
    if (Serial.available()) {
        String receivedSymbol = Serial.readStringUntil('\n'); // Read until newline
        writeSymbol(receivedSymbol, stepperX, stepperY, pen);
    }
}