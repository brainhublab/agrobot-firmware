
//On board configs
//Helping macroses
//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))




#define RESET_CONFIG 0
#define FORMAT_FLASH 0
 bool reseteWifiSettings = 0;



//behavior params

typedef struct
{
  unsigned long timerInterval;
  unsigned long previousMillis;
  

} timeSeriesParams;
typedef struct
{
  int dutyCycle;
} pwmParams;

typedef struct
{
  int triger;
  int value;
} trigerParams;

//data type params
typedef struct
{
  byte pinId;
  byte* data;
} digitalIOParams;




typedef struct
{
  bool isActive;
  byte id;
  byte type;
  byte dataType;
  byte behavior;
  byte processing;
  void (*behaviorCallback)(int, byte dataType, ...);
  long behaviorParams[4];
  long dataTypeParams[4];
  char dataBufferTX[64];
  char dataBufferRX[64];
} pinConfig;


 bool pinsConfigured = false;

//types of io pins
//pin type
#define EMPTY_CFG 0

#define DIGITAL_PIN 1
#define ANALOG_PIN 2

//data type
#define INPUT_DATA 1
#define OUTPUT_DATA 2

//behavior
#define TIME_SERIES_BEHAVIOR 1 //read periodical
#define TRIGER_BEHAVIOR 2//input as a trieger
#define PWM_BEHAVIOR 3

//input proccesing

//output procesig
#define PID_IO 1
#define FADE_IO 2


//pins arr

#define N_PINS 14

//byte _pinout[N_PINS] = {17, 16, 14, 12, 13, 15, 2, 0, 4, 5, 3, 1}; //note 16, 3, 1, 10, 9 is high on boot
 byte _pinout[N_PINS] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot and 10/9 are not recomended

//byte _spiPinsIds[4] = {5, 6, 7, 8};
pinConfig _managedPins[N_PINS];


//ioTimeOut for transmissions
 uint16_t ioTimeout = 100;

 byte slaveReceived = 0;

//FS Flash memmory


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

 bool ds18b20 = false;

 byte macId[6];

 char cfgTopicOut[12];
 char cfgTopicIn[12];
