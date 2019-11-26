
extern "C" {
  #include "freertos/FreeRTOS.h"
  #include "freertos/timers.h"
}
#include <Arduino.h>
#include "FS.h"
#include <ModbusRTU.h>
#include "EEPROM.h"
#include <AsyncMqttClient.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <Update.h>
#include "config.h"
#include "define.h"
#include "cutf.h"

/*
 * cma2018LHP515
 */
 /*
  * Modbus 400 -> 500 infor cho Wifi 400-416 : Wifi Name
  * 417->424 Wifi IP
  * 
  * 
  * 
  * 
  * 
  */
#define REGN 0
#define SLAVE_ID 1

ModbusRTU mb;
AsyncWebServer server(4999);
WiFiClient espClient;
AsyncMqttClient mqttClient;
TimerHandle_t mqttReconnectTimer;
char hienthiutf[200];
char begini[] = "Phạn Am nhàn ố ồ ô á à ạ ê ế ề ệ í ì ị ấ ầ ư ự ụ ú ù";
wchar_t hienthiascii[150];
//char16_t output[100];
uint32_t sogui = 0;
int i = 0;
int scenes = 10;
long time_cho = 0;
long delay_ms = 0;
char idRfidmain[25];
void setup() {
  EEPROM.begin(2048);
  if(!SPIFFS.begin(true)){printf("An Error has occurred while mounting SPIFFS\n");}
  Serial.begin(115200);
  loadWiFiConf();
  WiFi.disconnect(true);
    wifi_connect(0,WIFI_STA,WiFiConf.sta_ssid,WiFiConf.sta_pwd,WiFiConf.ap_ssid); 
    wifi_staticip(WiFiConf.sta_ip,WiFiConf.sta_gateway,WiFiConf.sta_subnet);   
    WiFi.onEvent(WiFiEvent);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info){
        wifiOnDisconnect();
    }, WiFiEvent_t::SYSTEM_EVENT_STA_DISCONNECTED);
    WiFi.onEvent([](WiFiEvent_t event, WiFiEventInfo_t info){
        wifigotip();
    }, WiFiEvent_t::SYSTEM_EVENT_STA_GOT_IP);
  setupWiFiConf();
  server.begin();
  Serial2.begin(115200, SERIAL_8N1);
  mb.begin(&Serial2);
  mb.slave(SLAVE_ID);
  mb.addHreg(REGN, 0x0000, 450);
  scenes = 10;
  mb.Hreg(300, scenes);
  for (int j = 0 ; j < sizeof(WiFiConf.sta_ssid) ; j = j+2) {
    mb.Hreg(400 + j/2, (((uint16_t)WiFiConf.sta_ssid[j+1]<< 8 )|((uint16_t)WiFiConf.sta_ssid[j])));
    if ((WiFiConf.sta_ssid[j] == '\0')||(WiFiConf.sta_ssid[j + 1] == '\0')) break;
  }
  Queue_RFID= xQueueCreate(5,sizeof(idRfidmain));

 xTaskCreatePinnedToCore(
                        TaskRFID,   /* Function to implement the task */
                        "TaskRFID", /* Name of the task */
                        8192,      /* Stack size in words */
                        NULL,       /* Task input parameter */
                        15,          /* Priority of the task */
                        NULL,       /* Task handle. */
                        1);  /* Core where the task should run */
  mqttReconnectTimer = xTimerCreate("mqttTimer", pdMS_TO_TICKS(2000), pdFALSE, (void*)0, reinterpret_cast<TimerCallbackFunction_t>(connectToMqtt));
  mqttClient.onConnect(onMqttConnect);
  mqttClient.onDisconnect(onMqttDisconnect);
  mqttClient.onSubscribe(onMqttSubscribe);
  mqttClient.onUnsubscribe(onMqttUnsubscribe);
  mqttClient.onMessage(onMqttMessage);
  mqttClient.onPublish(onMqttPublish);
  mqttClient.setServer(WiFiConf.mqtt_server, atoi(WiFiConf.mqtt_port));       
  mqttClient.setCredentials(WiFiConf.mqtt_user,WiFiConf.mqtt_pass);  
}
long timeTaskDelay = 0;
void loop() {
  vTaskDelay(10);
  if (statusWifiConnect == false){
    if (intCounterWifi == 30){
      if (xTaskGetTickCount() - timeTaskDelay> 500){
        timeTaskDelay=xTaskGetTickCount();
        WiFi.disconnect(true);
        printf("Chuyen\n");
        wifi_connect(2, WIFI_AP_STA, WiFiConf.sta_ssid, WiFiConf.sta_pwd,(char *)"esp32");
        intCounterWifi++;
      }
    }
    else if (intCounterWifi < 30) {
       if (xTaskGetTickCount() - timeTaskDelay> 500){
        timeTaskDelay=xTaskGetTickCount();
        intCounterWifi = intCounterWifi + 1;
        wifi_connect(0, WIFI_STA,WiFiConf.sta_ssid,WiFiConf.sta_pwd,WiFiConf.ap_ssid);
       }
    }
  }
  if ((xTaskGetTickCount() - time_cho > 8000) && (scenes == 11)) {
    scenes = 10;
    mb.Hreg(300, scenes);
  }
  if(xQueueReceive( Queue_RFID, &idRfidmain,  ( TickType_t ) 1 )== pdPASS ){
    // gui mqtt data nhan vien
    Serial.print(" Ma NV :");
    Serial.println(idRfidmain);
  }
  if (xTaskGetTickCount() - delay_ms > 1000) {
    delay_ms = xTaskGetTickCount();
    sogui = sogui + 1;
    mb.Hreg(301, sogui);
    mb.Hreg(302, sogui >> 16);
  }
  mb.task();
 // yield();
}
