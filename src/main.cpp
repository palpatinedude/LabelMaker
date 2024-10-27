
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "label.h"   // custom library


// stepper motor objects
AccelStepper stepperX(AccelStepper::DRIVER, STEP_PIN_X, DIR_PIN_X);
AccelStepper stepperY(AccelStepper::DRIVER, STEP_PIN_Y, DIR_PIN_Y);
Servo pen;

String receivedSymbol = "";

void setup() {
    Serial.begin(9600);
    initDrawing(stepperX, stepperY, pen);
}

void loop() {
    if (Serial.available()) {
        String receivedCommand = Serial.readStringUntil('\n'); 

        if (receivedCommand == "off") {
            // reset motors to initial position
            stepperX.setCurrentPosition(0);
            stepperY.setCurrentPosition(0);
            pen.write(90); // raise pen

            turnOffSwitch(stepperX, stepperY);
            
        

        } else {
            writeSymbol(receivedCommand, stepperX, stepperY, pen);
        }
    }
}
