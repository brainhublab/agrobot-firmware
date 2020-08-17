#include <Arduino.h>
#line 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
//#include<Arduino.h>
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
arduino
#elif WATER_LEVEL
  #include <HX711.h>
  #include <Servo.h>
  #include <PID_v1.h>

  HX711 waterLevelSensor;




  PID waterLevelPid(&wlPidInput, &wlPidOutput, &wlPidSetpoint, wlConsKp, wlConsKi, wlConsKd, DIRECT);

  Servo waterGateServo;




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



//bool isConfigured = false;
int loopPinId = 0;
bool loopSetup = true;



#line 75 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
void setup(void);
#line 171 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
void loop(void);
#line 2 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/connection.ino"
void publishErrorMessage();
#line 7 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/connection.ino"
void publishSuccessMessage(char* sucMsg);
#line 12 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/connection.ino"
void reconnectMqtt();
#line 2 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/helpers.ino"
void byteArrToStr(byte* arr, unsigned int len, char outStr[]);
#line 19 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/helpers.ino"
void generateWhoAmi();
#line 25 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/helpers.ino"
double mapDouble(double x, double inMin, double inMax, double outMin, double outMax);
#line 30 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/helpers.ino"
double valueToPercentsOf(double inp, double maxVal);
#line 3 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
char * getPinUID(byte index);
#line 8 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void writeParam(byte addr, byte param);
#line 14 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void resetConfig();
#line 19 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void loadCfgFiles();
#line 25 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void initIO();
#line 30 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void initSrvCfgFile();
#line 46 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void saveSrvParams(mqtt_params_t* mqttParamsCfg, http_params_t* httpParamsCfg, bool isConfigured);
#line 79 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void readSrvCfgFile();
#line 139 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void initCfgFile();
#line 572 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void saveLightControlCfgFile(lightControlCfg* lcCfg, bool isConfigured);
#line 619 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void readLightControlCfgFile();
#line 764 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void dataCallback(char* topic, byte* payload, unsigned int length);
#line 127 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/methods.ino"
void proecessLightControl();
#line 132 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/methods.ino"
void correctLightLevel();
#line 216 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
bool srvCfgFileExists();
#line 227 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
bool cfgFilesExists();
#line 240 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void configModeCallback(WiFiManager * myWiFiManager);
#line 253 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void runAutoConnect();
#line 257 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void setupWifiManager();
#line 377 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void setupMqtt();
#line 384 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void saveSrvCfgCallback();
#line 391 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void resetParamFlags();
#line 396 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
void setCfgFlag(byte addr, byte flag);
#line 75 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
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
  setupWaterLevel();

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
    Serial.println("------------------------------>");
    delay(20);
  Serial.print(loopPinId);
  if(loopSetup)
  {
//      callibrateMinMaxLevel();
      loopSetup = false;

  }
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

  
  Serial.println("printed from CODE");
}

#line 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/connection.ino"

void publishErrorMessage()
{

}

void publishSuccessMessage(char* sucMsg)
{

}

