#ifndef AGROBOT_METHODS
#define AGROBOT_METHODS
#pragma once //TODO ??


#include <config.h>
#include "agrobotShared.h"

class AgroBotMethods
{
#if UNIFIED_CONTROLleR
#endif

#if WATER_LEVEL
    void proccesWaterLevel();
    void correctWaterLevel();
    callibrateMinMaxLevel();
    double getWaterLevelPercents();
    double getWaterLevelRawData();
    void setWaterLevelGate(double);
#endif

#if LIGHT_CONTROL
    void proecessLightControl();
    void correctLightLevel();
#endif

#if NUTRITION_CONTROL
    void processNutritionControl();
    void correctNutritionConcentration();
#endif
};

#endif