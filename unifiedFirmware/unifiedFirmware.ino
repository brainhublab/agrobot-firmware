#include<Arduino.h>
#include <FS.h>                   //this needs to be first, or it all crashes and burns...

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

#if UNIFIED_CONTROLLER

#elif WATER_LEVEL
  #include <HX711.h>
  #include <Servo.h>
  #include <PID_v1.h>

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

bool shouldSaveSrvCfg = false;

long lastMsg = 0;
char msg[50];
int value = 0;

void theCb(void* p)
{

  Serial.println("THE CALLBACK IS CALLED------------------_>");
  delay(500);
}
//byte
byte pin  = 12;


//bool isConfigured = false;
int loopPinId = 0;
void setup(void)
{

  /* while (WiFi.status() != WL_CONNECTED)
     {
     delay(500);
    // Serial.print(".");
    }*/

  #if UNIFIED_CONTROLLER
  mcuType = 1;

  #elif WATER_LEVEL
  mcuType = 2;

  #elif LIGHT_CONTROL
  mcuType = 3;

  #elif NUTRITION_CONTROL
  mcuType = 4;
  #endif

  Serial.begin(115200);

//  if (!SPIFFS.begin())
//  {
//    Serial.println("ERRPR: Failed to mount FS");
//  }
//  //  if (SPIFFS.format())
//  //  {
//  //    Serial.println("formated file system");
//  //  }
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
//  if (!pinsCfgFileExists())
//  {
//    initPinsArr();
//    initPinsCfgFile();
//  }
//  else
//  {
//    initPinsArr();
//    //initPinsCfgFile();
//    readPinsConfig();
//    //initPinsArr();
//
//  }
//  setupPins();

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
  //  for (int i = 0; i < N_PINS; i++)
  //  {
  //    if (i != 11 && i != 12 && i!= 13)
  //    {
  //      pinMode(_managedPins[i].id, OUTPUT);
  //    }
  //    delay(200);
  //  }
  // byte _pinout[N_PINS] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot and 10/9 are not recomended



//  for (byte i = 0; i < N_PINS; i++)
//  {
//
//    Serial.println(_managedPins[i].isActive);
//    Serial.println(_managedPins[i].id );
//    Serial.println(_managedPins[i].type );
//    Serial.println(_managedPins[i].behavior);
//    Serial.println(_managedPins[i].dataType);
//    Serial.println(_managedPins[i].processing);
//
//    //
//    //        memset(_managedPins[i].behaviorParams, 0, sizeof(_managedPins[i].behaviorParams));
//    //        memset(_managedPins[i].dataTypeParams, 0, sizeof(_managedPins[i].dataTypeParams));
//    //
//    //
//    //        memset(_managedPins[i].dataBufferTX, 0, sizeof(_managedPins[i].dataBufferTX));
//    //        memset(_managedPins[i].dataBufferRX, 0, sizeof(_managedPins[i].dataBufferRX));
//    Serial.print("VALUES:    ");
//    for (int k = 0; k < 4; k++)
//    {
//      /// Serial.print("TICK");
//      //_managedPins[i].dataBufferTX[j] = (char)1;
//
//      Serial.print(_managedPins[i].behaviorParams[k]);
//
//    }
//
//    Serial.println("--------------------------------------");
//    delay(50);
//
//  }

  reconnectMqtt();

  Serial.println("-------------------END SETUP");
}

void loop(void)
{
  Serial.print(loopPinId);

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
  Serial.println("printed from CODE");
}
