#ifndef label.h
#define label.h

// libraries
#include <AccelStepper.h>
#include <ESP32Servo.h>

// stepper ,servo,switch pins
#define STEP_PIN_X 32  
#define DIR_PIN_X 33   
#define STEP_PIN_Y 25  
#define DIR_PIN_Y 26   
#define SERVO_PIN 27   
#define SWITCH_PIN 14 


// function prototypes
void initDrawing(AccelStepper& stepperX, AccelStepper& stepperY, Servo& pen);
void drawA(AccelStepper& stepperX, AccelStepper& stepperY, Servo& pen);
void writeSymbol(String symbol, AccelStepper& stepperX, AccelStepper& stepperY, Servo& pen);
void turnOffSwitch(AccelStepper& stepperX, AccelStepper& stepperY) 

#endif


