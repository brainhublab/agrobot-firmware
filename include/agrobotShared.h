#ifndef AGROBOT_SHARED_H
#define AGROBOT_SHARED_H
#include <Arduino.h>

#include <stdint.h>
#include "config.h"

#define TITLE_BUFFER_SIZE 64
#define ERR_MSG_BUFFER_SIZE 64
#define PAYLOAD_BUFFER_SIZE 32

/* Error JSON  messge
{
  "status":200,
  "err_type": 1,
  "details":"qwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqw"
}
*/

// const size_t errMsgCapacity = JSON_OBJECT_SIZE(3) + 100;
// StaticJsonDocument<errMsgCapacity> errJsonMsg;
typedef struct
{
    int status;
    uint8_t errType;
    char details[ERR_MSG_BUFFER_SIZE];
} errMsg_t;

/* data JSON message 
{
  "payload":100100123456.23456,
}
*/
// const size_t dataMsgCapacity = JSON_OBJECT_SIZE(1) + 10;
// StaticJsonDocument<dataMsgCapacity> inJsonMsg;
// StaticJsonDocument<dataMsgCapacity> outJsonMsg;
typedef struct
{
    unsigned long msgId;
    char payload[PAYLOAD_BUFFER_SIZE];
} dataMsg_t;
/*healthcheck message 
 {
    "is_configured": false,
    "signal_streigth": 1234567890,
    "battery_level": -1,
    "self_check":false,
}
*/
// const size_t healthcheckMsgCapacity = JSON_OBJECT_SIZE(4) + 70;
// StaticJsonDocument<healthcheckMsgCapacity> healtcheckJsonMsg;
typedef struct
{
    bool isConfigured;
    long signalStreight;
    int8_t batteryLevel;
    int selfCheckCode;
} healtcheck_t;
/*whoami JSON message 
{
    "mcu_type": 100,
    "title": "qwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqwqw",
    "macAddr": "10:02:b5:a7:c1:e1",
}
*/
// const size_t whoamiMsgCapacity = JSON_OBJECT_SIZE(3) + 120;
// StaticJsonDocument<whoamiMsgCapacity> whoamiJsonMsg;

typedef struct
{
    char macAddr[12];
    uint8_t mcuType;
    char title[TITLE_BUFFER_SIZE];
} whoami_t;

extern errMsg_t errMsg;
extern dataMsg_t dataMsgIn;
extern dataMsg_t dataMsgOut;
extern healtcheck_t healtcheck;
extern whoami_t whoami;

//MCU type related vars
//file system vars
extern bool shouldSaveSrvCfg;
extern bool isSrvConfigured; // = false;

//MQTT topics
extern char configTopic[38];      // /controller/10:02:b5:a7:c1:e1/config/
extern char authTopic[18];        // /controller/auth/
extern char errTopic[36];         ///controller/10:02:b5:a7:c1:e1/config/
extern char healthCheckTopic[43]; ///controller/10:02:b5:a7:c1:e1/healthcheck/
extern char rootDataTopic[36];    // /controller/10:02:b5:a7:c1:e1/data/

#endif