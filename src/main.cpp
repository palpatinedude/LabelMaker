#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "../lib/header.h"   // custom library


// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control  
Servo penServo;




void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    // Initialize pins
    setupPins();
}


void loop(){
     if (Serial.available()) {
        char letter = Serial.read();  // Read letter from serial input
        if (letter >= 'A' && letter <= 'Z') {
            drawLetter(letter);  // Draw the letter
        }
    }
}

