#ifndef LIGHT_CONTROL
#define LIGHT_CONTROL

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
    LightControl();
    void proecessLightControl();
    void correctLightLevel();

    bool lightControlConfigured; // = false;
    lightControlCfg _lightControlCfg;
};

#endif