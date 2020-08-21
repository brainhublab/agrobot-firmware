#ifndef AGROBOT_SETUP
#define AGROBOT_SETUP

//#pragma once //TODO ??


#include <stdint.h>

#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>


#include "config.h"
#include "agrobotShared.h"

#include "agrobotIO.h"
#include "agrobotHelpers.h"


#if UNIFIED_CONTROLLER //TODO not good idea

#elif WATER_LEVEL
#include <HX711.h>
#include <Servo.h>
#include <PID_v1.h>


#elif LIGHT_CONTROL

#elif NUTRITION_CONTROL

#endif


// class AgroboSetup
// {
    bool srvCfgFileExists();
    bool cfgFilesExists();
    void configModeCallback(WiFiManager *);
    void runAutoConnect();
    void setupWifiManager();
    void setupMqtt(PubSubClient*);
    void saveSrvCfgCallback();
    void resetParamFlags();
    void setCfgFlag(int8_t, int8_t); //changed from byte

#if UNIFIED_CONTROLLER
    void initPinsArr();
    bool isValidPin(int8_t);
    bool isActivedPin(int8_t);
    int8_t getPinIndex(int8_t);
    void setPinType(int8_t, int8_t);
    void setPinBehavior(int8_t, int8_t);
    void activatePin(int8_t);
    void setupPins();
    void setTimeSeriesBehavior(int);
    void setTrigerBehavior(int);
    void setPwmBehavior(int);
    bool pinsCfgFileExists();
#endif

#if WATER_LEVEL
    void setupWaterLevel();
#endif

#if NUTRITION_CONTROL

#endif

#if LIGHT_CONTROL

#endif
// };

#endif