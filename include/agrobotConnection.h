#ifndef AGROBOT_CONNECTION
#define AGROBOT_CONNECTION

#include <PubSubClient.h>

class AgrobotConnection
{
public:
    void publishErrorMessage();

    void publishSuccessMessage(char *sucMsg);

    void reconnectMqtt(PubSubClient *);
};

#endif