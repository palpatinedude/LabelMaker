#ifndef label.h
#define label.h

// libraries
#include <AccelStepper.h>
#include <ESP32Servo.h>

// stepper motor connections and motor interface type
#define STEP_PIN_X 32  
#define DIR_PIN_X 33   
#define STEP_PIN_Y 25  
#define DIR_PIN_Y 26   
#define SERVO_PIN 27   

void initDrawing(AccelStepper& stepperX, AccelStepper& stepperY, Servo& penServo);
void drawA(AccelStepper& stepperX, AccelStepper& stepperY, Servo& penServo);
void writeSymbol(String symbol, AccelStepper& stepperX, AccelStepper& stepperY, Servo& penServo);

#endif


