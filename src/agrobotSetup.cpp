#include "agrobotSetup.h"

#if UNIFIED_CONTROLLER
void initPinsArr()
{
  Serial.println("Initializing Structs");
  for (int8_t i = 0; i < N_PINS; i++)
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

bool isValidPin(int8_t pinId)
{
  //  for (int8_t i = 0; i < N_PINS; i++)
  //  {
  //    if (_managedPins[i].id == pinId)
  //    {
  //      return true;
  //    }
  //  }
  //  return false;
}

bool isActivedPin(int8_t pinId)
{
  //  for (int8_t i = 0; i < N_PINS; i++)
  //  {
  //    if (_managedPins[i].id == pinId && _managedPins[i].isActive)
  //    {
  //      return true;
  //    }
  //
  //  }
  //  return false;
}

int8_t getPinIndex(int8_t pinId)
{
  //  int8_t index = -1;
  //  for (int8_t i = 0; i < N_PINS; i++)
  //  {
  //    index  = _managedPins[i].id == pinId ?  i :  -1;
  //  }
  //  return index;
}


void setPinType(int8_t pinId, int8_t pinType)
{
  // _managedPins[getPinIndex(pinId)].type = pinType;

}

void setPinBehavior(int8_t pinId, int8_t pinBehavior)
{
  //  _managedPins[getPinIndex(pinId)].behavior[0] = pinBehavior;
}

void activatePin(int8_t pinId)
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

  uint8_t mac[6]; //changed from byte 
  WiFi.macAddress(mac);
  byteArrToStr(mac, WL_MAC_ADDR_LENGTH, macId); 


}


void setupMqtt(PubSubClient* mqttClient) //TODO refact
{
  // mqttClient.set
  mqttClient->setServer(WiFi.gatewayIP(), 1883); //TODO move to another function
  mqttClient->setCallback(dataCallback);
}

void saveSrvCfgCallback()
{
  shouldSaveSrvCfg = true; 
}



void resetParamFlags()
{

}

void setCfgFlag(int8_t addr, int8_t flag) //changed from byte 
{
}


