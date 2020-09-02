#include "agrobotShared.h"

extern errMsg_t errMsg = {0, 0, ""};
extern dataMsg_t dataMsgIn = {0, ""};
extern healtcheck_t healtcheck = {false, 0, -1, 0};
extern whoami_t whoami = {"", 0, ""};


//MCU type related vars
extern uint8_t mcuType = 0;
//file system vars
extern bool shouldSaveSrvCfg = false;
extern bool isSrvConfigured = false;
//extern char macId[12]={0};
