#ifndef WATER_FLOW_H
#define WATERFLOW_H

#include <Arduino.h>

#include <stdint.h>
#include "config.h"

class WaterFlow
{
public:
    WaterFlow();
    WaterFlow(uint8_t);

    void handlerP();
    void begin();
    uint8_t getPulseCount();
    unsigned int getFlow();       // multiply bi MILILITERS, LITERS, constants
    unsigned long getFlowTotal(); //TODO multiply by constant

    uint8_t flowPin;

    float flowCalibrationFactor; // = 4.5;

    //volatile uint8_t flowPulseCount; // = 0;
    uint8_t flowPulseCount;

    float flowFlowRate;                 // = 0.0f;
    unsigned int flowMilliLitres;       // = 0;
    unsigned long flowTotalMilliLitres; // = 0;

    unsigned int flowOldTimer; // = 0;

    // void ICACHE_RAM_ATTR wlFlowOutPulseCounter();
    // {
    //     // Increment the pulse counter
    //     wlFlowOutPulseCount++;
    // }
};

#endif