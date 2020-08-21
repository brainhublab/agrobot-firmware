#ifndef NUTRITION_CONTROL_H
#define NUTRITION_CONTROL_H
#include <initializer_list>

#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <stdio.h>

#include <ArduinoJson.h>

#include <stdint.h>
#include "config.h"
#include "agrobotShared.h"

typedef struct
{
    uint8_t nutritionMode;
    uint8_t targetConcentration;
    uint8_t currentConcentration;
    uint8_t controlPin;
} nutritionControlCfg;

class NutritionControl
{
public:
    NutritionControl();
    void processNutritionControl();
    void correctNutritionConcentration();

    void saveNutritionControlCfgFile();
    //void saveNutritionControlCfgFile(int *, bool);
    void readNutritionControlCfgFile();

    bool nutritionControlConfigured; // = false;
    uint8_t pwmPins[8];              // = {5, 4, 0, 2, 14, 12, 13, 15} ;
    uint8_t nutritionPumpsPins[N_DISPENSERS];

    nutritionControlCfg _nutritionControlCfg[N_DISPENSERS];
};

#endif