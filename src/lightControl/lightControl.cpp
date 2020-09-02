#include "ligthControl.h"

LightControl::LightControl()
{
    this->lightControlConfigured = false;
    this->_lightControlCfg = { 0,
                               0,
                               {0, 0},
                               0,
                               {0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 0, 0, 0,
                                0, 1, 2, 3,
                                4, 5, 9, 13,
                                14, 15, 15, 16,
                                18, 20, 22, 24,
                                28, 32, 36, 40,
                                44, 46, 50, 56,
                                62, 68, 74, 80,
                                86, 92, 98, 100,
                                100, 100, 100, 100,
                                100, 100, 100, 100,
                                100, 94, 88, 82,
                                76, 70, 64, 58,
                                52, 46, 40, 36,
                                32, 28, 24, 20,
                                18, 17, 16, 15,
                                14, 13, 12, 11,
                                10, 10, 5, 5,
                                5, 4, 3, 2,
                                1, 0, 0, 0,
                                0, 0, 0, 0}
    };
    uint8_t * ligtControlPinsPtr = ligtControlPins;
    for(int8_t i: {13, 15}) //TODO more pins in re4al
    {
      *ligtControlPinsPtr++=i;
    }
}

void LightControl::begin()
{
  for(int8_t i=0; i<LIGHT_CONTROL_N_PINS;i++)
  {
    pinMode(this->ligtControlPins[i], OUTPUT);
  }
}

void LightControl::proecessLightControl()
{
}

void LightControl::correctLightLevel()
{
}

void LightControl::saveLightControlCfgFile()
{
  File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json", "w");

  if (lightControlCfgFile)
  {
    Serial.println("Initializing light control config file for writing ...");

    const size_t lightControlCfgCapacity = JSON_ARRAY_SIZE(96) + JSON_OBJECT_SIZE(7);
    DynamicJsonDocument lightControlJsonCfgOut(lightControlCfgCapacity);

    lightControlJsonCfgOut["mcuType"] = whoami.mcuType;//MCU_TYPE; // TODO refactor
    lightControlJsonCfgOut["title"] = whoami.title;
    lightControlJsonCfgOut["isConfigured"] = this->lightControlConfigured;

    lightControlJsonCfgOut["lightMode"] = this->_lightControlCfg.lightMode;
    lightControlJsonCfgOut["targetLightLevel"] = this->_lightControlCfg.targetLightLevel;
    //lightControlJsonCfgOut["currentTime"] = this->_lightControlCfg.currentTime;
    char tmpTime[6];
    snprintf(tmpTime, 6,
             "%d:%d",
             this->_lightControlCfg.currentTime.hours,
             this->_lightControlCfg.currentTime.minutes);
    lightControlJsonCfgOut["currentTime"] = tmpTime;

    JsonArray lightIntensityMap = lightControlJsonCfgOut.createNestedArray("lightIntensityMap");
    for (byte i = 0; i < SIZEOF_ARRAY(this->_lightControlCfg.lightIntensityMap); i++)
    {
      lightIntensityMap[i] = this->_lightControlCfg.lightIntensityMap[i];
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

void LightControl::readLightControlCfgFile()
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

      this->lightControlConfigured = lightControlJsonCfgIn["isConfigured"];
      this->_lightControlCfg.lightMode = lightControlJsonCfgIn["lightMode"];
      this->_lightControlCfg.targetLightLevel = lightControlJsonCfgIn["targetLightLevel"];
      //      _lightControlCfg.currentDateTime = lightControlJsonCfgIn["currentDateTime"];
      if (2 != sscanf(lightControlJsonCfgIn["currentDateTime"],
                      "%hhu%*[^0123456789]%hhu",
                      &this->_lightControlCfg.currentTime.hours,
                      &this->_lightControlCfg.currentTime.minutes))
      {
        Serial.println("ERROR: Cannot extract current time please check formating");
      }
      JsonArray lightIntensityMap = lightControlJsonCfgIn["lightIntensityMap"];
      for (byte i = 0; i < SIZEOF_ARRAY(this->_lightControlCfg.lightIntensityMap); i++)
      {
        this->_lightControlCfg.lightIntensityMap[i] = lightIntensityMap[i];
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

void LightControl::setBrightnessLevel(uint8_t nodeId, uint8_t nodeBrightnes)
{
  analogWrite(nodeId, mapVal<uint8_t>(nodeBrightnes, 0, 100, 0, 255));
}
