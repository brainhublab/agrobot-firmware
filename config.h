//On board configs
//Helping macroses
//#define NELEMS(x)  (sizeof(x) / sizeof((x)[0]))
#define MEMBER_SIZE(type, member) sizeof(((type *)0)->member)

#define SIZEOF_ARRAY(x)  (sizeof (x) / sizeof (x[0]))

#define RESET_SETTINGS 0

struct mqttParams
{
  // char mqttUser[32];
  // char mqttPass[32];
};


#define PIN_UID_SIZE 8
struct pinConfig
{
  bool isActive;
  byte id;
  byte type;
  byte dataType;
  int behavior[2];
  byte processing;
  char UID[PIN_UID_SIZE];
  void (*processingCallback)(void);
  char* dataBuffer;
};

struct outputParams
{
  char* data;
  byte pinId;

};
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
#define INPUT_I2C 3
#define OUTPUT_I2C 4
#define INPUT_SPI 5
#define OUTPUT_SPI 6

//behavior
#define TIME_SERIES_PIN 1 //read periodical
#define TRIGER_PIN 2//input as a trieger
#define PWM_IO 3

//input proccesing

//output procesig
#define PID_IO 1
#define FADE_IO 2

//pins config

//pins arr
#define N_PINS 14
#define SDA_PIN 4
#define SCL_PIN 5

#define HSCLK_PIN 14
#define HMISO_PIN 12
#define HMOSI_PIN 13
#define HCS_pin 15
byte _pinout[N_PINS] = {16, 5, 4, 0, 2, 14, 12, 13, 15, 3, 1, 9, 10, 17}; //note 16, 3, 1, 10, 9 is high on boot
//byte _spiPinsIds[4] = {5, 6, 7, 8};
pinConfig _managedPins[N_PINS];

//byte _i2cPinsIds[2] = {1, 2};
//byte _reservedPis[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

//ioTimeOut for transmissions
uint16_t ioTimeout = 100;

byte slaveReceived = 0;


//FS Flash memmory

bool reseteWifiSettings = false;

//Mqtt conf
char mqttUser[32];
char mqttPass[32];
char* mqttServer;

byte macId[6];

char cfgTopicOut[12];
char cfgTopicIn[12];


//manager config
//default custom static IP
//char static_ip[16] = "10.0.1.56";
//char static_gw[16] = "10.0.1.1";
//char static_sn[16] = "255.255.255.0";

//Specialization configs
