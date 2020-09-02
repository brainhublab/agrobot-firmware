#ifndef UNIFIED_CONTROLLER_H
#define UNIFIED_CONTROLLER_H
#include <functional>

#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <stdio.h>

#include <ArduinoJson.h>

#include "config.h"
#include "agrobotShared.h"

typedef struct
{
    bool isActive;
    uint8_t id;
    uint8_t type;
    uint8_t dataType;
    uint8_t behavior;
    uint8_t processing;
    void (*behaviorCallback)(int, ...);
    //std::function<void(int, ...)> behaviorCallback;
    long behaviorParams[4];
    long dataTypeParams[4];
    uint8_t dataBufferTX[64];
    uint8_t dataBufferRX[64];
    //  char dataBufferTX[4];
    //  char dataBufferRX[4];
} pinConfig;

class UnifiedController
{
public:
    UnifiedController();

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

    void savePinsCfgFile();
    void readPinsConfig();
    void processPin(pinConfig *);

    static void readDigitalPin(int, ...);
    static void writeDigitalPin(int, ...);
    static void timeSeriesCaller(int, ...);
    static void trigerCaller(int, ...);
    static void pwmCaller(int, ...);

    bool unifiedControllerIsConfigured;
    bool pinsConfigured; //=false

    //byte _pinout[N_PINS] = {17, 16, 14, 12, 13, 15, 2, 0, 4, 5, 3, 1}; //note 16, 3, 1, 10, 9 is high on boot
    uint8_t _pinout[N_PINS]; //= {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot and 10/9 are not recomended

    //byte _spiPinsIds[4] = {5, 6, 7, 8};
    pinConfig _managedPins[N_PINS];

    //ioTimeOut for transmissions
    unsigned int ioTimeout; //= 100; //uint16_t
};

#endif