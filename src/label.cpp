// moveTo() --> target position
// runToPosition() --> block operation
// write() --> set angle of servo

#include "label.h"

// initialize the drawing function with motors and servo
void initDrawing(AccelStepper& stepperX, AccelStepper& stepperY, Servo& pen) {
    stepperX.setCurrentPosition(0);
    stepperY.setCurrentPosition(0);
    pen.attach(SERVO_PIN); 
    pen.write(90); // raise pen

    pinMode(SWITCH_PIN, OUTPUT);
    digitalWrite(SWITCH_PIN, HIGH);
}

void drawA(AccelStepper& stepperX, AccelStepper& stepperY, Servo& pen) {
    pen.write(0); // pen down 
    delay(1000); // stabilize

    stepperY.moveTo(100 * STEPS_PER_MM_Y); // move up 
    stepperX.moveTo(-50 * STEPS_PER_MM_X); // move left 
    stepperX.runToPosition(); 
    stepperY.runToPosition(); 

    delay(500); // pause

    stepperY.moveTo(0); // back down
    stepperX.moveTo(50 * STEPS_PER_MM_X); // right
    stepperX.runToPosition(); 
    stepperY.runToPosition(); 

    delay(500); // Short pause

    // crossbar 'A'
    stepperX.moveTo(0); // back to center
    stepperY.moveTo(50 * STEPS_PER_MM_Y); // down for crossbar
    stepperX.runToPosition(); // 
    stepperY.runToPosition(); // 

    delay(1000); // wait

    pen.write(90); // pen up 
    delay(1000); // stabilize
}


// choose which symbol to draw
void writeSymbol(String symbol, AccelStepper& stepperX, AccelStepper& stepperY, Servo& pen) {
    if (symbol == "A") {
        drawA(stepperX, stepperY, pen);
    } 
}

// turn off the switch pin
void turnOffSwitch(AccelStepper& stepperX, AccelStepper& stepperY) {
    digitalWrite(SWITCH_PIN, LOW); 
    stepperX.stop(); 
    stepperY.stop(); 
}