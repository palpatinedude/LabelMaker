
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
        String receivedSymbol = Serial.readStringUntil('\n'); 
        writeSymbol(receivedSymbol, stepperX, stepperY, pen);
    }
}