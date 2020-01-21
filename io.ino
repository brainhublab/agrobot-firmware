char* getPinUID(byte index)
{

}

void writeParam(byte addr, byte param)
{


}
void initFlagsCfgFile()
{
  if (SPIFFS.exists("/flags_cfg.json"))
  {
    Serial.println("WARNING: flags config exists You need to reset params firs");
  }
  else
  {
    File flagsCfgFile = SPIFFS.open("/flags_cfg.json", "w");
    flagsCfgFile.close();
  }
}

void initMqttCfgFile()
{
  if (SPIFFS.exists("/mqtt_cfg.json"))
  {
    Serial.println("Warning: wifi config file exists You need to reset params first");
  }
  else
  {
    setMqttParams(mqttUser, mqttPass);
  }

}

void setMqttParams(const char* user, const char* pass)
{
  File mqttCfgFile = SPIFFS.open("/mqtt_cfg.json", "w");
  if (mqttCfgFile)
  {
    Serial.println("Initializing wifi file");
    const size_t mqttCfgCapacity = JSON_OBJECT_SIZE(2) + 100;
    DynamicJsonDocument mqttJsonCfgOut(mqttCfgCapacity);


    mqttJsonCfgOut["mqttUser"] = user;
    mqttJsonCfgOut["mqttPass"] = pass;

    serializeJson(mqttJsonCfgOut, Serial);
    if (serializeJson(mqttJsonCfgOut, mqttCfgFile) == 0)
    {
      Serial.println(F("ERROR: Failed to write to mqttCfgFile"));
    }
  }
  mqttCfgFile.close();

}

void initPinsCfgFile()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    Serial.print("WARNING: pins config file already exists  You need to reset params first");
  }
  else
  {
    Serial.println("Initializing pins");
    setPinsCfgFile(_managedPins);
  }
}
void setPinsCfgFile(pinConfig* pinsArr)
{
  File pinsCfgFile = SPIFFS.open("/pins_cfg.json", "w");
  if (!pinsCfgFile) {
    Serial.println("failed to open config file for writing");
  }
  if (pinsCfgFile)
  {
    Serial.println("Initializing...");
    const size_t  pinsCfgCapacity = 14 * JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(15) + 930;
    DynamicJsonDocument pinJsonCfgOut(pinsCfgCapacity);
    pinJsonCfgOut["isConfigured"] = false;
    for (byte i = 0; i < N_PINS; i++)
    {
      String key = String(pinsArr[i].id);
      JsonObject pin = pinJsonCfgOut.createNestedObject(key);
      pin["isActive"] = pinsArr[i].isActive;
      pin["type"] = pinsArr[i].type;
      pin["behavior"] = pinsArr[i].behavior;
      pin["dataType"] = pinsArr[i].dataType;
      pin["processing"] = pinsArr[i].processing;
      pin["UID"] = pinsArr[i].UID;
    }
    if (serializeJson(pinJsonCfgOut, pinsCfgFile) == 0)
    {
      Serial.println("ERROR: failed to write init cfg");
    }

    pinsCfgFile.close();

  }
  else
  {
    Serial.println("EROORORORORORORO");
  }

}

void readMqttConfig()
{
  memset(mqttUser, 0, sizeof(mqttUser));
  memset(mqttPass, 0, sizeof(mqttPass));
  if (SPIFFS.exists("/mqtt_cfg.json"))
  {
    File mqttCfgFile = SPIFFS.open("/mqtt_cfg.json", "r");
    if (mqttCfgFile)
    {
      Serial.println("Reading mqtt config ...");
      const size_t mqttCfgCapacity = JSON_OBJECT_SIZE(2) + 100;
      DynamicJsonDocument mqttJsonCfgIn(mqttCfgCapacity);

      DeserializationError err = deserializeJson(mqttJsonCfgIn, mqttCfgFile);
      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }
      serializeJson(mqttJsonCfgIn, Serial);
      strlcpy(mqttUser,
              mqttJsonCfgIn["mqttUser"],
              sizeof(mqttUser));

      strlcpy(mqttPass,
              mqttJsonCfgIn["mqttPass"],
              sizeof(mqttPass));
    }
    mqttCfgFile.close();
  }
  else
  {
    Serial.println("ERROR mqttCfg file does not exists");
  }
}

