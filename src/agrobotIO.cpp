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
    savePinsCfgFile(_managedPins, true);

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
void savePinsCfgFile(pinConfig *pinsArr, bool isConfigured)
{
  File pinsCfgFile = SPIFFS.open("/pins_cfg.json", "w");
  if (!pinsCfgFile)
  {
    Serial.println("failed to open config file for writing");
  }
  if (pinsCfgFile)
  {
    Serial.println("Initializing...");

    const size_t pinsCfgCapacity = 26 * JSON_ARRAY_SIZE(4) + 2 * JSON_OBJECT_SIZE(6) + 12 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(17);
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
      const size_t pinsCfgCapacity = 26 * JSON_ARRAY_SIZE(4) + 2 * JSON_OBJECT_SIZE(6) + 12 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(17) + 1270;
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
          _managedPins[i].behaviorParams[j] = behaviorParams[j];
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

void processPin(pinConfig *pin)
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

      pin->behaviorCallback(4, pin->behaviorParams, readDigitalPin, &(pin->id), pin->dataBufferRX);
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
  byte *pinId = va_arg(argList, byte *);
  char *inData = va_arg(argList, char *);
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
  byte *pinId = va_arg(argList, byte *);
  char *data = va_arg(argList, char *);
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
  long *params = va_arg(argList, long *);
  void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...));

  if (millis() - (params[1]) >= (params[0] * 1000)) //TODO convert it in setup to milliseconds
  {
    params[1] = millis();
    //callback(2, va_arg(argList, byte*), va_arg(argList, char*));
    //    if (type == DIGITAL_PIN || type == ANALOG_PIN) //TODO only IO pins
    //    {
    callback(2, va_arg(argList, byte *), va_arg(argList, char *)); // callback(2, pinID, ioBuff)
    //    }
  }
  va_end(argList);
  Serial.println("----------------EXITING IN TIME SERIES CALLER");
}

