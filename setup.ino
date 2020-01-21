void initPinsArr()
{
  Serial.println("Initializing Structs");
  for (byte i = 0; i < N_PINS; i++)
  {
    _managedPins[i].isActive = false;
    _managedPins[i].id = _pinout[i];
    _managedPins[i].type = EMPTY_CFG;
    _managedPins[i].behavior[0] = EMPTY_CFG;
    _managedPins[i].dataType = EMPTY_CFG;
    _managedPins[i].processing = EMPTY_CFG;
    memset(_managedPins[i].UID, 0, PIN_UID_SIZE);
    _managedPins[i].processingCallback = NULL;
  }
  /*
    struct pinConfig
    {
    bool isActive;
    byte id;
    byte type;
    byte behavior;
    byte dataType;
    byte processing;
    char UID[8];
    };
  */
}

bool isValidPin(byte pinId)
{
  for (byte i = 0; i < N_PINS; i++)
  {
    if (_managedPins[i].id == pinId)
    {
      return true;
    }
  }
  return false;
}

bool isActivedPin(byte pinId)
{
  for (byte i = 0; i < N_PINS; i++)
  {
    if (_managedPins[i].id == pinId && _managedPins[i].isActive)
    {
      return true;
    }

  }
  return false;
}

byte getPinIndex(byte pinId)
{
  byte index = -1;
  for (byte i = 0; i < N_PINS; i++)
  {
    index  = _managedPins[i].id == pinId ?  i :  -1;
  }
  return index;
}


void setPinType(byte pinId, byte pinType)
{
  _managedPins[getPinIndex(pinId)].type = pinType;

}

void setPinBehavior(byte pinId, byte pinBehavior)
{
  _managedPins[getPinIndex(pinId)].behavior[0] = pinBehavior;
}

void activatePin(byte pinId)
{
  _managedPins[getPinIndex(pinId)].isActive = true;
}

void setupI2C()
{
  Wire.begin(SDA_PIN, SCL_PIN);
}
void setupSPI()
{
  SPI.begin();
}
bool setupPin(pinConfig* pin)
{
  if (!isValidPin(pin->id))
  {
    Serial.println("ERROR: is not a valid pin" + pin->id);
  }
  if (isActivedPin(pin->id))
  {
    Serial.println("ERROR: is already reserved");
    return false;
  }
  activatePin(pin->id);//TODO spi and i2c

  if (pin->type == INPUT_DATA)
  {
    pinMode(pin->id, INPUT);
    //setPinType(pin.id, pin.type);
//    setPinBehavior(pin->id, pin->behavior);
  }
  else if (pin->type == OUTPUT_DATA)
  {
    pinMode(pin->id, OUTPUT);
   // setPinType(pin.id, pin.type);
    //setPinBehavior(pin->id, pin->behavior);

  }
  else if (pin->type == INPUT_DATA + I2C_PINS)
  {
    setupI2C();
  }
  else if (pin->type == OUTPUT_DATA + I2C_PINS)
  {
    setupI2C();
  }
  else if (pin->type == INPUT_DATA + SPI_PINS)
  {
    setupSPI();
  }
  else if (pin->type == OUTPUT_DATA + SPI_PINS)
  {
    setupSPI();
  }
  else
  {
    Serial.println("ERROR: Wrong pin type property");
  }
}


bool pinsCfgFileExists()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    return true;
  }
  return false;

}


bool mqttCfgFileExists()
{
  if (SPIFFS.exists("/wifi_cfg.json"))
  {
    return true;
  }
  return false;
}

bool flagsCfgFileExists()
{
  if (SPIFFS.exists("flags_cfg.json"))
  {
    return true;
  }
  return false;
}

bool cfgFilesExists()
{
  if (flagsCfgFileExists() && mqttCfgFileExists() && pinsCfgFileExists())
  {
    return true;
  }
  return false;
}

void setupWifiManager()
{
  WiFiManager wifiManager;

  WiFiManagerParameter mqttUserParam("user", "mqtt user", mqttUser, 32);
  WiFiManagerParameter mqttPassParam("pass", "mqtt pass", mqttPass, 32);


  wifiManager.addParameter(&mqttUserParam);
  wifiManager.addParameter(&mqttPassParam);

  if (reseteWifiSettings)
  {
    wifiManager.resetSettings();
  }

  wifiManager.setMinimumSignalQuality();


  wifiManager.setSaveConfigCallback(saveMqttCfgCallback);
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect("AutoConnectAP");
  if (!wifiManager.autoConnect()) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  Serial.println("connected...yeey :)");

  strlcpy(mqttUser,
          mqttUserParam.getValue(),
          mqttUserParam.getValueLength());

  strlcpy(mqttPass,
          mqttPassParam.getValue(),
          mqttPassParam.getValueLength());

  WiFi.macAddress(macId);

}

void setupMqtt()
{
  // mqttClient.set
  mqttClient.setServer(WiFi.gatewayIP(), 1883); //TODO move to another function
  mqttClient.setCallback(dataCallback);
}

void saveMqttCfgCallback()
{
  shouldSaveMqttCfg = true;



  //byte mac[6];


  // strlcpy(mqttServer, WiFi.gatewayIP(), sizeof(WiFi.gatewayIP())/ )
  // setMqttParams(mqttUser, mqttPass);
}



void resetParamFlags()
{

}

void setCfgFlag(byte addr, byte flag)
{
}
