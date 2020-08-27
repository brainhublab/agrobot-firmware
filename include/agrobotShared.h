#ifndef AGROBOT_SHARED_H
#define AGROBOT_SHARED_H
#include <Arduino.h>
#include <stdarg.h>


#include <stdint.h>
#include "config.h"


//#if UNIFIED_CONTROLLER //TODO not good idea
    static void readDigitalPin(int, ...);
    static void writeDigitalPin(int, ...);
    static void timeSeriesCaller(int, ...);
    static void trigerCaller(int, ...);
    static void pwmCaller(int, ...);
//#elif WATER_LEVEL

//#elif LIGHT_CONTROL

//#elif NUTRITION_CONTROL

//#endif

//MCU type related vars
extern uint8_t mcuType; //=0

//wifi shared vars
extern bool reseteWifiSettings; //=0

//file system vars
extern bool shouldSaveSrvCfg;

//functionaly specific vars
#if UNIFIED_CONTROLLER

#endif

#if WATER_LEVEL



#endif

#if LIGHT_CONTROL
//split the day to 10 mins intervals and parse the light intensity map
//uint8_t lightIntensityMap[96] = {
//  0, 0, 0, 0,
//  0, 0, 0, 0,
//  0, 0, 0, 0,
//  0, 0, 0, 0,
//  0, 1, 2, 3,
//  4, 5, 9, 13,
//  14, 15, 15, 16,
//  18, 20, 22, 24,
//  28, 32, 36, 40,
//  44, 46, 50, 56,
//  62, 68, 74, 80,
//  86, 92, 98, 100,
//  100, 100, 100, 100,
//  100, 100, 100, 100,
//  100, 94, 88, 82,
//  76, 70, 64, 58,
//  52, 46, 40, 36,
//  32, 28, 24, 20,
//  18, 17, 16, 15,
//  14, 13, 12, 11,
//  10, 10, 5, 5,
//  5, 4, 3, 2,
//  1, 0, 0, 0,
//  0, 0, 0, 0
//};
//Nutrition controll module config
#endif

#if NUTRITION_CONTROL


#endif

//conn type
extern bool mqttClientFlag;// = false;
extern bool httpClientFlag;// = false;

//Mqtt conf

//mqtt topics
extern char cnfTopic[64];// = "asd";
extern char dataTopic[64];// = "asd";

//net structs

extern bool isSrvConfigured;// = false;
typedef struct
{
    char mqttUser[32];
    char mqttPass[32];
    char mqttSrv[64];
    char mqttPort[6];
} mqtt_params_t;

//Http conf
typedef struct
{
    char httpSrv[64];
    char httpPort[6];
    char httpToken[128];
} http_params_t;

extern mqtt_params_t mqttParams;// = {"", "", "", "1883"};
extern http_params_t httpParams;// = {"", "80", ""};


extern  char macId[12];

extern char cfgTopicOut[12];
extern char cfgTopicIn[12];

#endif