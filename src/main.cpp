#include <Arduino.h>
#include <FS.h> //this needs to be first, or it all crashes and burns...
#include <limits.h>

#include "config.h"
#include "agrobotShared.h"
#include "agrobotSetup.h"

#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//ESP Web Server Library to host a web page
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager

#include <PubSubClient.h>
#include <ArduinoJson.h>

#include <Wire.h>

#if UNIFIED_CONTROLLER

#elif WATER_LEVEL
#include <HX711.h>
#include <Servo.h>
#include <PID_v1.h>
#include "waterLevel/waterLevel.h"

WaterLevel waterLevel;

#elif LIGHT_CONTROL

#elif NUTRITION_CONTROL

#endif

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

long lastMsg = 0;
char msg[50];
int value = 0;

//bool isConfigured = false;
int loopPinId = 0;
bool loopSetup = true;


void setup(void)
{

  /* while (WiFi.status() != WL_CONNECTED)
     {
     delay(500);
    // Serial.print(".");
    }*/

  Serial.begin(115200);

  //  if (!SPIFFS.begin())
  //  {
  //    Serial.println("ERRPR: Failed to mount FS");
  //  }
  //
  //  if (RESET_CONFIG)
  //  {
  //    resetConfig();
  //    if (FORMAT_FLASH)
  //    {
  //      if (SPIFFS.format())
  //      {
  //        Serial.println("formated file system");
  //      }
  //    }
  //
  //  }
  //
  //  if (!srvCfgFileExists())
  //  {
  //    initSrvCfgFile();
  //  }
  //  else
  //  {
  //    readSrvCfgFile();
  //  }
  //  if (!isSrvConfigured)
  //  {
  //    setupWifiManager();
  //  }
  //  else
  //  {
  //    // setupAutoConnection();
  //    readSrvCfgFile();
  //  }
  //  if (shouldSaveSrvCfg)
  //  {
  //    saveSrvParams(&mqttParams, &httpParams, true);
  //
  //  }

  //TODO
  #if UNIFIED_CONTROLLER
  mcuType = 1;
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
    //initPinsArr();

  }
  setupPins();

  #elif WATER_LEVEL
  mcuType = 2;
  waterLevel.begin();
  //setupWaterLevel();


  #elif LIGHT_CONTROL
  mcuType = 3;

  #elif NUTRITION_CONTROL
  mcuType = 4;
  #endif




  // initCfgFiles();
  //  setupCfgFiles();

  // initCfgFiles();
  // initIO();


  //mqttPass
  //reconnectMqtt();

  Serial.println("-------------------END SETUP");
  
}

void loop(void)
{
  /*//TODOOOOO
    Serial.println("------------------------------>");
    delay(20);
  Serial.print(loopPinId);
  if(loopSetup)
  {
//      callibrateMinMaxLevel();
      loopSetup = false;

  }

*/

  //  proccesWaterLevel();

  //  Serial.println("------------------------------ ENTERING LOOP");
  //  if (loopPinId < N_PINS)
  //  {
  //    if (1)
  //    {
  //      Serial.print(loopPinId);
  //
  //      Serial.println("------------------------------ ПРОЦеССИНГ LOOP");
  //      processPin(&(_managedPins[loopPinId]));
  //
  //    }
  //    loopPinId ++;
  //  }
  //  else
  //  {
  //    loopPinId = 0;
  //  }

  // delay(5000);

  Serial.print("printed from CODE: ");
  Serial.print(waterLevel.waterFlowOut.flowPulseCount);
  Serial.print("  ----  ");
    Serial.println(waterLevel.waterFlowIn.flowPulseCount);

}