void readPinsConfig()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {

    File pinsCfgFile = SPIFFS.open("/pins_cfg.json", "r");
    if (pinsCfgFile)
    {
      Serial.println("Reading pins config...");
      const size_t  pinsCfgCapacity = 14 * JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(15) + 930;
      DynamicJsonDocument pinJsonCfgIn(pinsCfgCapacity);

      DeserializationError err = deserializeJson(pinJsonCfgIn, pinsCfgFile);
      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }
      // serializeJson(pinJsonCfgIn, Serial);
      pinsConfigured = pinJsonCfgIn["isConfigured"];

      for (byte i = 0; i < N_PINS; i++)
      {
        String key = String(_managedPins[i].id);
        JsonObject pin = pinJsonCfgIn[key];
        _managedPins[i].isActive = pin["isActive"];
        _managedPins[i].type = pin["type"];
        _managedPins[i].behavior[0] = pin["behavior"];
        _managedPins[i].dataType = pin["dataType"];
        _managedPins[i].processing = pin["processing"];
        strlcpy(_managedPins[i].UID, //Destination
                pin["UID"], //source
                sizeof(_managedPins[i].UID)); //destination capacity;

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

void dataCallback(char* topic, byte* payload, unsigned int length)
{

}

void processPin(pinConfig* pin, char* data)
{




}

void decomposeBehavior(int behavior)
{

}



void readDigitalPin(byte pinId, int* inData)
{
  *inData = digitalRead(pinId);

}

void writeDigital(byte pinId, byte outData)
{
  digitalWrite(pinId, outData);

}

void readI2C(char* inData, uint8_t addr, int reqRegister, uint8_t bytesToRead) //register must be byte type?
{
  Wire.beginTransmission(addr);

  Wire.write(reqRegister);

  Wire.endTransmission();
  Wire.requestFrom(addr, bytesToRead);

  uint16_t millisStart = millis();
  while (Wire.available() < bytesToRead) {
    if (ioTimeout > 0 && ((uint16_t)millis() - millisStart) > ioTimeout)
    {
      return ;
    }
    if (SIZEOF_ARRAY(inData) == bytesToRead) //TODO TEST NEEDED
    {
      for (byte i = 0; i < (byte)bytesToRead; i++)
      {
        inData[i] = Wire.read();
      }
    }
    else
    {
      return;
    }

  }


}

void writeI2c(char* outData) //TODO need to be called in setup function
{
  Wire.onReceive(_receiveEvent);
  Wire.onRequest(_requestEvent);

}

void _receiveEvent(int numBytes)
{
  slaveReceived = Wire.read(); //TODO: need to parse the recieved bytes
}

void _requestEvent()
{
  Wire.write(onI2CWrite());
}

byte onI2CWrite()
{
  return 1; //TODO need to implement
}

void setupMasterSPI()
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8); //need to be parametrical now is 8 (16/8=2Mhz)
  digitalWrite(SS, HIGH);
}
void readSPI(char* inData) //TODO need to call master setup function
{
  byte masterSend, masterReceive; //TODO need to be parametrical
  digitalWrite(SS, LOW);

  masterSend = 1; //value to send from master device
  masterReceive = SPI.transfer(masterSend);


}

void setupSlaveSPI()
{
  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);//Turn on SPI in Slave Mode
  SPI.attachInterrupt();//Interuupt ON is set for SPI commnucation



}

ISR (SPI_STC_vect)//Inerrrput routine function
{
  Slavereceived = SPDR;// Value received from master if store in variable slavereceived
  received = true;//Sets received as True
}

void writeSPI(char* outData) //TODO need to call slave setup function
{

}


void timeSeriesCaller(unsigned long* timerInterval, unsigned long* previousMillis, void (*callback)(void*), void* params)
{
  //tmpTimer = millis();
  if (millis() - *previousMillis >= *timerInterval)
  {

    callback(params);
  }
}

void timeSeriesCaller(unsigned long* timerInterval, unsigned long* previousMillis, void (*callback)())
{
  //tmpTimer = millis();
  if (millis() - *previousMillis >= *timerInterval)
  {
    callback();
  }
}


void trigerCaller(int triger, int value, void (*callback)(void*), void* params)
{
  if (triger == value)
  {
    callback(params);
  }
}

void trigerCaller(int triger, int vallue, void (*callback)())
{
  if (triger == 1)
  {
    callback();
  }
}


void pwmCaller(int dutyCycle, void (*callback)(void*), void* params)
{

}

void pwmCaller(int futyCycle, void (*callback))
{

}
