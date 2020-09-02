 #ifndef AGROBOT_CONFIG
 #define AGROBOT CONFIG
//#pragma once //TODO ??

 
 #include <stdint.h>


//Modules configs

//#define MCU_TYPE 1 //TODO change to shared
#define UNIFIED_CONTROLLER 1
#define WATER_LEVEL 0
#define LIGHT_CONTROL 0
#define NUTRITION_CONTROL 0

//Helping macroses
//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))



#define RESET_CONFIG 1
#define FORMAT_FLASH 1

//Unified controller params

//Setup vars 



//#if UNIFIED_CONTROLLER


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

//#elif WATER_LEVEL

#define HAS_WATER_FLOW_IN 1
#define HAS_WATER_FLOW_OUT 1

#define OPEN_WATER_GATE 100
#define HALF_OPEN_WATER_GATE  50
#define CLOSE_WATER_GATE 0

#define WATER_LEVEL_DRIFT_PERCENTS 4
//#define WATER_LEVEL_DRIFT_RAW 24000
#define WATER_LEVEL_DRIFT_RAW 12000

//class vars
#define LOADCELL_DOUT_PIN 16
#define LOADCELL_SCK_PIN 5
#define WATER_GATE_SERVO_PIN 0 //ТОДО


#define WATER_TANK_THRESHOLD 5 //TODO make it more cleaner with proper threshold

#if HAS_WATER_FLOW_IN
#define WATER_FLOW_IN_PIN 4

#endif

#if HAS_WATER_FLOW_OUT
#define WATER_FLOW_OUT_PIN 14 //TODO

#endif



//Light control module config
//#elif LIGHT_CONTROL


//Light modes
#define OFF 0
#define SOLAR_MODE 1
#define TIMER 2
#define CONTINUOUS 3

#define LIGHT_CONTROL_N_PINS 2 //TODO change in real tests!!!

#define IN_1_PIN 23
#define IN_2_PIN 23
#define IN_3_PIN 2
#define IN_4_PIN 13


//#elif NUTRITION_CONTROL

#define PERIODIC 1
#define RELATIVE 2

#define DISPENSER_JSON_SIZE 40

#define N_DISPENSERS 2 //need to be lower thant the MAX_N_PUMPS
#define MAX_N_DISPENSERS 8
#define MIN_N_DISPENSERS 1

//#endif




//types of io pins
//pin type
//#define EMPTY_CFG 0
#define EMPTY_CFG -1

//input proccesing

//pins arr



#endif