/*
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
    // Initialize WiFi
    Serial.println("setting up wifi");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    
    // Wait for WiFi connection
    int retryCount = 0;
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        retryCount++;
        Serial.println("WiFi Failed, retrying...");
        delay(5000);  // Retry every 5 seconds
        if (retryCount > 5) {
            Serial.println("WiFi connection failed after several attempts. Check your credentials.");
            return;
        }
    }

    Serial.print("WiFi Connected! IP Address: ");
    Serial.println(WiFi.localIP());
    
    // initialize WebSerial
    WebSerial.begin(&server);
    WebSerial.onMessage(recvMsg);
    
    // web server route for drawing input
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
        String html = "<html><body><h1>Send a Letter to Draw</h1>";
        html += "<form action='/send' method='GET'>";
        html += "Letter: <input type='text' name='letter' maxlength='1'>";
        html += "<input type='submit' value='Send'>";
        html += "</form></body></html>";
        request->send(200, "text/html", html);
    });

    // handle letter submission and drawing
    server.on("/send", HTTP_GET, [](AsyncWebServerRequest *request){
        String letter = request->getParam("letter")->value();
        if (letter.length() == 1) {
            drawLetter(letter.charAt(0));  
            request->send(200, "text/html", "Drawing: " + letter);
        } else {
            request->send(200, "text/html", "Please enter a single letter.");
        }
    });

    server.begin();
    Serial.println("WebServer Started.");
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
#include <AccelStepper.h>
#include <ESP32Servo.h>
#include "pins.h"         
#include "symbols.h"       
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

// create motor instances for X and Y axes
Motor motorX(X_EN_PIN, X_STEP_PIN, X_DIR_PIN);
Motor motorY(Y_EN_PIN, Y_STEP_PIN, Y_DIR_PIN);

// create servo instance for pen control
Servo penServo;

// cretae web server instance
AsyncWebServer server(80);

// wifi credentials
const char* ssid = "Rob2";          
const char* password = "F2524-fh";  

#define STEPS_PER_REVOLUTION 500   // Number of steps per full rotation 
#define FULL_ROTATION_DELAY 500   // Delay in milliseconds for the motor to complete its movement


void calibrateTapeMotor() {
    Serial.println("Starting tape motor calibration...");

    // rotate motor by the number of steps in one full revolution
    motorX.moveSteps(STEPS_PER_REVOLUTION);  
    delay(FULL_ROTATION_DELAY);  // Wait for the motor to complete its movement

    Serial.println("Tape motor calibration complete.");
    WebSerial.println("Tape motor calibration complete.");
}



// function to handle incoming WebSerial messages
void recvMsg(uint8_t *data, size_t len) {
    WebSerial.println("received data...");
    String receivedData = "";
    for (int i = 0; i < len; i++) {
        receivedData += char(data[i]);
    }
    WebSerial.println("received: " + receivedData);

    // check if input is a valid single letter
    if (receivedData.length() == 1 && receivedData[0] >= 'A' && receivedData[0] <= 'Z') {
        char letter = receivedData[0];
        WebSerial.println("drawing letter: " + String(letter));
        drawLetter(letter);  // draw the letter
    } else {
        WebSerial.println("invalid input. please send a letter (A-Z).");
    }
/*
    if (receivedData == "Tape") {
        WebSerial.println("Testing tape motor rotation...");
        calibrateTapeMotor();  // call function to rotate tape motor
    } else {
        WebSerial.println("Invalid command. Please type 'Tape' to test the motor.");
    }
}
/*
// function to initialize Wi-Fi and WebSerial
void setupWiFiAndWebSerial() {
    Serial.println("setting up wifi...");
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
*/
/*
// function to initialize Wi-Fi and WebSerial
void setupWiFiAndWebSerial() {
    Serial.println("setting up wifi...");
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);

    // retry Wi-Fi connection if it fails
    int retryCount = 0;
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        retryCount++;
        Serial.println("wifi failed, retrying...");
        delay(5000);
        if (retryCount > 5) {  // stop retrying after 5 attempts
            Serial.println("wifi connection failed. check your credentials.");
            return;
        }
    }

    // print IP address on successful connection
    Serial.print("wifi connected! ip address: ");
    Serial.println(WiFi.localIP());

    // initialize WebSerial for debugging
    WebSerial.begin(&server);
    WebSerial.onMessage(recvMsg);

    // start the web server
    server.begin();
    Serial.println("webserial and server started.");
}
*/
/*
// arduino setup function
void setup() {
    Serial.begin(115200);  // initialize serial communication
    Serial.println("starting setup...");
    setupPins();           // initialize motor and control pins
    setupWiFiAndWebSerial(); 
    Serial.println("setup complete.");
}

// arduino loop function
void loop() {
    WebSerial.println("system is running. send a letter (A-Z) via WebSerial to draw.");
    delay(2000);  // periodically send a status message
}
*/

/*
void setupWiFiAndServer() {
    Serial.println("Setting up Wi-Fi...");
    WiFi.disconnect(true);  // Clear old connections
    WiFi.mode(WIFI_STA);    // Set as station mode
    
  WiFi.onEvent([](arduino_event_id_t event, arduino_event_info_t info) {  // Use correct event types
        if (event == ARDUINO_EVENT_WIFI_STA_DISCONNECTED) {
            Serial.println("[WiFi Event] Disconnected from Wi-Fi");

            // Accessing the disconnection reason correctly
            uint8_t reason = info.wifi_sta_disconnected.reason;
            Serial.print("Reason code: ");
            Serial.println(reason);  // Print the reason code (numeric value)
        }
    });


    WiFi.begin(ssid, password, 0, NULL, true); 

    unsigned long startAttemptTime = millis();
    const unsigned long timeout = 30000;  // 30 seconds

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
        Serial.print(".");
        delay(1000);
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("\nWi-Fi connected!");
        Serial.print("IP Address: ");
        Serial.println(WiFi.localIP());

        // Initialize WebSerial
        WebSerial.begin(&server);
        WebSerial.onMessage(recvMsg);
        server.begin();
        Serial.println("WebServer started.");
    } else {
        Serial.println("\nWi-Fi connection failed. Check credentials or router settings.");
    }
}


void recvMsg(uint8_t *data, size_t len){
  WebSerial.println("Received Data...");
  String d = "";
  for(int i=0; i < len; i++){
    d += char(data[i]);
  }
  WebSerial.println("Received: " + d);
}

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


*/