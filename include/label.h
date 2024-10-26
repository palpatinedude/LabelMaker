#ifndef label.h
#define label.h

#include <AccelStepper.h>
#include <ESP32Servo.h>

void initDrawing(AccelStepper& stepperX, AccelStepper& stepperY, Servo& penServo);
void drawA(AccelStepper& stepperX, AccelStepper& stepperY, Servo& penServo);
void writeSymbol(String symbol, AccelStepper& stepperX, AccelStepper& stepperY, Servo& penServo);

#endif


