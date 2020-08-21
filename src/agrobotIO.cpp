#include <agrobotIO.h>

char *getPinUID(byte index)
{
  char *asd;
  return asd;
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

void saveSrvParams(mqtt_params_t *mqttParamsCfg, http_params_t *httpParamsCfg, bool isConfigured)
{
  File srvCfgFile = SPIFFS.open("/srv_cfg.json", "w");
  if (srvCfgFile)
  {
    Serial.println("Initializing wifi file");
    // const size_t mqttCfgCapacity = JSON_OBJECT_SIZE(3) + 110;

    const size_t srvCfgCapacity = JSON_OBJECT_SIZE(8);
    ArduinoJson::DynamicJsonDocument srvJsonCfgOut(srvCfgCapacity);

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
              sizeof(mqttParams.mqttPort));

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
   // savePinsCfgFile(_managedPins, true);

#elif WATER_LEVEL
    //saveWaterLevelCfgFile(&_waterLevel, false);

#elif LIGHT_CONTROL
    //saveLightControlCfgFile();

#elif NUTRITION_CONTROL
//    saveNutritionControlCfgFile();
#endif
  }
}

#if UNIFIED_CONTROLLER

#endif

#if WATER_LEVEL


#endif

#if LIGHT_CONTROL

#endif

#if NUTRITION_CONTROL


#endif

void dataCallback(char *topic, byte *payload, unsigned int length)
{
}
