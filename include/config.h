 #ifndef AGROBOT_CONFIG
 #define AGROBOT CONFIG
#pragma once //TODO ??

 
 #include <stdint.h>


//Modules configs

#define UNIFIED_CONTROLLER 1
#define WATER_LEVEL 0
#define LIGHT_CONTROL 0
#define NUTRITION_CONTROL 0

//Helping macroses
//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))



#define RESET_CONFIG 0
#define FORMAT_FLASH 1

//Unified controller params

//Setup vars 



#if UNIFIED_CONTROLLER


#define DIGITAL_PIN 1
#define ANALOG_PIN 2

//data type
#define INPUT_DATA 1
#define OUTPUT_DATA 2

//behavior
#define TIME_SERIES_BEHAVIOR 1 //read periodical
#define TRIGER_BEHAVIOR 2//input as a trieger
#define PWM_BEHAVIOR 3

#define N_PINS 14



//FS Flash memmory

//Water level module configs

#elif WATER_LEVEL

#define HAS_WATER_FLOW_IN 1
#define HAS_WATER_FLOW_OUT 0

#define OPEN_WATER_GATE 100
#define HALF_OPEN_WATER_GATE  50
#define CLOSE_WATER_GATE 0

#define WATER_LEVEL_DRIFT_PERCENTS 4
//#define WATER_LEVEL_DRIFT_RAW 24000
#define WATER_LEVEL_DRIFT_RAW 12000


#if HAS_WATER_FLOW_IN

#endif

#if HAS_WATER_FLOW_OUT

#endif



//Light control module config
#elif LIGHT_CONTROL


//Light modes
#define OFF 0
#define SOLAR_MODE 1
#define TIMER 2
#define CONTINUOUS 3


#elif NUTRITION_CONTROL


#define PERIODIC 1
#define RELATIVE 2

#define DISPENSER_JSON_SIZE 40

#define N_DISPENSERS 2 //need to be lower thant the MAX_N_PUMPS
#define MAX_N_DISPENSERS 8
#define MIN_N_DISPENSERS 1

#endif




//types of io pins
//pin type
//#define EMPTY_CFG 0
#define EMPTY_CFG -1

//input proccesing

//pins arr



#endif