/*
#include <Arduino.h>
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"
#include "motor.h"
#include "symbols.h"


// Motors instances to control tape and pen
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);  // Motor Y instance
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);  // Motor X instance
Servo penServo;  // Servo instance for pen control
// Pin definitions for the 4 switches


void setup() {
  Serial.begin(115200); // Start the serial monitor
 setupPins(motorX, motorY, penServo);  // Setup pins for motors and servo
 setMotorParameters(motorX, 3000, 500);
 setMotorParameters(motorY, 3000, 2000);
  // Trigger homing automatically without needing a button press
  // homing();

}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {  // If the button is pressed (LOW), stop the motor
         testMotor(motorY, 3000);  // Test motor X
     }
      delay(3000); // Small delay to debounce the switches
  }
 */

/*

void setup() {
   Serial.begin(115200);
   setupPins(motorX, motorY, penServo);  // Setup pins for motors and servo
}

void loop() {
   // int state = digitalRead(BUTTON_PIN);  // Read the state of the button
  //  if (state == LOW) {  // The pin goes LOW when the switch is pressed
     //  motorY.getStepper().stop();  // Stop the motor
    //}else{
        motorY.moveSteps(1000);  // Move forward by 100 steps
        motorY.run();  
  //}
  delay(500); // Check every 500 milliseconds
}

*/