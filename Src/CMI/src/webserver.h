#ifndef __WEBSERVER_H
#define __WEBSERVER_H

#ifndef __CMA_MAIN_H
//#error "This file should not be included directly. Include CMA_Main.h instead."
#endif
#include <ESPAsyncWebServer.h>
#include <AsyncMqttClient.h>

class WebServer:public AsyncWebServer {
public:
    friend class AsyncWebServerRequest;
    uint16_t web_port = 4999; 
    char dataHtmlType[11]  = "d";
    struct Config_t {
        
    };
    AsyncWebServer& ServerWeb;
    WebServer(Config_t& data);
    static String processor(const String& var) ;
    void handleDoUpdate(AsyncWebServerRequest* request, const String& filename, size_t index, uint8_t* data, size_t len, bool final) ;
    void setupWiFiConf(void) ;
    void getVariHtml(AsyncWebServerRequest* request, const __FlashStringHelper* id, char* dataget, size_t chieudai);
    void getVariIntHtml(AsyncWebServerRequest* request, const __FlashStringHelper* id, uint8_t* dataget) ;
};

#endif