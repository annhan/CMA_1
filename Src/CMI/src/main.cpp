#include <Arduino.h>
#include "main.h"
WifiConf::Config_t WifiDataconfig;
uint16_t lenghtEP = 1024;
WifiConf WifiConfn(WifiDataconfig);
char fff = 'f';
struct dataSave dataSave;


//typedef Config<WifiConf::Config_t> ConfigFormat;
void setup() {
 //SaveConfig.LoadFlash(100,WifiDataconfig);
 dataSave._loadFlash(100,WifiDataconfig);
  //_saveFlash(100,WifiDataconfig);
}

void loop() {
  // put your main code here, to run repeatedly:
}