#ifndef NUTRITION_CONTROL_H
#define NUTRITION_CONTROL_H
#include <initializer_list>

#include <stdint.h>
#include "config.h"


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

    bool nutritionControlConfigured; // = false;
    uint8_t pwmPins[8];               // = {5, 4, 0, 2, 14, 12, 13, 15} ;
    uint8_t nutritionPumpsPins[N_DISPENSERS];

    nutritionControlCfg _nutritionControlCfg[N_DISPENSERS];
};

#endif