#ifndef AGROBOT_IO_H
#define AGROBOT_IO_H

#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <stdio.h>

#include <ArduinoJson.h>

#include "config.h"
#include "agrobotShared.h"
#include "agrobotConnection.h"


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

//char *getPinUID(byte);
void writeParam(byte addr, byte param);
void resetConfig();
void loadCfgFiles();
void initIO();
void initSrvCfgFile();
void saveSrvParams(mqtt_params_t *, http_params_t *, bool);
void readSrvCfgFile();
void initCfgFile();



void mqttDataCallback(char *, byte *, unsigned int); //TODO check static
// };

#endif