#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"   // custom library
#include "symbols.h"  // custom library
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control  
Servo penServo;

AsyncWebServer server(80);

const char* ssid = "Rob2";          // Your WiFi SSID
const char* password = "F2524-fh";  // Your WiFi Password

void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println(d);
}

void setup() {
    // Initialize serial communication
    Serial.begin(115200);
    // Initialize pins
    setupPins();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.printf("WiFi Failed!\n");
        return;
    }
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
    // WebSerial is accessible at "<IP Address>/webserial" in browser
    WebSerial.begin(&server);
    WebSerial.onMessage(recvMsg);
    server.begin();
}

void loop(){
    WebSerial.println("Hello!");
    delay(200);
    // char received = Serial.readString();
    // char letter = received[0];
    // // char letter = Serial.read();  // Read letter from serial input
    // if (letter >= 'A' && letter <= 'Z') {
    // drawLetter(letter);  // Draw the letter
    // Serial.println(letter);
    // }
}



