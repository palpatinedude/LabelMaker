#ifndef __NETWORK__
#define __NETWORK__

#include <Arduino.h>
#include "WiFi.h"
#include <string.h>
#include <WiFiUdp.h>
#include <vector>
#include "dataManager.h"
#include "dummyHardware.h"



enum NET_STATES
{
    BEGIN,  //Waiting for connect signal from client
    CONNECT, //Setting the client ip for communication
    TEST,   //Testing the connection
    IDLE,    //Connected and waiting for commands
    DATA_IN,    //Recieving data
    RUN
};


class Connection
{
private:
    char _ssid[20];
    char _passw[30];
    int _port;
    const char *_name = "Label Maker";
    WiFiUDP _udp;
    IPAddress _clientIp;
    char packetBuffer[256];
    NET_STATES _state;
    DataManager _data;
    unsigned int _updateTime;
    unsigned int _timeNow;
    void fsm();


public:
    Connection();
    Connection(char *ssid, char *passwm, int port);
    void init();
    void monitor();
    int readPacket();
    void writePacket(const char *replyBuffer);
    NET_STATES getState();
    void setUpdateTime(unsigned int milliseconds);
    void sendData();
    int timer();
};

#endif