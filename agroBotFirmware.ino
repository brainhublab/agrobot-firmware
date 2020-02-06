#include <FS.h>                   //this needs to be first, or it all crashes and burns...

/*
   ESP8266 NodeMCU LED Control over WiFi Demo

   https://circuits4you.com
*/
#include "config.h"
//#include "helpers.h"
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
#include <SPISlave.h>
//ESPMaster esp(SS); //TODO need to be implemented master slave example




//const size_t flagsCfgCapacity = JSON_OBJECT_SIZE(2) + 50;
//DynamicJsonDocument flagsJsonCfg(flagsCfgCapacity);

/*const size_t  pinsCfgCapacity = 14*JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(14) + 910;
  DynamicJsonDocument pinJsonCfg(pinsCfgCapacity);*/

/*const size_t wifiCfgCapacity = JSON_OBJECT_SIZE(4) + 190;
  DynamicJsonDocument wifiJsonCfg(wifiCfgCapacity);*/

const size_t pinsCfgCapacity = 11 * JSON_ARRAY_SIZE(4) + 11 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(12) + 890;
//DynamicJsonDocument pinsJsonCfg(pinsCfgCapacity);
StaticJsonDocument<pinsCfgCapacity> pinsJsonCfg;


char _errMsg[60];
bool shouldSaveSrvCfg = false;



WiFiClient espClient;
PubSubClient mqttClient(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

void theCb(void* p)
{

  Serial.println("THE CALLBACK IS CALLED------------------_>");
  delay(500);
}
pinConfig testPinCfg;

byte pin  = LED_BUILTIN;
void setup(void) {

  /* while (WiFi.status() != WL_CONNECTED)
    {
    delay(500);
    // Serial.print(".");
    }*/


  Serial.begin(115200);

  if (!SPIFFS.begin())
  {
    Serial.println("ERRPR: Failed to mount FS");
  }
  /*if (RESET_CONFIG)
    {
    resetConfig();
    if (FORMAT_FLASH)
    {
      if (SPIFFS.format())
      {
        Serial.println("formated file system");
      }
    }

    }
    if (!srvCfgFileExists())
    {
    initSrvCfgFile();
    }
    else
    {
    readSrvCfgFile();
    }
    if (!srvCfgFileExists() || !isSrvConfigured)
    {
    setupWifiManager();
    }
    else
    {
    // setupAutoConnection();
    readSrvCfgFile();
    }
    if (shouldSaveSrvCfg)
    {
    saveSrvParams(&mqttParams, &httpParams, true);

    }
    if (!pinsCfgFileExists())
    {
    initPinsArr();
    initPinsCfgFile();
    }
  */
  // initCfgFiles();
  //  setupCfgFiles();

  // initCfgFiles();
  // initIO();


  //mqttPass

  Serial.println("-----------------------------------------------------------------------------------------////////-----------");
  savePinsCfgFile(_managedPins, true);

  testPinCfg.processingCallback = timeSeriesCaller;
  testPinCfg.behaviorCallback = timeSeriesCaller1;
  testPinCfg.behaviorParams[0] = 1;
  testPinCfg.behaviorParams[1] = 0;
  testPinCfg.dataBufferTX[0] = (char)1;
  testPinCfg.id = 16;
  pinMode(16, OUTPUT);
}

void loop(void) {
  long p = 5;
  //tpin.processingCallback(&tparam);
  //tpin.processingCallback(&tsp, theCb, &tparam);
  //Serial.println(analogRead(17));
  //  while(p< 10000)
  //  {
  //    Serial.print("-------------------------------------> JSON SIZE ");
  //      Serial.println(p);
  //    Serial.println(pinsCfgCapacity);
  //    p++;
  //    delay(50);
  //  }
//  testPinCfg.processingCallback(testPinCfg.behaviorParams, writeDigitalPin, &testPinCfg.id, testPinCfg.dataBufferTX);
  testPinCfg.behaviorCallback(4, testPinCfg.behaviorParams, writeDigitalPin1, &testPinCfg.id, testPinCfg.dataBufferTX);

}
