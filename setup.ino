void initPinsArr()
{
  Serial.println("Initializing Structs");
  for (byte i = 0; i < N_PINS; i++)
  {
    //
    //    _managedPins[i].isActive = true;
    //    _managedPins[i].id = _pinout[i];
    //    _managedPins[i].type = DIGITAL_PIN;
    //    _managedPins[i].behavior = TIME_SERIES_PIN;
    //    _managedPins[i].dataType = INPUT_DATA;
    //    _managedPins[i].processing = EMPTY_CFG;
    //    memset(_managedPins[i].UID, 0, PIN_UID_SIZE);
    //    _managedPins[i].processingCallback = NULL;
    //    _managedPins[i].behaviorParams  = NULL;
    //    _managedPins[i].dataTypeParams = NULL;
    //    memset(_managedPins[i].dataBuffer, 0, sizeof(_managedPins[i].dataBuffer));
    // _managedPins[i].dataBuffer = NULL;


  }
}
//void initPinsArr()
//{
//  Serial.println("Initializing Structs");
//  for (byte i = 0; i < N_PINS; i++)
//  {
//
//    _managedPins[i].id = _pinout[i];
//    _managedPins[i].processingCallback = NULL;
//    memset(_managedPins[i].dataBuffer, 0, sizeof(_managedPins[i].dataBuffer));
//
//
//  }
/*

  bool isActive;
  byte id;
  byte type;
  byte dataType;
  int behavior[2];
  byte processing;
  char UID[PIN_UID_SIZE];
  //void (*processingCallback)(void*);
  void (*processingCallback)(void*, void(*)(void*), void*);
  void* behaviorParams;
  void* dataTypeParams;
  char* dataBuffer;
  };

  }

*/

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

void setupI2C()
{
  Wire.begin(SDA_PIN, SCL_PIN);
}
void setupSPI()
{
  SPI.begin();
}
void setupPin(pinConfig* pinCfg, JsonObject piCfgObj)
{
  //pinConfig tmpPinCfg;
  if (!isValidPin(piCfgObj["id"]))
  {
    Serial.print("ERROR: is not a valid pin");
    Serial.print((int)piCfgObj["id"]);
    //return ; //need to exit
  }
  if (isActivedPin(piCfgObj["id"]))
  {
    Serial.println("ERROR: is already reserved");
    //return false;
  }
  //  activatePin(pin->id);//TODO spi and i2c
  //
  JsonArray dataTypeParamsArr = piCfgObj["dataTypeParams"];
  switch ((byte)piCfgObj["type"])
  {
    case DIGITAL_PIN :
      pinCfg->type = DIGITAL_PIN;
      break;
    case ANALOG_PIN :
      pinCfg->type = ANALOG_PIN;
      break;
    case I2C_PINS:
      pinCfg->type = I2C_PINS;
      setI2CParams(pinCfg, dataTypeParamsArr);
      break;
    case SPI_PINS:
      pinCfg->type = SPI_PINS;
      setSPIParams(pinCfg, dataTypeParamsArr);
      break;

  }//TODO call setup function after this;

  switch ((byte)piCfgObj["dataType"])
  {
    case INPUT_DATA:
      pinCfg->dataType = INPUT_DATA;
      break;
    case OUTPUT_DATA:
      pinCfg->dataType = OUTPUT_DATA;
      break;
  }

  JsonArray paramsArr = piCfgObj["behaviorParams"];
  switch ((byte)piCfgObj["behavior"])
  {
    case TIME_SERIES_BEHAVIOR:
      pinCfg->behavior = TIME_SERIES_BEHAVIOR;
      setTimeSeriesBehavior(pinCfg, paramsArr);
      break;
    case TRIGER_BEHAVIOR:
      pinCfg->behavior = TRIGER_BEHAVIOR;
      setTrigerBehavior(pinCfg, paramsArr);
      break;
    case PWM_BEHAVIOR:
      pinCfg->behavior = PWM_BEHAVIOR;
      setPwmBehavior(pinCfg, paramsArr);
      break;
  }

}

void setI2CParams(pinConfig* pinCfg, JsonArray paramsArr) //TODO need to finalize params asignmnent
{
  //  i2cParams tparams = {(uint8_t)paramsArr[0],
  //                       (int)paramsArr[1], (uint8_t)paramsArr[2]
  //                      };
  //  pinCfg->dataTypeParams = &tparams;

}
void setSPIParams(pinConfig* pinCfg, JsonArray paramsArr)//TODO need to finalize params asignmnent
{
  //spiParams tparams = {(int)paramsArr[0]};
  pinCfg->dataTypeParams[0] = (long)paramsArr[0];
}

void setTimeSeriesBehavior(pinConfig* pinCfg, JsonArray paramsArr) //TODO processing callback need to be behacior callback
{
  //timeSeriesParams tparams = {(unsigned long)paramsArr[0], 0};
  pinCfg->processingCallback = timeSeriesCaller;
  pinCfg->behaviorParams[0] = (unsigned long)paramsArr[0] ; //TODO check maybe unsecure ponter
}



void setTrigerBehavior(pinConfig* pinCfg, JsonArray paramsArr)
{
  trigerParams tparams = {(int)paramsArr[0], 0};
  pinCfg->processingCallback = trigerCaller;
  pinCfg->behaviorParams[0] = (int)paramsArr[0];
}

void setPwmBehavior(pinConfig* pinCfg, JsonArray paramsArr)
{
 // pwmParams tparams = {(int)paramsArr[0]};
  pinCfg->processingCallback = pwmCaller;
  pinCfg->behaviorParams[0] = (int)paramsArr[0];
}

bool pinsCfgFileExists()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    return true;
  }
  return false;

}


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
  if (srvCfgFileExists() && pinsCfgFileExists())
  {
    Serial.println("---------------------------ALL  FILE  EXISTS");

    return true;
  }
  return false;
}

void configModeCallback (WiFiManager * myWiFiManager) {
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
    if (!wifiManager.startConfigPortal()) {
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
    if (!wifiManager.autoConnect()) {

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

  WiFi.macAddress(macId);

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
