/*

#include <Arduino.h>
#include <ESP32Servo.h>
#include <AccelStepper.h>
#include "motor.h"

#define PEN_PIN 13
#define X_STEP_PIN 26
#define X_EN_PIN 12  
#define X_DIR_PIN 25
#define Y_STEP_PIN 22
#define Y_DIR_PIN 23
#define Y_EN_PIN 33  

// Motor instances
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);
Servo penServo;

// Movement parameters


const float X_DISTANCE_PER_STEP = 0.01178;  // mm per step for X-axis (12mm pulley, 1/16 microstepping)
const float Y_DISTANCE_PER_STEP = 0.07265;  // mm per step for Y-axis (74mm tape roller, 1/16 microstepping)

//const float X_DISTANCE_PER_STEP = 0.0108;  // mm per step for X
//const float Y_DISTANCE_PER_STEP = 0.08246; // mm per step for Y

// Function declarations
void moveSteppers(int x_steps, int y_steps);
void stepMotor(int stepPin);    
void drawHorizontalLine(int lineLength);
void drawVerticalLine(int lineLength);
void penControl(bool down);
void setupPins(Motor &motorX, Motor &motorY, Servo &penServo);
void setMotorParameters(Motor &motor, int speed, int acceleration);

void setup() {
  // Configure stepper pins as output
  pinMode(X_STEP_PIN, OUTPUT);
  pinMode(X_DIR_PIN, OUTPUT);
  
  pinMode(Y_STEP_PIN, OUTPUT);
  pinMode(Y_DIR_PIN, OUTPUT);

  setupPins(motorX, motorY, penServo);  
  setMotorParameters(motorX, 4000, 3000); 
  setMotorParameters(motorY, 3000, 2000); 
  
  // Set default direction (1 = forward, 0 = backward)
  digitalWrite(X_DIR_PIN, HIGH); // Move forward
  digitalWrite(Y_DIR_PIN, HIGH); // Move forward

  // Initialize the servo
  penServo.attach(PEN_PIN);
  penServo.write(190); // Raise the pen
  Serial.begin(115200);
  Serial.println("Setup complete.");
  delay(2000); // Small delay before the process starts
}

void loop() {
  drawHorizontalLine(50); // Draw horizontal line of 50mm
  delay(1000); // Wait for 1 second
  
  drawVerticalLine(50); // Draw vertical line of 50mm
  delay(1000); // Wait for 1 second
  
  while (true); // Stop after drawing
}

// Function to draw a horizontal line (along Y-axis)
void drawHorizontalLine(int lineLength) {
  Serial.println("Starting horizontal line..."); 
  penControl(true); // Lower the pen
  
  delay(1000); // Wait for the pen to go down
  
  int y_steps = round(lineLength / Y_DISTANCE_PER_STEP);  // Calculate Y-axis steps for the line
  moveSteppers(0, y_steps); // Move Y-axis only
  
  penControl(false); // Raise the pen
  Serial.println("Horizontal line complete.");
}

// Function to draw a vertical line (along X-axis)
void drawVerticalLine(int lineLength) {
  Serial.println("Starting vertical line..."); 
  penControl(true); // Lower the pen
  
  delay(1000); // Wait for the pen to go down
  
  int x_steps = round(lineLength / X_DISTANCE_PER_STEP);  // Calculate X-axis steps for the line
  moveSteppers(x_steps, 0); // Move X-axis only
  
  penControl(false); // Raise the pen
  Serial.println("Vertical line complete.");
}
void setupPins(Motor &motorX,Motor &motorY,Servo &penServo) {

    Serial.println("Setting up pins...");
    pinMode(PEN_PIN, OUTPUT);            
  
    motorX.enableMotor(true);  
    motorY.enableMotor(true);  
    
   // motorX.moveTo(0);
    penServo.attach(PEN_PIN); 

    penControl(true);  
    Serial.println("Pins setup complete.");
  
}

// set speed and acceleration parameters
void setMotorParameters(Motor &motor, int speed, int acceleration) {
    Serial.println("Setting motor parameters...");
    motor.setSpeed(speed);
    motor.setAcceleration(acceleration);
    Serial.println("Motor parameters set.");
}



// Function to raise or lower the pen
void penControl(bool down) {  
  if (down) {
    Serial.println("Pen down");
    penServo.write(100); // Lower the pen
  } else {
    Serial.println("Pen up");
    penServo.write(190); // Raise the pen
  }
}

// Function to move both steppers
void moveSteppers(int x_steps, int y_steps) {
  int x_counter = 0;  
  int y_counter = 0;  

  int total_steps = max(abs(x_steps), abs(y_steps)); 
  float x_interval = (x_steps != 0) ? (float)total_steps / abs(x_steps) : total_steps + 1; 
  float y_interval = (y_steps != 0) ? (float)total_steps / abs(y_steps) : total_steps + 1; 

  for (int i = 0; i < total_steps; i++) {
    if (i % (int)x_interval == 0 && x_counter < abs(x_steps)) {
      stepMotor(X_STEP_PIN); 
      x_counter++;
    }

    if (i % (int)y_interval == 0 && y_counter < abs(y_steps)) {
      stepMotor(Y_STEP_PIN); 
      y_counter++;
    }

    delayMicroseconds(500); // Speed control
  }
}

// Function to step a motor
void stepMotor(int stepPin) {
  digitalWrite(stepPin, HIGH);
  delayMicroseconds(10); // Pulse width
  digitalWrite(stepPin, LOW);
}
*/