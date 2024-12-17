#include "init.h"
#include "pins.h"
#include "motor.h"
#include "movement.h"
#include <ESP32Servo.h>

// Initialize motors and servo
void initialization() {
    Serial.println("Initialization started...");
    setupMotors(motorX, motorY);
    setupServo(penServo);
    setMotorParameters(motorX, 2000, 1000);
    setMotorParameters(motorY, 3000, 2000);
    firstHoming();
    homing();
    Serial.println("Initialization complete.");
}

void firstHoming(){
    penControl(true); 
    while (digitalRead(BUTTON_PIN) == HIGH) {
        motorX.moveSteps(-3000);
        motorX.run();
    }
    motorX.stop(); // Stop motor after pressing the buttoSSn
    currentPositionX = 0; // Update current position
    motorX.getStepper().setCurrentPosition(0);  // Update current position
}

// setup stepper motors configurations
void setupMotors(Motor &motorX, Motor &motorY) {
    motorX.enableMotor(true);
    motorY.enableMotor(true);
    Serial.println("Motors setup complete.");
}

// setup servo for pen control
void setupServo(Servo &penServo) {
    penServo.attach(PEN_PIN);
    penControl(true);
    Serial.println("Servo setup complete.");
}

// set speed and acceleration parameters
void setMotorParameters(Motor &motor, int speed, int acceleration) {
    Serial.println("Setting motor parameters...");
    motor.setSpeed(speed);
    motor.setAcceleration(acceleration);
    Serial.println("Motor parameters set.");
}