void reconnectMqtt()
{
  while (!mqttClient.connected())
  {
    Serial.println("Attempting MQTT connection ...");

    if (mqttClient.connect(macId, mqttParams.mqttUser, mqttParams.mqttPass))
    {
      Serial.println("Mqtt connected");
//      if (!pinsCfgFileExists()) //TODO rewrite
//      {
//        mqttClient.publish(cfgTopicOut, 0);
//        mqttClient.subscribe(cfgTopicIn);
//      }
//      else
//      {
//
//      }

    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

#line 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/helpers.ino"

void byteArrToStr(byte* arr, unsigned int len, char outStr[])
{
  //char outStr[len * 2];
  for (unsigned int i = 0; i < len; i++)
  {
    byte n1 = (arr[i] >> 4) & 0x0F;
    byte n2 = (arr[i] >> 0) & 0x0F;
    outStr[i * 2 + 0] = n1 < 0xA ? '0' + n1 : 'A' + n1 - 0xA;
    outStr[i * 2 + 1] = n2 < 0xA ? '0' + n2 : 'A' + n2 - 0xA;
  }
 // outStr[len * 2] = '\0';
 // return outStr;
}




void generateWhoAmi()
{


}

double mapDouble(double x, double inMin, double inMax, double outMin, double outMax)
{
  return (x-inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double valueToPercentsOf(double inp, double maxVal)
{
  return 100 / (maxVal /inp);
  
}

#line 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"


char* getPinUID(byte index)
{

}

void writeParam(byte addr, byte param)
{


}

void resetConfig()
{
  Serial.println("Reseting all configs");

}
void loadCfgFiles()
{
  //  readPinsConfig(); //TODO rewrite with defines
  readSrvCfgFile();
}

void initIO()
{

}

void initSrvCfgFile()
{
  if (SPIFFS.exists("/srv_cfg.json"))
  {
    Serial.println("Warning: wifi config file exists You need to reset params first");
  }
  else
  {
    // File mqttCfgFile = SPIFFS.open("/main_cfg.json", "w");
    // flagsCfgFile.close();
    saveSrvParams(&mqttParams, &httpParams, false);
  }

}


void saveSrvParams(mqtt_params_t* mqttParamsCfg, http_params_t* httpParamsCfg, bool isConfigured)
{

  File srvCfgFile = SPIFFS.open("/srv_cfg.json", "w");
  if (srvCfgFile)
  {
    Serial.println("Initializing wifi file");
    // const size_t mqttCfgCapacity = JSON_OBJECT_SIZE(3) + 110;

    const size_t srvCfgCapacity = JSON_OBJECT_SIZE(8);
    DynamicJsonDocument srvJsonCfgOut(srvCfgCapacity);

    srvJsonCfgOut["isConfigured"] = isConfigured;
    srvJsonCfgOut["mqttUser"] = mqttParamsCfg->mqttUser;
    srvJsonCfgOut["mqttPass"] = mqttParamsCfg->mqttPass;
    srvJsonCfgOut["mqttSrv"] = mqttParamsCfg->mqttSrv;
    srvJsonCfgOut["mqttPort"] = mqttParamsCfg->mqttPort;

    srvJsonCfgOut["httpSrv"] = httpParamsCfg->httpSrv;
    srvJsonCfgOut["httpPort"] = httpParamsCfg->httpPort;
    srvJsonCfgOut["httpToken"] = httpParamsCfg->httpToken;


    serializeJson(srvJsonCfgOut, Serial);
    if (serializeJson(srvJsonCfgOut, srvCfgFile) == 0)
    {
      Serial.println(F("ERROR: Failed to write to srvCfgFile"));
    }
  }
  srvCfgFile.close();

}

void readSrvCfgFile()
{
  Serial.println("-----------------------------> READING SRV FILE");

  if (SPIFFS.exists("/srv_cfg.json"))
  {
    File srvCfgFile = SPIFFS.open("/srv_cfg.json", "r");
    if (srvCfgFile)
    {
      Serial.println("Reading mqtt config ...");
      const size_t srvCfgCapacity = JSON_OBJECT_SIZE(8) + 460;
      DynamicJsonDocument srvJsonCfgIn(srvCfgCapacity);

      DeserializationError err = deserializeJson(srvJsonCfgIn, srvCfgFile);
      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }



      isSrvConfigured = srvJsonCfgIn["isConfigured"];

      strlcpy(mqttParams.mqttUser,
              srvJsonCfgIn["mqttUser"] | "exampleMqttUser",
              sizeof(mqttParams.mqttUser));
      strlcpy(mqttParams.mqttPass,
              srvJsonCfgIn["mqttPass"] | "exampleMqttPass",
              sizeof(mqttParams.mqttPass));
      strlcpy(mqttParams.mqttSrv,
              srvJsonCfgIn["mqttSrv"] | "example.com",
              sizeof(mqttParams.mqttSrv));
      strlcpy(mqttParams.mqttPort,
              srvJsonCfgIn["mqttPort"] | "1883",
              sizeof( mqttParams.mqttPort));


      strlcpy(httpParams.httpSrv,
              srvJsonCfgIn["httpSrv"] | "example.com",
              sizeof(httpParams.httpSrv));
      strlcpy(httpParams.httpPort,
              srvJsonCfgIn["httpPort"] | "80",
              sizeof(httpParams.httpPort));
      strlcpy(httpParams.httpToken,
              srvJsonCfgIn["httpToken"] | "exampleToken",
              sizeof(httpParams.httpToken));

      serializeJson(srvJsonCfgIn, Serial);


    }
    srvCfgFile.close();
  }
  else
  {
    Serial.println("ERROR mqttCfg file does not exists");
  }
}


void initCfgFile()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    Serial.print("WARNING: pins config file already exists  You need to reset params first");
  }
  else
  {
    Serial.println("Initializing pins");
    //setPinsCfgFile(_managedPins);
    #if UNIFIED_CONTROLLER
    savePinsCfgFile(_managedPins, true);

    #elif WATER_LEVEL
    saveWaterLevelCfgFile(&_waterLevel, false);

    #elif LIGHT_CONTROL
    //saveLightControlCfgFile();

    #elif NUTRITION_CONTROL
    //    saveNutritionControlCfgFile();
    #endif
  }
}

#if UNIFIED_CONTROLLER
void savePinsCfgFile(pinConfig* pinsArr, bool isConfigured)
{
  File pinsCfgFile = SPIFFS.open("/pins_cfg.json", "w");
  if (!pinsCfgFile)
  {
    Serial.println("failed to open config file for writing");
  }
  if (pinsCfgFile)
  {
    Serial.println("Initializing...");

    const size_t pinsCfgCapacity =  26 * JSON_ARRAY_SIZE(4) + 2 * JSON_OBJECT_SIZE(6) + 12 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(17);
    DynamicJsonDocument pinJsonCfgOut(pinsCfgCapacity);

    pinJsonCfgOut["isConfigured"] = isConfigured;
    for (byte i = 0; i < N_PINS; i++)
    {
      String key = String(pinsArr[i].id);
      JsonObject pin = pinJsonCfgOut.createNestedObject(key);
      pin["isActive"] = pinsArr[i].isActive;
      //pin["id"] = pinsArr[i].id
      pin["type"] = pinsArr[i].type;
      pin["behavior"] = pinsArr[i].behavior;
      pin["dataType"] = pinsArr[i].dataType;
      pin["processing"] = pinsArr[i].processing;

      JsonArray behaviorParams = pin.createNestedArray("behaviorParams");
      for (int j = 0; j < SIZEOF_ARRAY(pinsArr[i].behaviorParams); j++)
      {
        behaviorParams[j] = pinsArr[i].behaviorParams[j];
      }

      JsonArray dataTypeParams = pin.createNestedArray("dataTypeParams");
      for (int j = 0; j < SIZEOF_ARRAY(pinsArr[i].dataTypeParams); j++)
      {
        dataTypeParams[j] = pinsArr[i].dataTypeParams[j];
      }

      //      JsonArray dataBufferTX = pin.createNestedArray("dataBufferTX");
      //      for (int j = 0; j < SIZEOF_ARRAY(pinsArr[i].dataBufferTX); j++)
      //      {
      //        dataBufferTX[j] = pinsArr[i].dataBufferTX[j];
      //      }
      //
      //      JsonArray dataBufferRX = pin.createNestedArray("dataBufferRX");
      //      for (int j = 0; j < SIZEOF_ARRAY(pinsArr[i].dataBufferRX); j++)
      //      {
      //        dataBufferRX[j] = pinsArr[i].dataBufferRX[j];
      //      }



    }
    Serial.println("-------------------------------------> JSON SIZE SAVE PINS _1");
    Serial.println(pinJsonCfgOut.memoryUsage());
    serializeJson(pinJsonCfgOut, Serial);
    if (serializeJson(pinJsonCfgOut, pinsCfgFile) == 0)
    {
      Serial.println("ERROR: failed to write init cfg");
    }


    Serial.println("-------------------------------------> JSON SIZE SAVE PINS _1");
    Serial.println(pinJsonCfgOut.memoryUsage());
    pinsCfgFile.close();

  }
  else
  {
    Serial.println("ERROR: Something goes wrong with pins config files");
  }

}

void readPinsConfig()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {

    File pinsCfgFile = SPIFFS.open("/pins_cfg.json", "r");
    if (pinsCfgFile)
    {
      Serial.println("-------------------- READING PINS CFG");


      Serial.println("Reading pins config...");
      const size_t  pinsCfgCapacity = 26 * JSON_ARRAY_SIZE(4) + 2 * JSON_OBJECT_SIZE(6) + 12 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(17) + 1270;
      DynamicJsonDocument pinJsonCfgIn(pinsCfgCapacity);

      DeserializationError err = deserializeJson(pinJsonCfgIn, pinsCfgFile);
      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }
      // serializeJson(pinJsonCfgIn, Serial);
      pinsConfigured = pinJsonCfgIn["isConfigured"];

      serializeJson(pinJsonCfgIn, Serial);

      for (byte i = 0; i < N_PINS; i++)
      {
        String key = String(_managedPins[i].id);
        JsonObject pin = pinJsonCfgIn[key];
        Serial.println("---------------------------------------- THE KEY------>");
        Serial.print(key);
        _managedPins[i].isActive = pin["isActive"];
        //_managedPins[i].id = pin["id"];
        _managedPins[i].type = pin["type"];
        _managedPins[i].dataType = pin["dataType"];
        _managedPins[i].behavior = pin["behavior"];
        _managedPins[i].processing = pin["processing"];

        JsonArray behaviorParams = pin["behaviorParams"];
        for (int j = 0; j < SIZEOF_ARRAY(_managedPins[i].behaviorParams); j++)
        {
          _managedPins[i].behaviorParams[j] = behaviorParams[j] ;
        }

        JsonArray dataTypeParams = pin["dataTypeParams"];
        for (int j = 0; j < SIZEOF_ARRAY(_managedPins[i].dataTypeParams); j++)
        {
          _managedPins[i].dataTypeParams[j] = dataTypeParams[j];
        }

        //        JsonArray dataBufferTX = pin["dataBufferTX"];
        //        for (int j = 0; j < SIZEOF_ARRAY(_managedPins[i].dataBufferTX); j++)
        //        {
        //           _managedPins[i].dataBufferTX[j] = dataBufferTX[j];
        //        }
        //
        //        JsonArray dataBufferRX = pin["dataBufferRX"];
        //        for (int j = 0; j < SIZEOF_ARRAY(_managedPins[i].dataBufferRX); j++)
        //        {
        //           _managedPins[i].dataBufferRX[j] = dataBufferRX[j];
        //        }
      }
      pinsCfgFile.close();
    }


  }
  else
  {
    Serial.print("ERROR: no such sonfig file with name:");
    Serial.println("/pins_cfg.json");
  }
}


