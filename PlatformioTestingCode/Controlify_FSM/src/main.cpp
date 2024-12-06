#include <Arduino.h>
#include "cli.h"
#include "network.h"
#include "stdlib.h"
#include "string.h"
#include "stdio.h"


//#define _updateInterval 10 //ms

unsigned long time_now = 0;


Cli menu;
Connection server;

void setup() {
  menu = Cli(9600);
  menu.cli_init();
  server = Connection("George-WIFI", "6907005690", 2390);
  server.init();   
  server.setUpdateTime(10); 
}

void loop() {
    menu.runMenu();     //Run the cli 
    server.monitor();   //Monitor trafic and perform state changes

}
