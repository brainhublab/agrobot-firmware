#ifndef AGROBOT_CONNECTION_H
#define AGROBOT_CONNECTION_H
//#pragma once //TODO ??

#include <PubSubClient.h>

#include "agrobotShared.h"

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

//wifi shared vars

extern mqtt_params_t mqttParams;
extern http_params_t httpParams;

void publishErrorMessage();
void publishSuccessMessage(char *sucMsg);
void reconnectMqtt(PubSubClient *);

#endif