void processPin(pinConfig* pin)
{
  Serial.println("-------------------------- ENTERING IN PROCESS PIN");
  switch (pin->type)
  {
    case DIGITAL_PIN:
      //process digital
      switch (pin->dataType)
      {
        case INPUT_DATA:
          // digitalRead(pin->id);//Store value to buffer and set BEHAVIOR;
          Serial.println("-------------------------- INTPUT DATA  IN PROCESS PIN");

          pin->behaviorCallback(4, pin->behaviorParams, readDigitalPin, &pin->id, pin->dataBufferRX);
          break;
        case OUTPUT_DATA:
          Serial.println("-------------------------- OUTPUT DATA  IN PROCESS PIN");

          pin->behaviorCallback(4, pin->behaviorParams, writeDigitalPin, &(pin->id), pin->dataBufferTX);
          Serial.println("-------------------------- OUTPUT DATA  IN PROCESS PIN");
          break;
      }
      break;
    case ANALOG_PIN:
      //process analog red
      analogRead(pin->id); //TODO set the data bufer to read
      break;

  }
  Serial.println("-------------------------- EXIT IN PROCESS PIN");


}



void readDigitalPin(int argCount, ...) //TODO
{
  va_list argList;
  va_start(argList, argCount);
  byte* pinId = va_arg(argList, byte*);
  char* inData = va_arg(argList, char*);
  if (digitalRead(*pinId) == HIGH)
  {
    inData[0] = (char)1;
    Serial.print("------------------------------------------>HIGH");
  }
  else
  {
    Serial.print("------------------------------------------>LOW");
    inData[0] = (char)0;
  }
  Serial.print("------------------------------------------>");
  Serial.println(inData[0]);

  va_end(argList);

}



