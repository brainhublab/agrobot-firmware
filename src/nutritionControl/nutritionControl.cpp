#include "nutritionControl.h"

NutritionControl::NutritionControl()
{
    this->nutritionControlConfigured = false;
    //this->pwmPins[8] = {5, 4, 0, 2, 14, 12, 13, 15};
    uint8_t* pwmPinsPtr = pwmPins;
    for(int8_t i : {5, 4, 0, 2, 14, 12, 13, 15})
    {
        *pwmPinsPtr++=i;
    }
    for(int8_t i=0; i<N_DISPENSERS; i++)
    {
        this->_nutritionControlCfg[i] =  {0, 0, 0, 0};
    }

 
}

void NutritionControl::processNutritionControl()
{
}

void NutritionControl::correctNutritionConcentration()
{
}

void NutritionControl::saveNutritionControlCfgFile()
{
  
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
    nutritionControlJsonCfgOut["isConfigured"] = this->nutritionControlConfigured;

    JsonArray dispensers = nutritionControlJsonCfgOut.createNestedArray("dispensers");

    for (int i = 0; i < N_DISPENSERS; i++)
    {

      JsonObject dispenser = dispensers.createNestedObject();

      dispenser["nutritionMode"] = this->_nutritionControlCfg[i].nutritionMode;
      dispenser["targetConcentration"] = this->_nutritionControlCfg[i].targetConcentration;
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

void NutritionControl::readNutritionControlCfgFile()
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

     this->nutritionControlConfigured = nutritionControlJsonCfgIn["isConfigured"];

      for (byte i = 0; i < N_DISPENSERS; i++)
      {
       this->_nutritionControlCfg[i].nutritionMode = nutritionControlJsonCfgIn[i]["nutritionMode"];
       this->_nutritionControlCfg[i].targetConcentration = nutritionControlJsonCfgIn[i]["targetConcentration"];
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