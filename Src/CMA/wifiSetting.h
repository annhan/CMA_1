

#ifndef __WIFISETTING_H
#define __WIFISETTING_H

#ifndef __CMA_MAIN_H
//#error "This file should not be included directly. Include CMA_Main.h instead."
#endif
#define WIFI_CONF_FORMAT {0, 0, 0, 1}
#define WIFI_CONF_START 0
class WifiConf {
public:
    struct Config_t {
        uint8_t format[4];
        char sta_ssid[32];
        char sta_pwd[64];
        char sta_ip[16];
        char sta_gateway[16];
        char sta_subnet[16];
        char ap_ssid[32];
        char choose_dhcp[4];
        char mqtt_server[64];
        char mqtt_port[6];
        char mqtt_user[64];
        char mqtt_pass[64];
        char mqtt_subto1[64];
    };
    WifiConf();
};
#endif