void writeDigitalPin(int argCount, ...)
{
  va_list argList;
  va_start(argList, argCount);
  byte* pinId = va_arg(argList, byte*);
  char* data = va_arg(argList, char*);
  Serial.print("DIGITAL WRITE CALLED    ");
  Serial.print(*pinId);
  Serial.print("         ");
  Serial.print((int)data[0]);
  if ((int)data[0] == 1)
  {
    data[0] = (char)0;
  }
  else
  {
    data[0] = (char)1;
  }
  digitalWrite(*pinId, (int)data[0]);
  va_end(argList);

}

void timeSeriesCaller(int argCount, ...) //callback is digital write or red (param caount, paramsarr, cb, cb params
{
  Serial.println("----------------ENTERING IN TIME SERIES CALLER");
  //  if ( == NULL)
  //  {
  //    Serial.println("ERROR: Cannot call timeseriesCaller with empty params");
  //    return;
  //  }
  va_list argList;
  va_start(argList, argCount);
  long* params = va_arg(argList, long*);
  void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...));

  if (millis() - (params[1]) >= (params[0]  * 1000)) //TODO convert it in setup to milliseconds
  {
    params[1] = millis();
    //callback(2, va_arg(argList, byte*), va_arg(argList, char*));
    //    if (type == DIGITAL_PIN || type == ANALOG_PIN) //TODO only IO pins
    //    {
    callback(2, va_arg(argList, byte*), va_arg(argList, char*)); // callback(2, pinID, ioBuff)
    //    }


  }
  va_end(argList);
  Serial.println("----------------EXITING IN TIME SERIES CALLER");
}


void trigerCaller(int argCount, ...)  //callback is digital write or red
{
  va_list argList;
  va_start(argList, argCount);

  //  long* val = va_arg(argList, long*);
  //  long* triger = va_arg(argList, long*);
  long* params = va_arg(argList, long*);
  void (*callback)(int, ...) = va_arg(argList, void(*)(int, ...));

  if (params[1] == params[0])
  {
    Serial.println("TRIGERED");
    callback(2, va_arg(argList, byte*), va_arg(argList, char*)); // callback(2, pinID, ioBuff)
  }
  else
  {
    Serial.println("NOT TRIGERED");
  }
  va_end(argList);
}




void pwmCaller(int argCount, ...) //callback is digital write or red
{
  va_list argList;
  va_start(argList, argCount);
  long* params = va_arg(argList, long*);
  byte* pinId = va_arg(argList, byte*);

  if (*pinId == 16 || *pinId == 3 || *pinId == 1)
  {
    Serial.println("ERROR: selected pin not support PWM " );
  }
  else
  {
    if (params[0] > 1023)
    {
      params[0] = 1023;
    }
    analogWrite(*pinId, params[0] );
  }
  //void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...);
  //long* params, void (*callback)(void*, void*), void* dtParams, void* data

  //  if (pParams == NULL)
  //  {
  //    Serial.println("ERROR: pwm params are NULL");
  //    return;
  //  }
}
#endif

#if WATER_LEVEL
void saveWaterLevelCfgFile(waterLevelCfg* wlCfg, bool isConfigured)
{
  File waterLevelCfgFile = SPIFFS.open("/water_level_cfg.json", "w");
  if (!waterLevelCfgFile)
  {
    Serial.println("failed to open config file for writing");
  }
  if (waterLevelCfgFile)
  {
    Serial.println("Initializing water level config...");
    const size_t waterLevelCfgCapacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
    DynamicJsonDocument waterLevelJsonCfgOut(waterLevelCfgCapacity);

    waterLevelJsonCfgOut["mcuType"] = mcuType;
    waterLevelJsonCfgOut["title"] = "water level ID:" +  (String)macId;
    waterLevelJsonCfgOut["isConfigured"] = isConfigured;

    JsonObject in = waterLevelJsonCfgOut.createNestedObject("in");
    in["gateTarget"] = wlCfg->gateTarget;
    in["levelTarget"] = wlCfg->levelTarget;

    JsonObject inPID = in.createNestedObject("PID");

    inPID["agKp"] = wlAgKp;
    inPID["agKi"] = wlAgKi;
    inPID["agKd"] = wlAgKd;
    inPID["consKp"] = wlConsKp;
    inPID["consKi"] = wlConsKi;
    inPID["consKd"] = wlConsKd;



    if (serializeJson(waterLevelJsonCfgOut, waterLevelCfgFile))
    {
      Serial.println("ERROR: failed to write water level config");
    }
    waterLevelCfgFile.close();
  }
  else
  {
    Serial.println("ERROR: Something goes wrong with water level config file");
  }
}

void redWaterLevelCfgFile()
{
  if (SPIFFS.exists("/water_level_cfg.json"))
  {
    File waterLevelCfgFile = SPIFFS.open("/water_level_cfg.json", "r");
    if (waterLevelCfgFile)
    {
      Serial.println("Reading water level configs ...");

      const size_t waterLevelCfgCapacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6) + 150;
      DynamicJsonDocument waterLevelJsonCfgIn(waterLevelCfgCapacity);

      DeserializationError err = deserializeJson(waterLevelJsonCfgIn, waterLevelCfgFile);

      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }

      waterLevelConfigured = waterLevelJsonCfgIn["isConfigured"];
      _waterLevel.gateTarget = waterLevelJsonCfgIn["in"]["gateTarget"];
      _waterLevel.levelTarget = waterLevelJsonCfgIn["in"]["levelTarget"];

      JsonObject inPID = waterLevelJsonCfgIn["PID"];

      wlAgKp = inPID["agKp"];
      wlAgKi = inPID["agKi"];
      wlAgKd = inPID["agKd"];
      wlConsKp = inPID["consKp"];
      wlConsKi = inPID["consKi"];
      wlConsKd = inPID["consKd"];

    }
    waterLevelCfgFile.close();

  }
  else
  {
    Serial.print("ERROR: no such sonfig file with name:");
    Serial.println("/water_level_cfg.json");
  }
}
#endif

