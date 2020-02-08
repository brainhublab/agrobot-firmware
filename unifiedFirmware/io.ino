char* getPinUID(byte index)
{

}

void writeParam(byte addr, byte param)
{


}

void resetConfig()
{

}
void loadCfgFiles()
{
  readPinsConfig();
  readSrvCfgFile();
}

void initIO()
{

}
/*
  void initMainCfgFile()
  {
  if (SPIFFS.exists("/main_cfg.json"))
  {
    Serial.println("WARNING: flags config exists You need to reset params firs");
  }
  else
  {
    //File flagsCfgFile = SPIFFS.open("/main_cfg.json", "w");
    //flagsCfgFile.close();
    Serial.println("Creating main configuration file");
    setMainParams();
  }
  }

  void setMainParams()
  {
  File mainCfgFile = SPIFFS.open("main_cfg.json", "w");
  if(mainCfgFile)
  {
    Serial.println("Initializing main config file");
    const.
  }
  }
*/
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
    const size_t srvCfgCapacity = JSON_OBJECT_SIZE(8) + 460; //TODO chesk and fix if needed
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

void initPinsCfgFile()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    Serial.print("WARNING: pins config file already exists  You need to reset params first");
  }
  else
  {
    Serial.println("Initializing pins");
    //setPinsCfgFile(_managedPins);
    savePinsCfgFile(_managedPins, true);
  }
}
void savePinsCfgFile(pinConfig* pinsArr, bool isConfigured)
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
    pinsJsonCfg["isConfigured"] = isConfigured;
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
    Serial.println("-------------------------------------> JSON SIZE");
    Serial.println(pinJsonCfgOut.memoryUsage());
    if (serializeJson(pinJsonCfgOut, pinsCfgFile) == 0)
    {
      Serial.println("ERROR: failed to write init cfg");
    }


    Serial.println("-------------------------------------> JSON SIZE");
    Serial.println(pinsJsonCfg.memoryUsage());
    pinsCfgFile.close();

  }
  else
  {
    Serial.println("ERROR: Something goes wrong with pins config files");
  }

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
      serializeJson(srvJsonCfgIn, Serial);

      isSrvConfigured = srvJsonCfgIn["isConfigured"];
      strlcpy(mqttParams.mqttUser,
              srvJsonCfgIn["mqttUser"],
              sizeof(mqttParams.mqttUser));
      strlcpy(mqttParams.mqttPass,
              srvJsonCfgIn["mqttPass"],
              sizeof(srvJsonCfgIn["mqttPass"]));
      strlcpy(mqttParams.mqttSrv,
              srvJsonCfgIn["mqttSrv"],
              sizeof(srvJsonCfgIn["mqttSrv"]));
      strlcpy(mqttParams.mqttPort,
              srvJsonCfgIn["mqttPort"],
              sizeof( srvJsonCfgIn["mqttPort"]));


      strlcpy(httpParams.httpSrv,
              srvJsonCfgIn["httpSrv"],
              sizeof(srvJsonCfgIn["httpSrv"]));
      strlcpy(httpParams.httpPort,
              srvJsonCfgIn["httpPort"],
              sizeof(srvJsonCfgIn["httpPort"]));
      strlcpy(httpParams.httpToken,
              srvJsonCfgIn["httpToken"],
              sizeof(srvJsonCfgIn["httpToken"]));

    }
    srvCfgFile.close();
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
      //const size_t  pinsCfgCapacity = 14 * JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(15) + 930;
      //DynamicJsonDocument pinJsonCfgIn(pinsCfgCapacity);

      DeserializationError err = deserializeJson(pinsJsonCfg, pinsCfgFile);
      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }
      // serializeJson(pinJsonCfgIn, Serial);
      pinsConfigured = pinsJsonCfg["isConfigured"];

      for (byte i = 0; i < N_PINS; i++)
      {
        String key = String(_managedPins[i].id);
        JsonObject pin = pinsJsonCfg[key];
        //        _managedPins[i].isActive = pin["isActive"];
        //        _managedPins[i].type = pin["type"];
        //        _managedPins[i].behavior = pin["behavior"];
        //        _managedPins[i].dataType = pin["dataType"];
        //        _managedPins[i].processing = pin["processing"];
        /*    strlcpy(_managedPins[i].UID, //Destination
                    pin["UID"], //source
                    sizeof(_managedPins[i].UID)); //destination capacity;*/

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

void processPin(pinConfig* pin)
{


  switch (pin->type)
  {
    case DIGITAL_PIN:
      //process digital
      switch (pin->dataType)
      {
        case INPUT_DATA:
          // digitalRead(pin->id);//Store value to buffer and set BEHAVIOR;
          pin->behaviorCallback(4, pin->type, pin->behaviorParams, readDigitalPin, &pin->id, pin->dataBufferRX);
          break;
        case OUTPUT_DATA:
          pin->behaviorCallback(4, pin->type, pin->behaviorParams, writeDigitalPin, &pin->id, pin->dataBufferTX);
          break;
      }
      break;
    case ANALOG_PIN:
      //process analog red
      analogRead(pin->id); //TODO set the data bufer to read
      break;
    case I2C_PINS:
      switch (pin->dataType)
      {
        case INPUT_DATA:
          pin->behaviorCallback(4, pin->type, pin->behaviorParams, readI2C, pin->dataTypeParams, pin->dataBufferRX);
          break;
        case OUTPUT_DATA:
          pin->behaviorCallback(4, pin->type, pin->behaviorParams, writeI2C, pin->dataTypeParams, pin->dataBufferTX);
          break;
      }
      //process i2c io
      break;
    case SPI_PINS:
      switch (pin->behavior)
      {
        case INPUT_DATA:
          pin->behaviorCallback(4, pin->type, pin->behaviorParams, readSPI, pin->dataTypeParams, pin->dataBufferRX);
          break;
        case OUTPUT_DATA:
          pin->behaviorCallback(4, pin->type, pin->behaviorParams, writeSPI, pin->dataTypeParams, pin->dataBufferTX);
          break;
      }
      //proces spi io
      break;

  }


}



void readDigitalPin(int argCount, ...) //TODO
{
  va_list argList;
  va_start(argList, argCount);
  byte* pinId = va_arg(argList, byte*);
  char* inData = va_arg(argList, char*);
  if(digitalRead(*pinId) == HIGH)
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
void readI2C(int argCount, ...)
{

}
void readI2C1(char* inData, uint8_t addr, int reqRegister, uint8_t bytesToRead) //register must be byte type?
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


void writeI2C(int argCount, ...) //TODO need to be called in setup function
{
  //void* params, void* data
  //TODO out data need to be char*
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
//SPI master IO need to be implemented
void setupMasterSPI()
{
  SPI.begin();
  SPI.setClockDivider(SPI_CLOCK_DIV8); //need to be parametrical now is 8 (16/8=2Mhz)
  digitalWrite(SS, HIGH);
}
void readSPI(int argCount, ...) //TODO need to call master setup function
{
  //void* params, void* data
  //char* inData
  byte masterSend, masterReceive; //TODO need to be parametrical
  digitalWrite(SS, LOW);

  masterSend = 1; //value to send from master device
  masterReceive = SPI.transfer(masterSend);


}
//SPI slave IO

void _spiOnData(uint8_t* data, size_t len)
{
  //String msg = String((char*) data);
  strncpy(spiRxBuffer, (char*)data, sizeof(data));
  // (void) len;
  Serial.println(spiRxBuffer);

}

void _spiOnDataSent()
{
  Serial.println("SPI Data is sent by slave");
}

void _spiOnStatus(uint32_t statusData)
{
  Serial.printf("Status: %u\n", statusData);
  SPISlave.setStatus(millis()); //set next status
}

void _spiOnStatusSent()
{
  Serial.println("Status Sent");

}
void setupSlaveSPI()
{
  memset(spiTxBuffer, 0, sizeof(spiTxBuffer));
  memset(spiRxBuffer, 0, sizeof(spiRxBuffer));

  SPISlave.onData(_spiOnData);

  SPISlave.onDataSent(_spiOnDataSent);
  SPISlave.onStatus(_spiOnStatus);
  SPISlave.onStatusSent(_spiOnStatusSent);

  SPISlave.begin();
  SPISlave.setStatus(millis());

  //SPISlave.setData();//send initial data


}

/*ISR (SPI_STC_vect)//Inerrrput routine function
  {
  Slavereceived = SPDR;// Value received from master if store in variable slavereceived
  received = true;//Sets received as True
  }*/

void writeSPI(int argCount, ...) //TODO need to call slave setup function
{
  //void* params, void* data
  //char* outData

}

void timeSeriesCaller(int argCount, byte type, ...)
{
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
    if (type == DIGITAL_PIN || type == ANALOG_PIN)
    {
      callback(2, va_arg(argList, byte*), va_arg(argList, char*)); // callback(2, pinID, ioBuff)
    }
    else if (type == I2C_PINS)
    {
      callback(2, va_arg(argList, byte*)); //TODO place rigtht parameters for i3c iter
    }
    else if (type == SPI_PINS)
    {
      Serial.println("SPITRIGERED");
    }

  }
  va_end(argList);
}


void trigerCaller(int argCount, byte type, ...)
{
  va_list argList;
  va_start(argList, argCount);

  //  long* val = va_arg(argList, long*);
  //  long* triger = va_arg(argList, long*);
  long* params = va_arg(argList, long*);
  void (*callback)(int, ...) = va_arg(argList, void(*)(int, ...));
  if (params[1] == params[0])
  {
    if (type == DIGITAL_PIN || type == ANALOG_PIN)
    {
      callback(2, va_arg(argList, byte*), va_arg(argList, char*)); // callback(2, pinID, ioBuff)
    }
    else if (type == I2C_PINS)
    {
      callback(2, va_arg(argList, byte*)); //TODO place rigtht parameters for i3c iter
    }
    else if (type == SPI_PINS)
    {
      Serial.println("SPITRIGERED");
    }

  }

  if (params[1] == params[0])
  {
    Serial.println("TRIGERED");
  }
  else
  {
    Serial.println("NOT TRIGERED");
  }

  //long* params, void (*callback)(void*, void*), void* dtParams, void* data

  //  if (tParams == NULL)
  //  {
  //    Serial.println("ERROR: Triger params are NULL");
  //    return;
  //  }
  //    if (((trigerParams*)tParams)->triger == ((trigerParams*)tParams)->value)
  //    {
  //      callback(2, );
  //    }
  va_end(argList);
}




void pwmCaller(int argCount, byte type, ...)
{
  va_list argList;
  va_start(argList, argCount);
  long* params = va_arg(argList, long*);
  byte* pinId = va_arg(argList, byte*);
  analogWrite(*pinId, params[0] );
  //void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...);
  //long* params, void (*callback)(void*, void*), void* dtParams, void* data

  //  if (pParams == NULL)
  //  {
  //    Serial.println("ERROR: pwm params are NULL");
  //    return;
  //  }
}
