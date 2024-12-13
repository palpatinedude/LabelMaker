
/*
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"   // custom library
#include "symbols.h"  // custom library

// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control  
Servo penServo;

void setup() {
    Serial.begin(115200);  // Initialize serial communication
    Serial.println("Starting setup...");

    setupPins();  // Initialize motor pins (from custom pins.h)
    Serial.println("Setup Complete.");

}

void loop() {
    Serial.println("Starting Servo Test...");

    Serial.println("Moving Servo to up position...");
    penServo.write(0);  
    delay(2000);  

    Serial.println("Moving Servo to down position...");
    penServo.write(90);  
    delay(2000); 

    // Optionally, move to another angle to test further range
    Serial.println("Moving Servo to another position...");
    penServo.write(180);  // Move the pen to "down" position (180 degrees)
    delay(2000);  // Wait for 2 seconds

     // Test moving the servo to "up" position (away from the tape)
    Serial.println("Moving Servo to up position...");
    penServo.write(0);  // Move the pen to "up" position (0 degrees)
    delay(2000);  // Wait for 2 seconds

   //testTapeRotation();
}
*/
/*

#include <Arduino.h>
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

void setup() {
    Serial.begin(115200);  // initialize serial communication
    Serial.println("Starting setup...");
    setupPins();  // initialize pins
    setupWiFiAndServer(); 
    Serial.println("Setup Complete.");
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

*/

/*
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

const char* ssid = "Rob2";          // Your WiFi SSID (will be used later)
const char* password = "F2524-fh";  // Your WiFi Password (will be used later)

AsyncWebServer server(80);  // HTTP server runs on port 80

void listAvailableWiFi() {
  Serial.println("Scanning for available Wi-Fi networks...");

  // Scan for Wi-Fi networks
  int numNetworks = WiFi.scanNetworks();
  if (numNetworks == 0) {
    Serial.println("No networks found.");
  } else {
    Serial.print(numNetworks);
    Serial.println(" networks found:");
    
    for (int i = 0; i < numNetworks; i++) {
      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));  // Print SSID
      Serial.print(" (Signal Strength: ");
      Serial.print(WiFi.RSSI(i));  // Print signal strength
      Serial.println(" dBm)");
      delay(10);
    }
  }

  // Clear the network list after scanning
  WiFi.scanDelete();
}

void setupWiFi() {
  Serial.println("Connecting to WiFi...");

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  int retryCount = 0;
  
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    retryCount++;
    Serial.print(".");
    delay(1000);  // Retry every 1 second

    // Print status code for debugging
    Serial.print("Wi-Fi status: ");
    Serial.println(WiFi.status());  // Print the status code to debug

    if (retryCount > 20) {  // Retry up to 20 times
      Serial.println("WiFi connection failed.");
      return;
    }
  }

  // Print the IP address once connected
  Serial.print("WiFi connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  // Start the serial communication for debugging
  Serial.begin(115200);

  // Scan for available networks and print them
  listAvailableWiFi();

  // Connect to WiFi using the provided credentials
  setupWiFi();

  // Serve a basic web page when accessing the root URL ("/")
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello, this is the ESP32 Web Server!");
  });

  // Start the web server
  server.begin();
  Serial.println("Web server started.");
}

void loop() {
  // Nothing to do here
}
*/