#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <stdio.h>

#include <ArduinoJson.h>
#include "agrobotShared.h"
#include "agrobotHelpers.h"

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
    void begin(); //TODO make configurable with multiple drivers
    void proecessLightControl();
    void correctLightLevel();

    void saveLightControlCfgFile();
    void readLightControlCfgFile();

    void setBrightnessLevel(uint8_t , uint8_t);
    

    bool lightControlConfigured; // = false;
    lightControlCfg _lightControlCfg;
    uint8_t ligtControlPins[LIGHT_CONTROL_N_PINS];

};

#endif