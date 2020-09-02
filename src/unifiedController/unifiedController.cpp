#include "unifiedController.h"

void UnifiedController::savePinsCfgFile()
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

    pinJsonCfgOut["isConfigured"] = this->unifiedControllerIsConfigured;
    for (byte i = 0; i < N_PINS; i++)
    {
      String key = String(this->_managedPins[i].id);
      JsonObject pin = pinJsonCfgOut.createNestedObject(key);
      pin["isActive"] = this->_managedPins[i].isActive;
      //pin["id"] = this->_managedPins[i].id
      pin["type"] = this->_managedPins[i].type;
      pin["behavior"] = this->_managedPins[i].behavior;
      pin["dataType"] = this->_managedPins[i].dataType;
      pin["processing"] = this->_managedPins[i].processing;

      JsonArray behaviorParams = pin.createNestedArray("behaviorParams");
      for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].behaviorParams); j++)
      {
        behaviorParams[j] = this->_managedPins[i].behaviorParams[j];
      }

      JsonArray dataTypeParams = pin.createNestedArray("dataTypeParams");
      for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataTypeParams); j++)
      {
        dataTypeParams[j] = this->_managedPins[i].dataTypeParams[j];
      }

      //      JsonArray dataBufferTX = pin.createNestedArray("dataBufferTX");
      //      for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataBufferTX); j++)
      //      {
      //        dataBufferTX[j] = this->_managedPins[i].dataBufferTX[j];
      //      }
      //
      //      JsonArray dataBufferRX = pin.createNestedArray("dataBufferRX");
      //      for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataBufferRX); j++)
      //      {
      //        dataBufferRX[j] = this->_managedPins[i].dataBufferRX[j];
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

void UnifiedController::readPinsConfig()
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
        String key = String(this->_managedPins[i].id);
        JsonObject pin = pinJsonCfgIn[key];
        Serial.println("---------------------------------------- THE KEY------>");
        Serial.print(key);
        this->_managedPins[i].isActive = pin["isActive"];
        //this->_managedPins[i].id = pin["id"];
        this->_managedPins[i].type = pin["type"];
        this->_managedPins[i].dataType = pin["dataType"];
        this->_managedPins[i].behavior = pin["behavior"];
        this->_managedPins[i].processing = pin["processing"];

        JsonArray behaviorParams = pin["behaviorParams"];
        for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].behaviorParams); j++)
        {
          this->_managedPins[i].behaviorParams[j] = behaviorParams[j];
        }

        JsonArray dataTypeParams = pin["dataTypeParams"];
        for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataTypeParams); j++)
        {
          this->_managedPins[i].dataTypeParams[j] = dataTypeParams[j];
        }

        //        JsonArray dataBufferTX = pin["dataBufferTX"];
        //        for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataBufferTX); j++)
        //        {
        //           this->_managedPins[i].dataBufferTX[j] = dataBufferTX[j];
        //        }
        //
        //        JsonArray dataBufferRX = pin["dataBufferRX"];
        //        for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataBufferRX); j++)
        //        {
        //           this->_managedPins[i].dataBufferRX[j] = dataBufferRX[j];
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

void UnifiedController::processPin(pinConfig *pin)
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




//From Setup
void UnifiedController::initPinsArr()
{
  Serial.println("Initializing Structs");
  for (int8_t i = 0; i < N_PINS; i++)
  {

    this->_managedPins[i].isActive = true;
    this->_managedPins[i].id = _pinout[i];
    this->_managedPins[i].type = DIGITAL_PIN;
    this->_managedPins[i].behavior = TIME_SERIES_BEHAVIOR;
    this->_managedPins[i].dataType = OUTPUT_DATA;
    this->_managedPins[i].processing = EMPTY_CFG;
    this->_managedPins[i].behaviorCallback = NULL;

    for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].behaviorParams); j++)
    {
      this->_managedPins[i].behaviorParams[j] = 5;
    }
    for (int j = 0; j < SIZEOF_ARRAY(this->_managedPins[i].dataTypeParams); j++)
    {
      this->_managedPins[i].dataTypeParams[j] = 5;
    }

    memset(this->_managedPins[i].dataBufferTX, 1, sizeof(this->_managedPins[i].dataBufferTX));
    memset(this->_managedPins[i].dataBufferRX, 1, sizeof(this->_managedPins[i].dataBufferRX));
  }
}

bool UnifiedController::isValidPin(int8_t pinId)
{
  //  for (int8_t i = 0; i < N_PINS; i++)
  //  {
  //    if (this->_managedPins[i].id == pinId)
  //    {
  //      return true;
  //    }
  //  }
  //  return false;
}

bool UnifiedController::isActivedPin(int8_t pinId)
{
  //  for (int8_t i = 0; i < N_PINS; i++)
  //  {
  //    if (this->_managedPins[i].id == pinId && this->_managedPins[i].isActive)
  //    {
  //      return true;
  //    }
  //
  //  }
  //  return false;
}

int8_t UnifiedController::getPinIndex(int8_t pinId)
{
  //  int8_t index = -1;
  //  for (int8_t i = 0; i < N_PINS; i++)
  //  {
  //    index  = this->_managedPins[i].id == pinId ?  i :  -1;
  //  }
  //  return index;
}

void UnifiedController::setPinType(int8_t pinId, int8_t pinType)
{
   this->_managedPins[getPinIndex(pinId)].type = pinType;
}

void UnifiedController::setPinBehavior(int8_t pinId, int8_t pinBehavior)
{
   //this->_managedPins[getPinIndex(pinId)].behavior[0] = pinBehavior;
}

void UnifiedController::activatePin(int8_t pinId)
{
  // this->_managedPins[getPinIndex(pinId)].isActive = true;
}

void UnifiedController::setupPins()
{
  for (int i = 0; i < N_PINS; i++)
  {
    //setupPin(&(this->_managedPins[i]));
    switch (this->_managedPins[i].behavior)
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

    switch (this->_managedPins[i].dataType)
    {
    case INPUT_DATA:
      pinMode(this->_managedPins[i].id, INPUT);
      break;
    case OUTPUT_DATA:
      pinMode(this->_managedPins[i].id, OUTPUT);
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

void UnifiedController::setTimeSeriesBehavior(int pinId) //TODO processing callback need to be behacior callback pinConfig* pinCfg
{
  // pinCfg->behaviorCallback = timeSeriesCaller;
  this->_managedPins[pinId].behaviorCallback = timeSeriesCaller;
}

void UnifiedController::setTrigerBehavior(int pinId)
{
  this->_managedPins[pinId].behaviorCallback = trigerCaller;
}

void UnifiedController::setPwmBehavior(int pinId)
{
  this->_managedPins[pinId].behaviorCallback = pwmCaller;
}

bool UnifiedController::pinsCfgFileExists()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    return true;
  }
  return false;
}


 void UnifiedController::readDigitalPin(int argCount, ...) //TODO
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

 void UnifiedController::writeDigitalPin(int argCount, ...)
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

 void UnifiedController::timeSeriesCaller(int argCount, ...) //callback is digital write or red (param caount, paramsarr, cb, cb params
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

 void UnifiedController::trigerCaller(int argCount, ...) //callback is digital write or red
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

void UnifiedController::pwmCaller(int argCount, ...) //callback is digital write or red
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