#ifndef AGROBOT_SETUP_H
#define AGROBOT_SETUP_H

//#pragma once //TODO ??

#include <stdint.h>
#include <WiFiManager.h> //https://github.com/tzapu/WiFiManager
#include <PubSubClient.h>

#include "config.h"
#include "agrobotShared.h"

#include "agrobotIO.h"
#include "agrobotHelpers.h"
#include "agrobotConnection.h"

#if UNIFIED_CONTROLLER //TODO not good idea

#elif WATER_LEVEL
#include <HX711.h>
#include <Servo.h>
#include <PID_v1.h>

#elif LIGHT_CONTROL

#elif NUTRITION_CONTROL

#endif
void setupWhoami();
void setupSrvAddr();
void setupMqttTopics();
bool srvCfgFileExists();
bool cfgFilesExists();
void configModeCallback(WiFiManager *);
void runAutoConnect();
void setupWifiManager();
void setupMqtt(PubSubClient *);
void saveSrvCfgCallback();
void resetParamFlags();
void setCfgFlag(int8_t, int8_t); //changed from byte

#endif
