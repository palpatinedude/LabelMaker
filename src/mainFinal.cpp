
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"   // custom library
#include "symbols.h"  // custom library
#include "motor.h" // custom library
#include <Arduino.h>


// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control  
Servo penServo;

// initialize current position of the motor
int currentPosition = 0;

void setup() {
    Serial.begin(115200); 
    Serial.println("Starting setup...");
    setupPins(motorX,motorY,penServo);  
    setMotorParameters(motorX, 2000, 1000); 
    setMotorParameters(motorY, 3000, 2000);  
    initialization();
    homing();
    Serial.println("Setup complete.");
}

void loop(){
     if (digitalRead(BUTTON_PIN) == LOW || currentPosition >= MAX_POSITION) {
        homing();  
    }
    drawHorizontalLine(470); // for 2 cm
    delay(1000);
    drawVerticalLine(9400); // for 2 cm
    delay(1000);
    drawHorizontalLine(-470); // for 2 cm
    delay(1000);
    drawVerticalLine(-9400); // for 2 cm
}

//  ----------------- DEFINED FUNCTIONS -----------------
