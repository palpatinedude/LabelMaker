#include "network.h"


Connection::Connection()
{

}

Connection::Connection(char *ssid, char *passw, int port)
{
    strcpy(this->_ssid, ssid);
    strcpy(this->_passw, passw);
    this->_port = port;
    this->_state = NET_STATES::BEGIN;
    this->_data = DataManager();
    this->_updateTime = 50; //Default update time 50ms
    this->_timeNow = 0;
}

void Connection::init()
{
    WiFi.mode(WIFI_STA);
    WiFi.begin(this->_ssid, this->_passw);
    Serial.println("\nConnecting");

    while(WiFi.status() != WL_CONNECTED){
        Serial.print(".");
        delay(100);
    }
    this->_udp.begin(WiFi.localIP(), this->_port);

    Serial.println("\nConnected to the WiFi network");
    Serial.print("Local ESP32 IP: ");
    Serial.println(WiFi.localIP());
}

int Connection::readPacket()
{
    int packetSize = this->_udp.parsePacket();
    //If there is a udp packet available
    if(packetSize){
        // read the packet into packetBufffer
        int len = this->_udp.read(packetBuffer, 255);
        if (len > 0) {
        packetBuffer[len] = 0;
        }
        return 0; //Packet available
    }
    return 1; //Packet not available
}

void Connection::writePacket(const char *replyBuffer)
{ 
    this->_udp.beginPacket(this->_udp.remoteIP(), this->_udp.remotePort());
    int size = strlen(replyBuffer);
    for(int i = 0; i < size; i++){
        this->_udp.write(replyBuffer[i]);
    }
    this->_udp.endPacket();
}

void Connection::fsm()
{
    switch (this->_state)
    {
    case NET_STATES::BEGIN: //Set next state to connect or test
        Serial.println("BEGIN");    //DEBUG
        if(!strcmp(this->packetBuffer, "test")){
            this->_state = NET_STATES::TEST;
        }
        else if(!strcmp(this->packetBuffer, "connect")){
            this->_state = NET_STATES::CONNECT;
        }
        break;

    case NET_STATES::TEST: //Test connection. Dont set client ip yet
        Serial.println("TEST"); //DEBUG
        if(!strcmp(this->packetBuffer, this->_name)){ //Expecting to recieve the name of the device
            char replyBuffer[] = "confirm";
            writePacket(replyBuffer);
        }
        this->_state = NET_STATES::BEGIN;
        break;
    
    case NET_STATES::CONNECT:
        Serial.println("CONNECT");
        if(!strcmp(this->packetBuffer, this->_name)){ //Expecting to recieve the name of the device
            char replyBuffer[] = "confirm";
            writePacket(replyBuffer);
            this->_state = NET_STATES::IDLE;
            Serial.println("IDLE"); //DEBUG
            this->_clientIp = this->_udp.remoteIP(); //Seting the connected client's ip
        }else this->_state = NET_STATES::BEGIN;
        break;
    
    case NET_STATES::IDLE:  //On IDLE Start updating the client on values from hardware
        //Set RGB Led to green (Only for devkit)
        if(!strcmp(this->packetBuffer, "disconnect")){
            Serial.println("DISCONNECT");   //DEBUG
            this->_state = NET_STATES::BEGIN;
        }
        else if(!strcmp(this->packetBuffer, "DATA")){
            Serial.println("DATA");    //DEBUG
            this->_state = NET_STATES::DATA_IN;
            this->_data.clearData();
        }
        else if(!strcmp(this->packetBuffer, "RUN")){
            Serial.println("RUN");    //DEBUG
            this->_state = NET_STATES::RUN;
        }

        break;
    case NET_STATES::DATA_IN:
        if(!strcmp(this->packetBuffer, "END")){
            Serial.println("END");  //DEBUG
            this->_state = NET_STATES::IDLE;
        }
        else{
            
            //Parsing input and saving to data manager
            std::string s = this->packetBuffer;
            
            std::string delimiter = ",";
            std::vector<std::string> parsedInput;
            size_t pos = 0;
            std::string token;
            
            while ((pos = s.find(delimiter)) != std::string::npos) {
                token = s.substr(0, pos);
                parsedInput.push_back(token);
                s.erase(0, pos + delimiter.length());
            }
            parsedInput.push_back(s);
            
            if(!parsedInput.at(0).compare("vals")){
                int x = atoi(parsedInput.at(1).c_str());
                int y = atoi(parsedInput.at(2).c_str());
                int p = atoi(parsedInput.at(3).c_str());
                this->_data.appendData(x, y, p);

                //DEBUG
                printf("X: %d, Y: %d, P: %d\n", x, y, p);
            }
            
        }
        break;

    case NET_STATES::RUN:
        int size = this->_data.size();
        unsigned int startTime = millis();
        unsigned int currentTime;
        int valX;
        int valY;
        int dataSize = this->_data.size();
        int index = 0;
        while(index < size){
            valX = this->_data.getX(index);
            valY = this->_data.getY(index);
            currentTime = millis();
            if(currentTime - startTime >= valX){
                //Send rpm to motor control here
                index++;
                
                //Updating client on hardware state change
                if(timer()){
                    sendData();
                }
            }


        }
        this->_state = NET_STATES::IDLE;

    
        Serial.println("IDLE");  //DEBUG
        this->_state = NET_STATES::IDLE;
        break;

    //default:
        //break;
    }
}

void Connection::monitor()
{
    //NeoPixel.clear();
    if(!readPacket()){
        fsm();
    }
}

NET_STATES Connection::getState(){
    return this->_state;
}

void Connection::setUpdateTime(unsigned int milliseconds)
{
    this->_updateTime = milliseconds;
}


/**
 * @brief Send data from hardware to the client
 * 
 */
void Connection::sendData()
{
    char message[50];

    
    writePacket(message); //Send data with code:vals and delimiter ,
}

/**
 * @brief Returns 1 every set time interval
 * 
 * @return int 
 */
int Connection::timer()
{
    if(millis() >= this->_timeNow + this->_updateTime && getState() == NET_STATES::RUN){
        this->_timeNow += this->_updateTime;
        return 1;
    }
    else return 0;
}