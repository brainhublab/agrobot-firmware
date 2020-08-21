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