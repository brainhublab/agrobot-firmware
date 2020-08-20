#ifndef AGROBOT_CONNECTION
#define AGROBOT_CONNECTION
#pragma once //TODO ??

#include "agrobotShared.h"


#include <PubSubClient.h>

class AgrobotConnection
{
public:
    void publishErrorMessage();

    void publishSuccessMessage(char *sucMsg);

    void reconnectMqtt(PubSubClient *);
};

#endif