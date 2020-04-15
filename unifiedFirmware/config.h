
//Modules configs

#define UNIFIED_CONTROLLER 0
#define WATER_LEVEL 0
#define LIGHT_CONTROL 0
#define NUTRITION_CONTROL 1

//Helping macroses
//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))



#define RESET_CONFIG 0
#define FORMAT_FLASH 1
bool reseteWifiSettings = 0;

byte mcuType = 0;
//Unified controller params

#if UNIFIED_CONTROLLER
bool pinsConfigured = false;

typedef struct
{
  bool isActive;
  byte id;
  byte type;
  byte dataType;
  byte behavior;
  byte processing;
  void (*behaviorCallback)(int, ...);
  long behaviorParams[4];
  long dataTypeParams[4];
  byte dataBufferTX[64];
  byte dataBufferRX[64];
  //  char dataBufferTX[4];
  //  char dataBufferRX[4];
} pinConfig;

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

//byte _pinout[N_PINS] = {17, 16, 14, 12, 13, 15, 2, 0, 4, 5, 3, 1}; //note 16, 3, 1, 10, 9 is high on boot
byte _pinout[N_PINS] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot and 10/9 are not recomended

//byte _spiPinsIds[4] = {5, 6, 7, 8};
pinConfig _managedPins[N_PINS];


//ioTimeOut for transmissions
uint16_t ioTimeout = 100;


//FS Flash memmory



//Water level module configs

#elif WATER_LEVEL

bool waterLevelConfigured = false;
typedef struct
{
  byte valveCurrent;
  byte valveTarget;
  byte levelCurrent;
  byte levelTarget;
  int waterFlowIn;
  int waterFlowOut;
} waterLevelCfg;


waterLevelCfg _waterLevel;

//Light control module config
#elif LIGHT_CONTROL

bool lightControlConfigured = false;

//Light modes 
#define OFF 0
#define SOLAR_MODE 1
#define TIMER 2
#define CONTINUOUS 3


typedef struct 
{
  byte currentLightLevel;
  byte targetLightLevel;
  byte currentDateTime;
  byte lightMode;
}lightControlCfg;

lightControlCfg _lightControlCfg;


//Nutrition controll module config
#elif NUTRITION_CONTROL

bool nutritionControlConfigured = false;

#define PERIODIC 1
#define RELATIVE 2

#define DISPENSER_JSON_SIZE 40

#define N_DISPENSERS 2 //need to be lower thant the MAX_N_PUMPS
#define MAX_N_DISPENSERS 8
#define MIN_N_DISPENSERS 1
byte pwmPins[] = {5, 4, 0, 2, 14, 12, 13, 15} ;


byte nutritionPumpsPins[N_DISPENSERS];
typedef struct 
{
  byte nutritionMode;
  byte targetConcentration;
  byte currentConcentration;
  byte controlPin;
}nutritionControlCfg;

nutritionControlCfg _nutritionControlCfg[N_DISPENSERS];
#endif




//types of io pins
//pin type
#define EMPTY_CFG 0

//input proccesing

//pins arr


//conn type
bool mqttClientFlag = false;
bool httpClientFlag = false;

//Mqtt conf

//mqtt topics
char cnfTopic[64] = "asd";
char dataTopic[64] = "asd";

//net structs

bool isSrvConfigured = false;
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

mqtt_params_t mqttParams = {"", "", "", "1883"};
http_params_t httpParams = {"", "80", ""};


char macId[12];

char cfgTopicOut[12];
char cfgTopicIn[12];
