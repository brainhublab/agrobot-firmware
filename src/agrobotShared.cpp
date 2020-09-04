#include "agrobotShared.h"

extern errMsg_t errMsg = {0, 0, ""};
extern dataMsg_t dataMsgIn = {0, ""};
extern healtcheck_t healtcheck = {false, 0, -1, 0};
extern whoami_t whoami = {"", 0, ""};


//MQTT topics
extern char configTopic[38] = "";      // /controller/10:02:b5:a7:c1:e1/config/
extern char authTopic[18] = "" ;       // /controller/auth/
extern char errTopic[37] = "";         ///controller/10:02:b5:a7:c1:e1/config/
extern char healthCheckTopic[43] = ""; ///controller/10:02:b5:a7:c1:e1/healthcheck/
extern char rootDataTopic[36] = "";    // /controller/10:02:b5:a7:c1:e1/data/

//extern char configTopic[38]


//MCU type related vars
extern uint8_t mcuType = 0;
//file system vars
extern bool shouldSaveSrvCfg = false;
extern bool isSrvConfigured = false;
//extern char macId[12]={0};
