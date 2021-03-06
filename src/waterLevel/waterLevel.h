#ifndef WATER_LEVEL_H
#define WATER_LEVEL_H
#include <HX711.h>
#include <PID_v1.h>
#include <Servo.h>
#include <stdint.h>

#include <FS.h> //this needs to be first, or it all crashes and burns...

#include <stdio.h>

#include <ArduinoJson.h>

#include "agrobotHelpers.h"
#include "config.h"
#include "agrobotShared.h"

#include "waterFlow/waterFlow.h"
//TODO migrate some of vars in config header
// static void ICACHE_RAM_ATTR wlFlowInPulseCounter();
// static void ICACHE_RAM_ATTR wlFlowOutPulseCounter();
typedef struct
{
    uint8_t gateCurrent;
    uint8_t gateTarget;
    uint8_t levelCurrent;
    uint8_t levelTarget;
    int waterFlowIn;
    int waterFlowOut;
} waterLevelCfg;

//methods
class WaterLevel
{
public:
    WaterLevel();

    void begin();

    void proccesWaterLevel();
    void correctWaterLevel();
    void callibrateMinMaxLevel();
    double getWaterLevelPercents();
    double getWaterLevelRawData();
    void setWaterLevelGate(double);

    void saveWaterLevelCfgFile();
    void readWaterLevelCfgFile();

    double waterLevelRawMax;
    double waterLevelRawMin;
    bool waterLevelConfigured;

    waterLevelCfg _waterLevel;

    // const uint8_t loadCellDoutPin;   // = 16; //TODO PIN IDS
    // const uint8_t loadCellSckPin;    // = 5;
    // const uint8_t waterGateServoPin; // = 0;
    //                                  //
    // const int waterTankThreshold;    // = 5; //TODO make it more cleaner with proper threshold

    //PID configuration and variables

    double wlPidInput;    // = 0.f;
    double wlPidOutput;   // = 0.f;
    double wlPidSetpoint; // = 0.f;

    //double Kp = 2, Ki = 5, Kd = 1;

    //Aggresive PID values //TODO PID params to conf header
    double wlAgKp;
    double wlAgKi;
    double wlAgKd;

    //conservative PID values
    double wlConsKp;
    double wlConsKi;
    double wlConsKd; // = 1,  = 0.05,  = 0.25

    HX711 waterLevelSensor;
    //PID waterLevelPid(&wlPidInput, &wlPidOutput, &wlPidSetpoint, wlConsKp, wlConsKi, wlConsKd, DIRECT);

    PID waterLevelPid; //(double *, double *, double *, double, double, double, int);

    Servo waterGateServo;

#if HAS_WATER_FLOW_IN
    WaterFlow waterFlowIn;
#endif

#if HAS_WATER_FLOW_OUT
    WaterFlow waterFlowOut;
#endif
};

#endif