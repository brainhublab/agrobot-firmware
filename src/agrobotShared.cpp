#include "agrobotShared.h"

//MCU type related vars
extern uint8_t mcuType = 0;

//wifi shared vars
extern bool reseteWifiSettings = 0;

//file system vars
extern bool shouldSaveSrvCfg = false;

//functionaly specific vars
#if UNIFIED_CONTROLLER

static void readDigitalPin(int argCount, ...) //TODO
{
    va_list argList;
    va_start(argList, argCount);
    byte *pinId = va_arg(argList, byte *);
    char *inData = va_arg(argList, char *);
    if (digitalRead(*pinId) == HIGH)
    {
        inData[0] = (char)1;
        Serial.print("------------------------------------------>HIGH");
    }
    else
    {
        Serial.print("------------------------------------------>LOW");
        inData[0] = (char)0;
    }
    Serial.print("------------------------------------------>");
    Serial.println(inData[0]);

    va_end(argList);
}

static void writeDigitalPin(int argCount, ...)
{
    va_list argList;
    va_start(argList, argCount);
    byte *pinId = va_arg(argList, byte *);
    char *data = va_arg(argList, char *);
    Serial.print("DIGITAL WRITE CALLED    ");
    Serial.print(*pinId);
    Serial.print("         ");
    Serial.print((int)data[0]);
    if ((int)data[0] == 1)
    {
        data[0] = (char)0;
    }
    else
    {
        data[0] = (char)1;
    }
    digitalWrite(*pinId, (int)data[0]);
    va_end(argList);
}

static void timeSeriesCaller(int argCount, ...) //callback is digital write or red (param caount, paramsarr, cb, cb params
{
    Serial.println("----------------ENTERING IN TIME SERIES CALLER");
    //  if ( == NULL)
    //  {
    //    Serial.println("ERROR: Cannot call timeseriesCaller with empty params");
    //    return;
    //  }
    va_list argList;
    va_start(argList, argCount);
    long *params = va_arg(argList, long *);
    void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...));

    if (millis() - (params[1]) >= (params[0] * 1000)) //TODO convert it in setup to milliseconds
    {
        params[1] = millis();
        //callback(2, va_arg(argList, byte*), va_arg(argList, char*));
        //    if (type == DIGITAL_PIN || type == ANALOG_PIN) //TODO only IO pins
        //    {
        callback(2, va_arg(argList, byte *), va_arg(argList, char *)); // callback(2, pinID, ioBuff)
                                                                       //    }
    }
    va_end(argList);
    Serial.println("----------------EXITING IN TIME SERIES CALLER");
}

static void trigerCaller(int argCount, ...) //callback is digital write or red
{
    va_list argList;
    va_start(argList, argCount);

    //  long* val = va_arg(argList, long*);
    //  long* triger = va_arg(argList, long*);
    long *params = va_arg(argList, long *);
    void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...));

    if (params[1] == params[0])
    {
        Serial.println("TRIGERED");
        callback(2, va_arg(argList, byte *), va_arg(argList, char *)); // callback(2, pinID, ioBuff)
    }
    else
    {
        Serial.println("NOT TRIGERED");
    }
    va_end(argList);
}

static void pwmCaller(int argCount, ...) //callback is digital write or red
{
    va_list argList;
    va_start(argList, argCount);
    long *params = va_arg(argList, long *);
    byte *pinId = va_arg(argList, byte *);

    if (*pinId == 16 || *pinId == 3 || *pinId == 1)
    {
        Serial.println("ERROR: selected pin not support PWM ");
    }
    else
    {
        if (params[0] > 1023)
        {
            params[0] = 1023;
        }
        analogWrite(*pinId, params[0]);
    }
    //void (*callback)(int, ...) = va_arg(argList, void (*)(int, ...);
    //long* params, void (*callback)(void*, void*), void* dtParams, void* data

    //  if (pParams == NULL)
    //  {
    //    Serial.println("ERROR: pwm params are NULL");
    //    return;
    //  }
}
#endif

#if WATER_LEVEL

#endif

#if LIGHT_CONTROL

extern bool lightControlConfigured = false;

typedef struct
{
    uint8_t hours;
    uint8_t minutes;
} timeOfTheDay;

// typedef struct
// {
//     uint8_t currentLightLevel;
//     uint8_t targetLightLevel;
//     timeOfTheDay currentTime;
//     uint8_t lightMode;
//     uint8_t lightIntensityMap[96]
//      = {
//         0, 0, 0, 0,
//         0, 0, 0, 0,
//         0, 0, 0, 0,
//         0, 0, 0, 0,
//         0, 1, 2, 3,
//         4, 5, 9, 13,
//         14, 15, 15, 16,
//         18, 20, 22, 24,
//         28, 32, 36, 40,
//         44, 46, 50, 56,
//         62, 68, 74, 80,
//         86, 92, 98, 100,
//         100, 100, 100, 100,
//         100, 100, 100, 100,
//         100, 94, 88, 82,
//         76, 70, 64, 58,
//         52, 46, 40, 36,
//         32, 28, 24, 20,
//         18, 17, 16, 15,
//         14, 13, 12, 11,
//         10, 10, 5, 5,
//         5, 4, 3, 2,
//         1, 0, 0, 0,
//         0, 0, 0, 0
//     };

// } lightControlCfg;

// extern lightControlCfg _lightControlCfg;

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

extern bool nutritionControlConfigured = false;

extern uint8_t pwmPins[] = {5, 4, 0, 2, 14, 12, 13, 15};

extern uint8_t nutritionPumpsPins[N_DISPENSERS];
// typedef struct
// {
//     uint8_t nutritionMode;
//     uint8_t targetConcentration;
//     uint8_t currentConcentration;
//     uint8_t controlPin;
// } nutritionControlCfg;

//extern nutritionControlCfg _nutritionControlCfg[N_DISPENSERS];
#endif

//conn type
extern bool mqttClientFlag = false;
extern bool httpClientFlag = false;

//Mqtt conf

//mqtt topics
extern char cnfTopic[64] = "asd";
extern char dataTopic[64] = "asd";

//net structs

extern bool isSrvConfigured = false;
// typedef struct
// {
//     char mqttUser[32];
//     char mqttPass[32];
//     char mqttSrv[64];
//     char mqttPort[6];
// } mqtt_params_t;

//Http conf
// typedef struct
// {
//     char httpSrv[64];
//     char httpPort[6];
//     char httpToken[128];
// } http_params_t;

extern mqtt_params_t mqttParams = {"", "", "", "1883"};
extern http_params_t httpParams = {"", "80", ""};

extern char macId[12];

extern char cfgTopicOut[12];
extern char cfgTopicIn[12];
