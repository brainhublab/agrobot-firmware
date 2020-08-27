#ifndef AGROBOT_CONNECTION_H
#define AGROBOT_CONNECTION_H
//#pragma once //TODO ??

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