//On board configs
//Helping macroses
//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))

#define RESET_CONFIG 1
#define FORMAT_FLASH 1
bool reseteWifiSettings = 0;

uint8_t i2cAddresses[127];
uint8_t i2cBytesToRead[127];
int reqRegisters[127];


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
  //char* inData;
  uint8_t addr; //TODO make it array for multiple addressess
  int reqRegister; //TODO maybe multiple register to request
  uint8_t bytesToRead;
} i2cParams;

typedef struct
{
 int param;
} spiParams;

#define PIN_UID_SIZE 8

typedef struct
{
  bool isActive;
  byte id;
  byte type;
  byte dataType;
  byte behavior;
  byte processing;
  char UID[PIN_UID_SIZE];
  //void (*processingCallback)(long*, void(*)(void*, void*), void*, void*);
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
#define I2C_PINS 3
#define SPI_PINS 4

//data type
#define INPUT_DATA 1
#define OUTPUT_DATA 2
//#define INPUT_I2C 3 //TODO onlu IN OUT needed
//#define OUTPUT_I2C 4
//#define INPUT_SPI 5
//#define OUTPUT_SPI 6

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
#define SDA_PIN 4
#define SCL_PIN 5

#define HSCLK_PIN 14
#define HMISO_PIN 12
#define HMOSI_PIN 13
#define HCS_pin 15
//byte _pinout[N_PINS] = {17, 16, 14, 12, 13, 15, 2, 0, 4, 5, 3, 1}; //note 16, 3, 1, 10, 9 is high on boot
byte _pinout[N_PINS] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot and 10/9 are not recomended

//byte _spiPinsIds[4] = {5, 6, 7, 8};
pinConfig _managedPins[N_PINS];



//byte _i2cPinsIds[2] = {1, 2};
//byte _reservedPis[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//ioTimeOut for transmissions
uint16_t ioTimeout = 100;

byte slaveReceived = 0;

//SPI vars
char spiRxBuffer[32];
char spiTxBuffer[32];

static uint32_t spiSelectState = 0x00;
static uint32_t spiTransferState = 0x00;

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


//manager config
//default custom static IP
//char static_ip[16] = "10.0.1.56";
//char static_gw[16] = "10.0.1.1";
//char static_sn[16] = "255.255.255.0";

//Specialization configs

/*

   #define NODE_MCU_BOARD  1
  #define WE_MOS_D1_MINI_BOARD 2
  #define MCU_BOARD 2
  #if MCU_BOARD == NODE_MCU_BOARD
  #define N_PINS 14

  #define SDA_PIN 4
  #define SCL_PIN 5

  #define HSCLK_PIN 14
  #define HMISO_PIN 12
  #define HMOSI_PIN 13
  #define HCS_pin 15
  byte _pinout[N_PINS] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, A0}; //note 16, 3, 1, 10, 9 is high on boot
  //byte _spiPinsIds[4] = {5, 6, 7, 8};
  pinConfig _managedPins[N_PINS];
  #elif MCU_BOARD == WE_MOS_D1_MINI_BOARD
  #endif
*/