void trigerCaller(int argCount, ...) //callback is digital write or red
{
  va_list argList;
  va_start(argList, argCount);

  //  long* val = va_arg(argList, long*);
  //  long* triger = va_arg(argList, long*);
  long *params = va_arg(argList, long *);
  void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...));

  if (params[1] == params[0])
  {
    Serial.println("TRIGERED");
    callback(2, va_arg(argList, byte *), va_arg(argList, char *)); // callback(2, pinID, ioBuff)
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
  long *params = va_arg(argList, long *);
  byte *pinId = va_arg(argList, byte *);

  if (*pinId == 16 || *pinId == 3 || *pinId == 1)
  {
    Serial.println("ERROR: selected pin not support PWM ");
  }
  else
  {
    if (params[0] > 1023)
    {
      params[0] = 1023;
    }
    analogWrite(*pinId, params[0]);
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

void saveWaterLevelCfgFile(WaterLevel *waterLevel, bool isConfigured)
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
    waterLevelJsonCfgOut["title"] = "water level ID:" + (String)macId;
    waterLevelJsonCfgOut["isConfigured"] = isConfigured;

    JsonObject in = waterLevelJsonCfgOut.createNestedObject("in");
    in["gateTarget"] = waterLevel->_waterLevel.gateTarget;
    in["levelTarget"] = waterLevel->_waterLevel.levelTarget;

    JsonObject inPID = in.createNestedObject("PID");

    inPID["agKp"] = waterLevel->wlAgKp;
    inPID["agKi"] = waterLevel->wlAgKi;
    inPID["agKd"] = waterLevel->wlAgKd;
    inPID["consKp"] = waterLevel->wlConsKp;
    inPID["consKi"] = waterLevel->wlConsKi;
    inPID["consKd"] = waterLevel->wlConsKd;

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

void redWaterLevelCfgFile(WaterLevel *waterLevel)
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

      waterLevel->waterLevelConfigured = waterLevelJsonCfgIn["isConfigured"];
      waterLevel->_waterLevel.gateTarget = waterLevelJsonCfgIn["in"]["gateTarget"];
      waterLevel->_waterLevel.levelTarget = waterLevelJsonCfgIn["in"]["levelTarget"];

      JsonObject inPID = waterLevelJsonCfgIn["PID"];

      waterLevel->wlAgKp = inPID["agKp"];
      waterLevel->wlAgKi = inPID["agKi"];
      waterLevel->wlAgKd = inPID["agKd"];
      waterLevel->wlConsKp = inPID["consKp"];
      waterLevel->wlConsKi = inPID["consKi"];
      waterLevel->wlConsKd = inPID["consKd"];
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
void saveLightControlCfgFile(lightControlCfg *lcCfg, bool isConfigured)
{
  File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json", "w");

  if (lightControlCfgFile)
  {
    Serial.println("Initializing light control config file for writing ...");

    const size_t lightControlCfgCapacity = JSON_ARRAY_SIZE(96) + JSON_OBJECT_SIZE(7);
    DynamicJsonDocument lightControlJsonCfgOut(lightControlCfgCapacity);

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

void readLightControlCfgFile(LightControl *lightControl)
{
  if (SPIFFS.exists("/light_control_cfg.json"))
  {
    File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json", "r");

    if (lightControlCfgFile)
    {
      Serial.println("Reading light control config file ...");

      const size_t lightControlCfgCapacity = JSON_ARRAY_SIZE(96) + JSON_OBJECT_SIZE(6) + 150;
      DynamicJsonDocument lightControlJsonCfgIn(lightControlCfgCapacity);

      DeserializationError err = deserializeJson(lightControlJsonCfgIn, lightControlCfgFile);

      if (err)
      {
        Serial.println("ERROR: failed to read file, using default configuration");
      }

      lightControl->lightControlConfigured = lightControlJsonCfgIn["isConfigured"];
      lightControl->_lightControlCfg.lightMode = lightControlJsonCfgIn["lightMode"];
      lightControl->_lightControlCfg.targetLightLevel = lightControlJsonCfgIn["targetLightLevel"];
      //      _lightControlCfg.currentDateTime = lightControlJsonCfgIn["currentDateTime"];
      if (2 != sscanf(lightControlJsonCfgIn["currentDateTime"],
                      "%hhu%*[^0123456789]%hhu",
                      &lightControl->_lightControlCfg.currentTime.hours,
                      &lightControl->_lightControlCfg.currentTime.minutes))
      {
        Serial.println("ERROR: Cannot extract current time please check formating");
      }
      JsonArray lightIntensityMap = lightControlJsonCfgIn["lightIntensityMap"];
      for (byte i = 0; i < SIZEOF_ARRAY(lightControl->_lightControlCfg.lightIntensityMap); i++)
      {
        lightControl->_lightControlCfg.lightIntensityMap[i] = lightIntensityMap[i];
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

void saveNutritionControlCfgFile(int *ncCfg, bool isConfigured)
{
  /*
  File nutritionControlCfgFile = SPIFFS.open("/nutrition_control_cfg.json", "w");

  if (nutritionControlCfgFile)
  {
    Serial.println("Initializing nutrition control config file for writing ...");

    //    const size_t nutritionControlCfgCapacity = JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4);
    const size_t nutritionControlCfgCapacity = JSON_ARRAY_SIZE(N_DISPENSERS) +
                                               N_DISPENSERS * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4); //+ 100 + DISPENSER_JSON_SIZE * N_DISPENSERS;

    DynamicJsonDocument nutritionControlJsonCfgOut(nutritionControlCfgCapacity);

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
  */
}

void readNutritionControlCfgFile(NutritionControl *nutritionControl)
{

  if (SPIFFS.exists("/nutrition_control_cfg.json"))
  {
    File nutritionControlCfgFile = SPIFFS.open("/nutrition_control_cfg.json", "r");

    if (nutritionControlCfgFile)
    {
      Serial.println("Reading nutrition control config file ...");

      const size_t nutritionControlCfgCapacity = JSON_ARRAY_SIZE(N_DISPENSERS) +
                                                 N_DISPENSERS * JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + 100 + DISPENSER_JSON_SIZE * N_DISPENSERS;
      DynamicJsonDocument nutritionControlJsonCfgIn(nutritionControlCfgCapacity);

      DeserializationError err = deserializeJson(nutritionControlJsonCfgIn, nutritionControlCfgFile);

      if (err)
      {
        Serial.println("ERROR: failed to read file, using default configuration");
      }

      nutritionControl->nutritionControlConfigured = nutritionControlJsonCfgIn["isConfigured"];

      for (byte i = 0; i < N_DISPENSERS; i++)
      {
        nutritionControl->_nutritionControlCfg[i].nutritionMode = nutritionControlJsonCfgIn[i]["nutritionMode"];
        nutritionControl->_nutritionControlCfg[i].targetConcentration = nutritionControlJsonCfgIn[i]["targetConcentration"];
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

void dataCallback(char *topic, byte *payload, unsigned int length)
{
}
