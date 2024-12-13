/*

#include <AccelStepper.h>
#include <ESP32Servo.h>
#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>
#include "motor.h"
#include "pins.h"  
#include "symbols.h" 

// motors instances to control tape and pen
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);  // Motor X instance
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);  // Motor Y instance
Servo penServo;  // Servo instance for pen control

/*
// server instance to handle web requests
AsyncWebServer server(80);
const char* ssid = "Rob2";          
const char* password = "F2524-fh";  
void setupWiFiAndServer();
void recvMsg(uint8_t *data, size_t len);
*/
/*
void setup() {
    Serial.begin(115200);  
    Serial.println("Starting setup...");

    setupPins(motorX, motorY, penServo);  
    setMotorParameters(motorX, 3000, 500); 
    setMotorParameters(motorY, 3000, 2000); 
 
    //setupWiFiAndServer();

    Serial.println("Setup complete. ");
    delay(2000);  
}

void loop() {
 //  drawSquare(500);  
  // delay(2000); 

 // drawHorizontalLine(400);
 // delay(500);
 
  //drawVerticalLine(4000);
  //delay(500);

/* 
  drawHorizontalLine(-500);
  delay(500);
  drawVerticalLine(2000);
  delay(2000);
 */


/*

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println("Received: " + d);
}


void setupWiFiAndServer() {
    Serial.println("Setting up Wi-Fi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    int retryCount = 0;
    while (WiFi.status() != WL_CONNECTED) {
        retryCount++;
        Serial.println("Wi-Fi failed, retrying...");
        delay(5000);  // Retry every 5 seconds
        Serial.print("Wi-Fi Status: ");
        Serial.println(WiFi.status());  // Print status code to debug
        
        if (retryCount > 10) {  // Retry up to 10 times
            Serial.println("Wi-Fi connection failed after several attempts. Check your credentials.");
            return;
        }
    }
    Serial.print("Wi-Fi connected! IP Address: ");
    Serial.println(WiFi.localIP());
    
    // Initialize WebSerial
    WebSerial.begin(&server);
    WebSerial.onMessage(recvMsg);
    server.begin();
    Serial.println("WebServer started.");
}
*/

