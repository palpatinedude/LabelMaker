#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"   // custom library
#include "symbols.h"  // custom library
#include "BluetoothSerial.h"
 
BluetoothSerial SerialBT;

// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control  
Servo penServo;




void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    // Initialize pins
    setupPins();
    SerialBT.begin("LabelMaker"); // Set device name
    Serial.println("Bluetooth device is ready to pair");
}


void loop(){
     if (SerialBT.available()) {
        String received = SerialBT.readString();
        char letter = received[0];
        // char letter = Serial.read();  // Read letter from serial input
        if (letter >= 'A' && letter <= 'Z') {
            drawLetter(letter);  // Draw the letter
            Serial.println(letter);
        }
    }
}