#if LIGHT_CONTROL
void saveLightControlCfgFile(lightControlCfg* lcCfg, bool isConfigured)
{
  File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json", "w");

  if (lightControlCfgFile)
  {
    Serial.println("Initializing light control config file for writing ...");

    const size_t lightControlCfgCapacity = JSON_ARRAY_SIZE(96) + JSON_OBJECT_SIZE(7);
    DynamicJsonDocument  lightControlJsonCfgOut(lightControlCfgCapacity);

    lightControlJsonCfgOut["mcuType"] = mcuType; // TODO refactor
    lightControlJsonCfgOut["title"] = "light control ID:" + (String)macId;
    lightControlJsonCfgOut["isConfigured"] = isConfigured;

    lightControlJsonCfgOut["lightMode"] = lcCfg->lightMode;
    lightControlJsonCfgOut["targetLightLevel"] = lcCfg->targetLightLevel;
    //lightControlJsonCfgOut["currentTime"] = lcCfg->currentTime;
    char tmpTime[6];
    snprintf(tmpTime, 6,
             "%d:%d",
             lcCfg->currentTime.hours,
             lcCfg->currentTime.minutes);
    lightControlJsonCfgOut["currentTime"] = tmpTime;

    JsonArray lightIntensityMap = lightControlJsonCfgOut.createNestedArray("lightIntensityMap");
    for (byte i = 0; i < SIZEOF_ARRAY(lcCfg->lightIntensityMap); i++)
    {
      lightIntensityMap[i] = lcCfg->lightIntensityMap[i];
    }

    if (serializeJson(lightControlJsonCfgOut, lightControlCfgFile) == 0) // TODO write it for each
    {
      Serial.println("ERROR: failed to write light control config");
    }
    lightControlCfgFile.close();
  }
  else
  {
    Serial.println("ERROR: Failed to open light control config for writing");

  }



}

void readLightControlCfgFile()
{
  if (SPIFFS.exists("/light_control_cfg.json"))
  {
    File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json" , "r");

    if (lightControlCfgFile)
    {
      Serial.println("Reading light control config file ...");

      const size_t lightControlCfgCapacity = JSON_ARRAY_SIZE(96) + JSON_OBJECT_SIZE(6) + 150;
      DynamicJsonDocument lightControlJsonCfgIn(lightControlCfgCapacity);

      DeserializationError err =  deserializeJson(lightControlJsonCfgIn, lightControlCfgFile);

      if (err)
      {
        Serial.println("ERROR: failed to read file, using default configuration");
      }

      lightControlConfigured = lightControlJsonCfgIn["isConfigured"];
      _lightControlCfg.lightMode = lightControlJsonCfgIn["lightMode"];
      _lightControlCfg.targetLightLevel = lightControlJsonCfgIn["targetLightLevel"];
      //      _lightControlCfg.currentDateTime = lightControlJsonCfgIn["currentDateTime"];
      if (2 != sscanf(lightControlJsonCfgIn["currentDateTime"],
                      "%hhu%*[^0123456789]%hhu",
                      &_lightControlCfg.currentTime.hours,
                      &_lightControlCfg.currentTime.minutes))
      {
        Serial.println("ERROR: Cannot extract current time please check formating");
      }
      JsonArray lightIntensityMap = lightControlJsonCfgIn["lightIntensityMap"];
      for(byte i=0; i<SIZEOF_ARRAY(_lightControlCfg.lightIntensityMap); i++)
      {
        _lightControlCfg.lightIntensityMap[i]  = lightIntensityMap[i];
      }
    }
    lightControlCfgFile.close();

  }
  else
  {
    Serial.print("ERROR: no such sonfig file with name:");
    Serial.println("/light_control_cfg.json");
  }

}
#endif

#if NUTRITION_CONTROL

void saveNutritionControlCfgFile(nutritionControlCfg* ncCfg, bool isConfigured)
{
  File nutritionControlCfgFile = SPIFFS.open("/nutrition_control_cfg.json", "w");

  if (nutritionControlCfgFile)
  {
    Serial.println("Initializing nutrition control config file for writing ...");

    //    const size_t nutritionControlCfgCapacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4);
    const size_t nutritionControlCfgCapacity = JSON_ARRAY_SIZE(N_DISPENSERS)  +
        N_DISPENSERS * JSON_OBJECT_SIZE(2)  + JSON_OBJECT_SIZE(4); //+ 100 + DISPENSER_JSON_SIZE * N_DISPENSERS;

    DynamicJsonDocument  nutritionControlJsonCfgOut(nutritionControlCfgCapacity);

    nutritionControlJsonCfgOut["mcuType"] = mcuType; // TODO refactor
    nutritionControlJsonCfgOut["title"] = "nutrition control ID:" + (String)macId;
    nutritionControlJsonCfgOut["isConfigured"] = isConfigured;

    JsonArray dispensers = nutritionControlJsonCfgOut.createNestedArray("dispensers");

    for (int i = 0; i < N_DISPENSERS; i++)
    {

      JsonObject dispenser = dispensers.createNestedObject();

      dispenser["nutritionMode"] = ncCfg->nutritionMode;
      dispenser["targetConcentration"] = ncCfg->targetConcentration;

    }

    //    JsonObject in = lightControlJsonCfgOu.createNestedObject("in");
    //    in["nutritionMode"] = ncCfg->nutritionMode;
    //    in["targetConcentration"] = lcCfg->targetConcentration;


    if (serializeJson(nutritionControlJsonCfgOut, nutritionControlCfgFile) == 0) // TODO write it for each
    {
      Serial.println("ERROR: failed to write nutrition control config");
    }
    nutritionControlCfgFile.close();
  }
  else
  {
    Serial.println("ERROR: Failed to open nutrition control config for writing");

  }



}

