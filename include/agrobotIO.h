#ifndef AGROBOT_IO
#define AGROBOT_IO

#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <stdio.h>

#include <ArduinoJson.h>

#include "config.h"
#include "agrobotShared.h"

#if UNIFIED_CONTROLLER //TODO not good idea
#include "unifiedController/unifiedController.h"
#elif WATER_LEVEL
#include "waterLevel/waterLevel.h"

#elif LIGHT_CONTROL
#include "lightControl/ligthControl.h"
#elif NUTRITION_CONTROL
//#include "nutritionControl/nutritionControl.h"
#endif
#include "nutritionControl/nutritionControl.h"



char *getPinUID(byte);
void writeParam(byte addr, byte param);
void resetConfig();
void loadCfgFiles();
void initIO();
void initSrvCfgFile();
void saveSrvParams(mqtt_params_t *, http_params_t *, bool);
void readSrvCfgFile();
void initCfgFile();

#if UNIFIED_CONTROLLER
void savePinsCfgFile(pinConfig *, bool);
void readPinsConfig();
void processPin(pinConfig *);
void readDigitalPin(int, ...);
void writeDigitalPin(int, ...);
void timeSeriesCaller(int, ...);
void trigerCaller(int, ...);
void pwmCaller(int, ...);
#endif

#if WATER_LEVEL
void saveWaterLevelCfgFile(waterLevelCfg *, bool);
void redWaterLevelCfgFile();
#endif

#if LIGHT_CONTROL
void saveLightControlCfgFile(lightControlCfg *, bool);
void readLightControlCfgFile();
#endif

#if NUTRITION_CONTROL
void saveNutritionControlCfgFile(nutritionControlCfg *, bool);
//void saveNutritionControlCfgFile(int *, bool);
void readNutritionControlCfgFile();
#endif

void dataCallback(char *, byte *, unsigned int); //TODO check static
// };

#endif