#pragma once

#ifndef __CMA_MAIN_H
#define __CMA_MAIN_H


#include <stdint.h>
#include "Arduino.h"
#include "pins_arduino.h"

extern "C" {
#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
}

#include <SPIFFS.h>
//#include "webserver.h"
#include "wifiSetting.h"
#include "./Lib/SaveFlash/SaveFlash.h"
WifiConf::Config_t Wifi_config;

WifiConf WifiConfn(WifiConf::Config_t Wifi_config);
#endif