void readNutritionControlCfgFile()
{
  if (SPIFFS.exists("/nutrition_control_cfg.json"))
  {
    File nutritionControlCfgFile = SPIFFS.open("/nutrition_control_cfg.json" , "r");

    if (nutritionControlCfgFile)
    {
      Serial.println("Reading nutrition control config file ...");

      const size_t nutritionControlCfgCapacity = JSON_ARRAY_SIZE(N_DISPENSERS)  +
          N_DISPENSERS * JSON_OBJECT_SIZE(2)  + JSON_OBJECT_SIZE(4) + 100 + DISPENSER_JSON_SIZE * N_DISPENSERS;
      DynamicJsonDocument nutritionControlJsonCfgIn(nutritionControlCfgCapacity);

      DeserializationError err =  deserializeJson(nutritionControlJsonCfgIn, nutritionControlCfgFile);

      if (err)
      {
        Serial.println("ERROR: failed to read file, using default configuration");
      }



      nutritionControlConfigured = nutritionControlJsonCfgIn["isConfigured"];

      for (byte i = 0; i < N_DISPENSERS; i++)
      {
        _nutritionControlCfg[i].nutritionMode = nutritionControlJsonCfgIn[i]["nutritionMode"];
        _nutritionControlCfg[i].targetConcentration = nutritionControlJsonCfgIn[i]["targetConcentration"];
      }

    }
    nutritionControlCfgFile.close();
  }
  else
  {
    Serial.print("ERROR: no such sonfig file with name:");
    Serial.println("/nutrition_control_cfg.json");
  }

}
#endif

void dataCallback(char* topic, byte* payload, unsigned int length)
{

}

#line 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/methods.ino"
#if UNIFIED_CONTROLleR
#endif

#if WATER_LEVEL
void proccesWaterLevel()
{

  correctWaterLevel();

}

void correctWaterLevel()
{
  Serial.println("------------------Correction of waterLevel");
  wlPidInput = getWaterLevelPercents();
  Serial.println(wlPidInput);
  double gap = abs(wlPidSetpoint - wlPidInput);
  Serial.print("-------------- GAP: ");
  Serial.println(gap);
  if (gap < 10)
  {
    //operate gate by using conservative PID
    waterLevelPid.SetTunings(wlConsKp, wlConsKi, wlConsKd);
  }
  else
  {
    //operate gate by using agresive PID
    waterLevelPid.SetTunings(wlAgKp, wlAgKi, wlAgKd);
  }
  waterLevelPid.Compute();
  Serial.print("--------------PID OUT ");
  Serial.println(map((int)wlPidOutput, 0, 255, 0, 100));
  setWaterLevelGate(map((int)wlPidOutput, 0, 255, 0, 100));
}

void callibrateMinMaxLevel() //TODO add water flow sensors detection later 
//TODO need to be finished in real installation 
{
  Serial.println("-------------Entering in calibration");
  //waterGateServo.write(0); //TODO wrato to pecent function
  setWaterLevelGate(0);
  bool waterTankEmpty = false;
  double waterLevelRawDataOld = 0;
  double waterLevelRawData = 0;
  while (!waterTankEmpty)
  {
    Serial.println("--------------MIN CALIB ITERATION");
    waterLevelRawData = abs(getWaterLevelRawData()); // TODO reading need to be abs();
    if ((abs(waterLevelRawData - waterLevelRawDataOld)) >= WATER_LEVEL_DRIFT_RAW)
    {
      waterLevelRawDataOld = waterLevelRawData;
      Serial.println("-----------------MIN LEVEL CALIBRATION");
      Serial.println(waterLevelRawDataOld);
    }
    else
    {
      waterTankEmpty = true;
    }
    delay(2000);

  }
  waterLevelSensor.set_scale();
  waterLevelSensor.tare();
  waterLevelRawData = 0;

  waterLevelRawMin = getWaterLevelRawData();
  Serial.println("Waiting .........................");
  delay(5000);
  

  //waterGateServo.write(180); //TODO wrato to pecent function
  setWaterLevelGate(100);

  while (waterTankEmpty)
  {
    Serial.println("--------------MAX CALIB ITERATION");
    waterLevelRawData = abs(getWaterLevelRawData());
    if ((abs(waterLevelRawData - waterLevelRawData)) >= WATER_LEVEL_DRIFT_RAW)
    {
      waterLevelRawDataOld = waterLevelRawData;
      Serial.println("---------------MAX LEVEL CALIBRATION");
      Serial.println(waterLevelRawDataOld);

    }
    else
    {
      waterTankEmpty = false;
    }
    delay(2000);
  }
  

  waterLevelRawMax = getWaterLevelRawData();

  Serial.print(waterLevelRawMin);
  Serial.print("      ");
  Serial.println(waterLevelRawMax);

   Serial.println("Waiting .........................2");
  delay(10000);

}

