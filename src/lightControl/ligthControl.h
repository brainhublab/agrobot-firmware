#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <stdint.h>
#include "config.h"

typedef struct
{
    uint8_t hours;
    uint8_t minutes;
} timeOfTheDay;

typedef struct
{
    uint8_t currentLightLevel;
    uint8_t targetLightLevel;
    timeOfTheDay currentTime;
    uint8_t lightMode;
    uint8_t lightIntensityMap[96];

} lightControlCfg;

class LightControl
{
    public:
    LightControl();
    void proecessLightControl();
    void correctLightLevel();

    bool lightControlConfigured; // = false;
    lightControlCfg _lightControlCfg;
};

#endif