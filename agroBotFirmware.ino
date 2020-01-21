#include <FS.h>                   //this needs to be first, or it all crashes and burns...

/*
   ESP8266 NodeMCU LED Control over WiFi Demo

   https://circuits4you.com
*/
#include "config.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <PubSubClient.h>


#include <ArduinoJson.h>


#include <Wire.h>
#include<SPI.h>




const size_t flagsCfgCapacity = JSON_OBJECT_SIZE(2) + 50;
DynamicJsonDocument flagsJsonCfg(flagsCfgCapacity);

/*const size_t  pinsCfgCapacity = 14*JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(14) + 910;
  DynamicJsonDocument pinJsonCfg(pinsCfgCapacity);*/

/*const size_t wifiCfgCapacity = JSON_OBJECT_SIZE(4) + 190;
  DynamicJsonDocument wifiJsonCfg(wifiCfgCapacity);*/

char _errMsg[60];
bool shouldSaveMqttCfg = false;



WiFiClient espClient;
PubSubClient mqttClient(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;



void setup(void) {
  Serial.begin(115200);


  WiFiManager wifiManager;
  // Wait for connection
  /* while (WiFi.status() != WL_CONNECTED)
    {
     delay(500);
    // Serial.print(".");
    }*/

  if (RESET_SETTINGS)
  {
    if (SPIFFS.format())
    {
      Serial.println("formated file system");
    }

  }
  SPIFFS.begin();
  if (!mqttCfgFileExists())
  {
    setupWifiManager();

  }
  if (shouldSaveMqttCfg)
  {
    setMqttParams(mqttUser, mqttPass);
  }
  if (!pinsCfgFileExists())
  {
    initPinsArr();
    initPinsCfgFile();
  }
  if (!flagsCfgFileExists())
  {
    initFlagsCfgFile();
  }
  // initCfgFiles();
  //  setupCfgFiles();
  readPinsConfig();
  readMqttConfig();

  //mqttPass

  Serial.println("FROM STRUCTARR");
  Serial.println(_managedPins[0].UID);
  Serial.println(WiFi.gatewayIP()[0]);

}

void loop(void) {
}
