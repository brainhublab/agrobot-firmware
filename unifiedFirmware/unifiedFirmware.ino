#include<Arduino.h>
#include <FS.h>                   //this needs to be first, or it all crashes and burns...
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <PubSubClient.h>
#include <ArduinoJson.h>


#include <Wire.h>

//ESPMaster esp(SS); //TODO need to be implemented master slave example

#include "config.h"

char _errMsg[60];


//const size_t flagsCfgCapacity = JSON_OBJECT_SIZE(2) + 50;
//DynamicJsonDocument flagsJsonCfg(flagsCfgCapacity);

/*const size_t wifiCfgCapacity = JSON_OBJECT_SIZE(4) + 190;
  DynamicJsonDocument wifiJsonCfg(wifiCfgCapacity);*/

//const size_t pinsCfgCapacity = 11 * JSON_ARRAY_SIZE(4) + 11 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(12) + 890;
//DynamicJsonDocument pinsJsonCfg(pinsCfgCapacity);
//StaticJsonDocument<pinsCfgCapacity> pinsJsonCfg;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

bool shouldSaveSrvCfg = false;

long lastMsg = 0;
char msg[50];
int value = 0;

void theCb(void* p)
{

  Serial.println("THE CALLBACK IS CALLED------------------_>");
  delay(500);
}
pinConfig testPinCfg;
//byte
byte pin  = 12;


//bool isConfigured = false;

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
//  if (SPIFFS.format())
//  {
//    Serial.println("formated file system");
//  }
  if (RESET_CONFIG)
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
  if (!isSrvConfigured)
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
  else
  {
    initPinsArr();
    //initPinsCfgFile();
    readPinsConfig();
  }

  // initCfgFiles();
  //  setupCfgFiles();

  // initCfgFiles();
  // initIO();


  //mqttPass

  Serial.println("-----------------------------------------------------------------------------------------////////-----------");
 // savePinsCfgFile(_managedPins, true);
  //
  //  //testPinCfg.behaviorCallback = timeSeriesCaller;
  //  testPinCfg.behaviorCallback = pwmCaller;
  //  testPinCfg.behaviorParams[0] = 512;
  //  testPinCfg.behaviorParams[1] = 0;
  //  testPinCfg.dataBufferTX[0] = (char)1;
  //  testPinCfg.dataBufferRX[0] = (char)1;
  //  testPinCfg.id = 12;
  //  testPinCfg.type = DIGITAL_PIN;
  //  pinMode(4, INPUT);
  //  pinMode(pin, INPUT);
  //  analogWrite(12, 512);

  for (byte i = 0; i < N_PINS; i++)
  {

    Serial.println(_managedPins[i].isActive);
    Serial.println(_managedPins[i].id );
    Serial.println(_managedPins[i].type );
    Serial.println(_managedPins[i].behavior);
    Serial.println(_managedPins[i].dataType);
    Serial.println(_managedPins[i].processing);

    //
    //        memset(_managedPins[i].behaviorParams, 0, sizeof(_managedPins[i].behaviorParams));
    //        memset(_managedPins[i].dataTypeParams, 0, sizeof(_managedPins[i].dataTypeParams));
    //
    //
    //        memset(_managedPins[i].dataBufferTX, 0, sizeof(_managedPins[i].dataBufferTX));
    //        memset(_managedPins[i].dataBufferRX, 0, sizeof(_managedPins[i].dataBufferRX));


    Serial.println("--------------------------------------");

  }
}

void loop(void) {
  long p = 1;


  delay(50000);
  Serial.println("printed from CODE");
}