double getWaterLevelPercents()
{
  return valueToPercentsOf(getWaterLevelRawData(), waterLevelRawMax);
}

double getWaterLevelRawData()
{
  while (!waterLevelSensor.is_ready())
  {
    delay(5);
  }
  return waterLevelSensor.get_value(3);

}

void setWaterLevelGate(double percents)
{
  waterGateServo.write(map((int)percents, 0, 100, 0, 180));
}
#endif

#if LIGHT_CONTROL

void proecessLightControl()
{

}

void correctLightLevel()
{

}


#endif

#if NUTRITION_CONTROL

void processNutritionControl
{

}

void correctNutritionConcentration()
{

}
#endif

#line 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
#if UNIFIED_CONTROLLER
void initPinsArr()
{
  Serial.println("Initializing Structs");
  for (byte i = 0; i < N_PINS; i++)
  {

    _managedPins[i].isActive = true;
    _managedPins[i].id = _pinout[i];
    _managedPins[i].type = DIGITAL_PIN;
    _managedPins[i].behavior = TIME_SERIES_BEHAVIOR;
    _managedPins[i].dataType = OUTPUT_DATA;
    _managedPins[i].processing = EMPTY_CFG;
    _managedPins[i].behaviorCallback = NULL;

    for (int j = 0; j < SIZEOF_ARRAY(_managedPins[i].behaviorParams); j++)
    {
      _managedPins[i].behaviorParams[j] = 5;
    }
    for (int j = 0; j < SIZEOF_ARRAY(_managedPins[i].dataTypeParams); j++)
    {
      _managedPins[i].dataTypeParams[j] = 5;
    }


    memset(_managedPins[i].dataBufferTX, 1, sizeof(_managedPins[i].dataBufferTX));
    memset(_managedPins[i].dataBufferRX, 1, sizeof(_managedPins[i].dataBufferRX));


  }
}

bool isValidPin(byte pinId)
{
  //  for (byte i = 0; i < N_PINS; i++)
  //  {
  //    if (_managedPins[i].id == pinId)
  //    {
  //      return true;
  //    }
  //  }
  //  return false;
}

bool isActivedPin(byte pinId)
{
  //  for (byte i = 0; i < N_PINS; i++)
  //  {
  //    if (_managedPins[i].id == pinId && _managedPins[i].isActive)
  //    {
  //      return true;
  //    }
  //
  //  }
  //  return false;
}

byte getPinIndex(byte pinId)
{
  //  byte index = -1;
  //  for (byte i = 0; i < N_PINS; i++)
  //  {
  //    index  = _managedPins[i].id == pinId ?  i :  -1;
  //  }
  //  return index;
}


void setPinType(byte pinId, byte pinType)
{
  // _managedPins[getPinIndex(pinId)].type = pinType;

}

void setPinBehavior(byte pinId, byte pinBehavior)
{
  //  _managedPins[getPinIndex(pinId)].behavior[0] = pinBehavior;
}

void activatePin(byte pinId)
{
  // _managedPins[getPinIndex(pinId)].isActive = true;
}

void setupPins()
{
  for (int i = 0; i < N_PINS; i++)
  {
    //setupPin(&(_managedPins[i]));
    switch (_managedPins[i].behavior)
    {
      case TIME_SERIES_BEHAVIOR:
        setTimeSeriesBehavior(i);
        break;
      case TRIGER_BEHAVIOR:
        setTrigerBehavior(i);
        break;
      case PWM_BEHAVIOR:
        setPwmBehavior(i);
        break;
    }

    switch (_managedPins[i].dataType)
    {
      case INPUT_DATA:
        pinMode(_managedPins[i].id, INPUT);
        break;
      case OUTPUT_DATA:
        pinMode(_managedPins[i].id, OUTPUT);
        break;

    }
  }

}


//void setupPin(pinConfig* pinCfg)
//{
//  switch (pinCfg->behavior)
//  {
//    case TIME_SERIES_BEHAVIOR:
//
//      setTimeSeriesBehavior(pinCfg);
//      break;
//    case TRIGER_BEHAVIOR:
//      setTrigerBehavior(pinCfg);
//      break;
//    case PWM_BEHAVIOR:
//      setPwmBehavior(pinCfg);
//      break;
//  }

//}


void setTimeSeriesBehavior(int pinId) //TODO processing callback need to be behacior callback pinConfig* pinCfg
{
  // pinCfg->behaviorCallback = timeSeriesCaller;
  _managedPins[pinId].behaviorCallback = timeSeriesCaller;
}



void setTrigerBehavior(int pinId)
{
  _managedPins[pinId].behaviorCallback = trigerCaller;
}

void setPwmBehavior(int pinId)
{
  _managedPins[pinId].behaviorCallback = pwmCaller;
}

bool pinsCfgFileExists()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    return true;
  }
  return false;

}

#endif

#if WATER_LEVEL

