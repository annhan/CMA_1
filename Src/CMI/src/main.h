#ifndef __CMA_MAIN_H
#define __CMA_MAIN_H
#pragma once
#include <Arduino.h>
#include "pins_arduino.h"

extern "C" {
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

#include <SPIFFS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncMqttClient.h>
//#include "webserver.h"
#include "wifiSetting.h"
#include "SaveFlash.h"

//class SaveEpromStruct;
class WifiConf;

#endif





