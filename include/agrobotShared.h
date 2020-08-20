#ifndef AGROBOT_SHARED
#define AGROBOT_SHARED
#include <stdint.h>
#include "config.h"

//MCU type related vars
extern uint8_t mcuType; //=0

//wifi shared vars
extern bool reseteWifiSettings; //=0

//file system vars
extern bool shouldSaveSrvCfg;

//functionaly specific vars
#if UNIFIED_CONTROLLER
extern bool pinsConfigured; //=false

typedef struct
{
    bool isActive;
    uint8_t id;
    uint8_t type;
    uint8_t dataType;
    uint8_t behavior;
    uint8_t processing;
    void (*behaviorCallback)(int, ...);
    long behaviorParams[4];
    long dataTypeParams[4];
    uint8_t dataBufferTX[64];
    uint8_t dataBufferRX[64];
    //  char dataBufferTX[4];
    //  char dataBufferRX[4];
} pinConfig;

//byte _pinout[N_PINS] = {17, 16, 14, 12, 13, 15, 2, 0, 4, 5, 3, 1}; //note 16, 3, 1, 10, 9 is high on boot
extern uint8_t _pinout[N_PINS]; //= {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot and 10/9 are not recomended

//byte _spiPinsIds[4] = {5, 6, 7, 8};
extern pinConfig _managedPins[N_PINS];

//ioTimeOut for transmissions
extern unsigned int ioTimeout; //= 100; //uint16_t
#endif

#if WATER_LEVEL
extern double waterLevelRawMax;
extern double waterLevelRawMin;
extern bool waterLevelConfigured;
typedef struct
{
    uint8_t gateCurrent;
    uint8_t gateTarget;
    uint8_t levelCurrent;
    uint8_t levelTarget;
    int waterFlowIn;
    int waterFlowOut;
} waterLevelCfg;

extern waterLevelCfg _waterLevel;

extern const uint8_t loadCellDoutPin;   // = 16; //TODO PIN IDS
extern const uint8_t loadCellSckPin;    // = 5;
extern const uint8_t waterGateServoPin; // = 0;
//
extern const int waterTankThreshold; // = 5; //TODO make it more cleaner with proper threshold

//PID configuration and variables

extern dmouble wlPidInput;   // = 0.f;
extern double wlPidOutput;   // = 0.f;
extern double wlPidSetpoint; // = 0.f;

//double Kp = 2, Ki = 5, Kd = 1;

extern double wlAgKp, wlAgKi, wlAgKd;       //= 4.0, = 0.2, = 1.0;
extern double wlConsKp, wlConsKi, wlConsKd; // = 1,  = 0.05,  = 0.25

#if HAS_WATER_FLOW_IN
extern const uint8_t waterFlowInPin;// = 4;

extern float wlFlowInCalibrationFactor;// = 4.5;

extern volatile uint8_t wlFlowInPulseCount;// = 0;

extern float wlFlowInFlowRate;// = 0.0f;
extern unsigned int wlFlowInFlowMilliLitres;// = 0;
extern unsigned long wlFlowInFTotalMilliLitres;// = 0;

extern unsigned int wlFlowInOldTimer;// = 0;

void ICACHE_RAM_ATTR wlFlowInPulseCounter();
// {
//     // Increment the pulse counter
//     wlFlowInPulseCount++;
// }
#endif

#if HAS_WATER_FLOW_OUT
extern const uint8_t waterFlowOutPin;// = 0;

extern float wlFlowOutCalibrationFactor;// = 4.5;

extern volatile uint8_t wlFlowOutPulseCount;// = 0;

extern float wlFlowOutFlowRate;// = 0.0f;
extern unsigned int wlFlowOutFlowMilliLitres;// = 0;
extern unsigned long wlFlowOutFTotalMilliLitres;// = 0;

extern unsigned int wlFlowOutOldTimer;// = 0;


void ICACHE_RAM_ATTR wlFlowOutPulseCounter();
// {
//     // Increment the pulse counter
//     wlFlowOutPulseCount++;
// }
#endif

#endif

#if LIGHT_CONTROL

extern bool lightControlConfigured;// = false;

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
    //  = {
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 0, 0, 0,
    //     0, 1, 2, 3,
    //     4, 5, 9, 13,
    //     14, 15, 15, 16,
    //     18, 20, 22, 24,
    //     28, 32, 36, 40,
    //     44, 46, 50, 56,
    //     62, 68, 74, 80,
    //     86, 92, 98, 100,
    //     100, 100, 100, 100,
    //     100, 100, 100, 100,
    //     100, 94, 88, 82,
    //     76, 70, 64, 58,
    //     52, 46, 40, 36,
    //     32, 28, 24, 20,
    //     18, 17, 16, 15,
    //     14, 13, 12, 11,
    //     10, 10, 5, 5,
    //     5, 4, 3, 2,
    //     1, 0, 0, 0,
    //     0, 0, 0, 0
    // };

} lightControlCfg;

extern lightControlCfg _lightControlCfg;

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

extern bool nutritionControlConfigured;// = false;

extern uint8_t pwmPins[];// = {5, 4, 0, 2, 14, 12, 13, 15} ;


extern uint8_t nutritionPumpsPins[N_DISPENSERS];
typedef struct
{
    uint8_t nutritionMode;
    uint8_t targetConcentration;
    uint8_t currentConcentration;
    uint8_t controlPin;
} nutritionControlCfg;

nutritionControlCfg _nutritionControlCfg[N_DISPENSERS];
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