#include "main.h"
#include "webserver.h"
/*
 http://192.168.100.86:4999/SetTimeRtc?timestamp=1576032486
 http://192.168.100.77:4999/setKhuVuc?i=2&kv=1
  http://192.168.100.77:4999/set_id?id=58

 Mna Lan Dung

 Using DM9051
DM9051 Ethernet module consumes one SPI interface plus an interrupt and reset GPIO. By default they're connected as follows:
GPIO DM9051
GPIO19  SPI_CLK
GPIO23  SPI_MOSI
GPIO25  SPI_MISO
GPIO22  SPI_CS
GPIO4 Interrupt
GPIO5 Reset
 */




 //////////////////////////////////////////////////////////////////
 ////// Truyen tham so Html ////////////////////////////
 //////////////////////////////////////////////////////////////////

String WebServer::processor(const String& var) {
	
	char __dataFileName[sizeof(var)];
	var.toCharArray(__dataFileName, sizeof(__dataFileName));
	/*
	if (var == F("SSID")) {
		return String(Wifi_config.sta_ssid);
	}
	else if (var == F("PASS")) {
		return String(WiFiConf.sta_pwd);
	}
	else if (var == F("IP")) {
		return String(WiFiConf.sta_ip);
	}
	else if (var == F("GATEWAY")) {
		return String(WiFiConf.sta_gateway);
	}
	else if (var == F("SUB")) {
		return String(WiFiConf.sta_subnet);
	}
	else if (var == F("ServerMQTT")) {
		return String(WiFiConf.mqtt_server);
	}
	else if (var == F("PortMQTT")) {
		return String(WiFiConf.mqtt_port);
	}
	else if (var == F("USERMQTT")) {
		return String(WiFiConf.mqtt_user);
	}
	else if (var == F("PASSMQTT")) {
		return String(WiFiConf.mqtt_pass);
	}
	else if (var == F("SUBTopic1")) {
		return String(WiFiConf.mqtt_subto1);
	}
	else if (var == F("CHOOSEDHCP")) {
		return atoi(WiFiConf.choose_dhcp) == 1 ? String(1) : String(0);
	}
	else if (var == F("VERSION")) {
		return String("V1.1 Ng�y 9/1/2020");
	}
	return String();*/
}

void  WebServer::handleDoUpdate(AsyncWebServerRequest* request, const String& filename, size_t index, uint8_t* data, size_t len, bool final) {

	/*if (!index) {
		//  Serial.println("Update");
		content_len = request->contentLength();
		// if filename includes spiffs, update the spiffs partition
		int cmd = (filename.indexOf("spiffs") > -1) ? U_SPIFFS : U_FLASH;
		if (!Update.begin(UPDATE_SIZE_UNKNOWN, cmd)) {
			Update.printError(Serial);
		}
	}
	if (Update.write(data, len) != len) {
		Update.printError(Serial);
	}

	if (final) {
		AsyncWebServerResponse* response = request->beginResponse(302, "text/plain", "Please wait while the device reboots");
		response->addHeader(F("Refresh"), "20");
		response->addHeader(F("Location"), "/");
		request->send(response);
		if (!Update.end(true)) {
			Update.printError(Serial);
		}
		else {
			ESP.restart();
		}
	}*/
}

//////////////////////////////////////////////////////////////////
////// Cai dat Html ////////////////////////////
//////////////////////////////////////////////////////////////////
void WebServer::getVariHtml(AsyncWebServerRequest* request, const __FlashStringHelper* id, char* dataget, size_t chieudai) {
	if (request->hasParam(id, true)) {
		request->getParam(id, true)->value().toCharArray(dataget, chieudai);
	}
}
void WebServer::getVariIntHtml(AsyncWebServerRequest* request, const __FlashStringHelper* id, uint8_t* dataget) {
	if (request->hasParam(id)) {
		* dataget = request->getParam(id)->value().toInt();
	}
}
void WebServer::setupWiFiConf(void) {
	ServerWeb.on("/2.css", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/2.css", F("text/css"));
		});
	ServerWeb.on("/", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/index.html", String(), false, processor);
		});
	ServerWeb.on("/wifi_conf", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, "/wifi_conf.html", String(), false,processor);
		});
	ServerWeb.on("/mqtt_conf", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, F("/mqtt_conf.html"), String(), false, processor);
		});
	ServerWeb.on("/setTime", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(200,"text/plain", F("OK ...."));
		});
	ServerWeb.on("/setKhuVuc", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(200, "text/plain", F("OK ...."));
		});
	ServerWeb.on("/setRf", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(200, "text/plain" , F("OK ...."));
		});
	ServerWeb.on("/set_wifi_conf", HTTP_POST, [](AsyncWebServerRequest* request) {
		});
	ServerWeb.on("/set_id", HTTP_POST, [](AsyncWebServerRequest* request) {
		request->send(200, "text/plain", F("OK ...."));
		});
	ServerWeb.on("/set_mqtt_conf", HTTP_POST, [](AsyncWebServerRequest* request) {
		});

	ServerWeb.on("/firmware", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, F("/update.html"));
		});
	// server.on("/firmware", HTTP_GET, [](AsyncWebServerRequest *request){request->send(SPIFFS, F("/index.html"));});
	/*ServerWeb.on("/doUpdate", HTTP_POST, [](AsyncWebServerRequest* request) {},
		[](AsyncWebServerRequest* request, const String& filename, size_t index, uint8_t* data,
			size_t len, bool final) {
				handleDoUpdate(request, filename, index, data, len, final);
		});*/
	ServerWeb.on("/Reboot", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(200, "s","OK.. Rebooting");
		vTaskDelay(1000);
		ESP.restart();
		});
	ServerWeb.on("/favicon.ico", HTTP_GET, [](AsyncWebServerRequest* request) {
		request->send(SPIFFS, F("/favicon.ico"), F("image/png"));
		});
}