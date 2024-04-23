#pragma once

#ifndef PERSONALSERVER_H
#define PERSONALSERVER_H

#include <WiFi.h>
#include <WiFiManager.h>
#include <DNSServer.h>
#include <ESPmDNS.h>
#include <WebServer.h>

#include <FS.h>
#include <SPIFFS.h>

#include <GyverPortal.h>

#include <ArduinoJson.h>

#define ESP_DRD_USE_SPIFFS true
#define JSON_CONFIG_FILE "/test_config.json"

#ifdef ESP32_DEVKIT_C_V4
#define PIN_RESET_WIFI 0
#endif

#ifdef ESP32_S3_DEVKIT_C
#define PIN_RESET_WIFI_S3 0
#endif

class PersonalServer : WiFiManager
{
public:
    PersonalServer();
    void initWifiManager(uint8_t timeout = 120);
    void saveConfigFile(void);
    int loadConfigFile(void);
    void saveConfigCallback();
    void configModelCallback(WiFiManager *myWiFiManager);

private:
    bool res;
    bool shouldSaveConfig = false;
    char testString[50];
    int testNumber;

    // uint8_t timeOut;
#ifdef ESP32_DEVKIT_C_V4
    uint8_t pinResetWifi = PIN_RESET_WIFI;
#endif

#ifdef ESP32_S3_DEVKIT_C
    uint8_t pinResetWifi = PIN_RESET_WIFI_S3;
#endif
};

#endif // PERSONALSERVER_H