void setupWaterLevel()
{
  waterLevelSensor.begin(loadCellDoutPin, loadCellSckPin);

  waterLevelSensor.set_scale();
  waterLevelSensor.tare();

  #if HAS_WATER_FLOW_IN
  pinMode(waterFlowInPin, INPUT);
  digitalWrite(waterFlowInPin, HIGH); //TODO check if its needed;

  attachInterrupt(digitalPinToInterrupt(waterFlowInPin), wlFlowInPulseCounter, FALLING);

  #endif

  #if HAS_WATER_FLOW_OUT
  pinMode(waterFlowOutPin, INPUT);
  digitalWrite(waterFlowOutPin, HIGH);

  attachInterrupt(digitalPinToInterrupt(waterFlowOutPin), wlFlowOutPulseCounter, FALLING);
  #endif

  while (!waterLevelSensor.is_ready())
  {
    delay(100);
  }

  //TODO need to choose right variables for PID
  if (_waterLevel.gateTarget != EMPTY_CFG)
  {
    wlPidInput = _waterLevel.levelCurrent;
    wlPidSetpoint = _waterLevel.levelTarget;

  }
  else
  {//TODO chack for optimal initial params
    wlPidInput = 0.0f;
    wlPidSetpoint = 100.0f;
  }
wlPidSetpoint = 100.0f;
  waterLevelPid.SetMode(AUTOMATIC);
  waterGateServo.attach(waterGateServoPin); //todo need to be attached with value from memmory

}


#endif
bool srvCfgFileExists()
{
  if (SPIFFS.exists("/srv_cfg.json"))
  {
    Serial.println("---------------------------SRV FILE  EXISTS");
    return true;
  }
  Serial.println("---------------------------SRV FILE  NOT EXISTS");

  return false;
}
bool cfgFilesExists()
{

  if (srvCfgFileExists()) //TODO need to add for rest of cfg
  {

    Serial.println("---------------------------ALL  FILE  EXISTS");

    return true;
  }
  return false;
}

void configModeCallback (WiFiManager * myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.print("-------------------------------------->");
  // myWiFiManager->resetSettings();
  // ESP.reset();

  Serial.println("on faild");
}

void runAutoConnect()
{

}
void setupWifiManager()
{
  Serial.println("---------------------------------_>Enter in config");
  WiFiManager wifiManager;
  char customhtml[24] = "type=\"checkbox\"";
  strcat(customhtml, " checked");

  //  memset(httpToken, 0, SIZEOF_ARRAY(httpToken));

  if (reseteWifiSettings)
  {
    wifiManager.resetSettings();
  }


  WiFiManagerParameter mqttUserParam("mqtt_user", "mqtt user", mqttParams.mqttUser, 32);
  WiFiManagerParameter mqttPassParam("mqtt_pass", "mqtt pass", mqttParams.mqttPass, 32);
  WiFiManagerParameter mqttSrvParam("mqtt_srv", "mqtt srv", mqttParams.mqttSrv, 64); //for now is 64 length
  WiFiManagerParameter mqttPortParam("mqtt_port", "mqtt port", mqttParams.mqttPort, 6);


  WiFiManagerParameter httpSrvParam("http_srv", "http srv", httpParams.httpSrv, 64);
  WiFiManagerParameter httpPortParam("http_port", "http port", httpParams.httpPort, 6);
  WiFiManagerParameter httpTokenParam("http_token", "http token", httpParams.httpToken, 128);//for now is placed 128 token length


  wifiManager.addParameter(&mqttUserParam);
  wifiManager.addParameter(&mqttPassParam);
  wifiManager.addParameter(&mqttSrvParam);
  wifiManager.addParameter(&mqttPortParam);

  wifiManager.addParameter(&httpSrvParam);
  wifiManager.addParameter(&httpPortParam);
  wifiManager.addParameter(&httpTokenParam);


  wifiManager.setMinimumSignalQuality();

  wifiManager.setAPCallback(configModeCallback);

  wifiManager.setSaveConfigCallback(saveSrvCfgCallback);
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect("AutoConnectAP");

  if (!isSrvConfigured)
  {
    Serial.println("--------------------------------> ENTERING NON AUITOCONECT");
    if (!wifiManager.startConfigPortal())
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      // ESP.reset();
      delay(5000);
    }
  }
  else
  {
    Serial.println("--------------------------------> ENTERING NON AUITOCONECT");
    if (!wifiManager.autoConnect())
    {

      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }
  }



  Serial.println("connected...yeey :)");

  strlcpy(mqttParams.mqttUser,
          mqttUserParam.getValue(),
          mqttUserParam.getValueLength());

  strlcpy(mqttParams.mqttPass,
          mqttPassParam.getValue(),
          mqttPassParam.getValueLength());

  strlcpy(mqttParams.mqttSrv,
          mqttSrvParam.getValue(),
          mqttSrvParam.getValueLength());

  strlcpy(mqttParams.mqttPort,
          mqttPortParam.getValue(),
          mqttPortParam.getValueLength());


  strlcpy(httpParams.httpSrv,
          httpSrvParam.getValue(),
          httpSrvParam.getValueLength());

  strlcpy(httpParams.httpPort,
          httpPortParam.getValue(),
          httpPortParam.getValueLength());

  strlcpy(httpParams.httpToken,
          httpTokenParam.getValue(),
          httpTokenParam.getValueLength());




  Serial.println("----------------------------------------------------------------------------SIZE");
  //Serial.println(httpTokenParam.getValueLength());

  Serial.println( httpTokenParam.getValueLength());
  Serial.println( strlen(httpTokenParam.getValue()));

  byte mac[6];
  WiFi.macAddress(mac);
  byteArrToStr(mac, WL_MAC_ADDR_LENGTH, macId);


}


void setupMqtt()
{
  // mqttClient.set
  mqttClient.setServer(WiFi.gatewayIP(), 1883); //TODO move to another function
  mqttClient.setCallback(dataCallback);
}

void saveSrvCfgCallback()
{
  shouldSaveSrvCfg = true;
}



void resetParamFlags()
{

}

void setCfgFlag(byte addr, byte flag)
{
}

