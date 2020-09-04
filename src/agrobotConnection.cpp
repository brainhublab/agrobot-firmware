
#include <agrobotConnection.h>

extern mqtt_params_t mqttParams = {"", "", "", "1883"};
extern http_params_t httpParams = {"", "80", ""};

void publishErrorMessage()
{
}

void publishSuccessMessage(char *sucMsg)
{
}

void reconnectMqtt(PubSubClient *mqttClient)
{
  while (!mqttClient->connected())
  {
    Serial.println("Attempting MQTT connection ...");

    if (mqttClient->connect(whoami.macAddr, mqttParams.mqttUser, mqttParams.mqttPass))
    {
      Serial.println("Mqtt connected");

      const size_t whoamiCapacity = JSON_OBJECT_SIZE(3) + 120;
      StaticJsonDocument<whoamiCapacity> whoamiJson;

      whoamiJson["mac_addr"] = whoami.macAddr;
      whoamiJson["mcu_type"] = whoami.mcuType;
      whoamiJson["title"] = whoami.title;
      char whoamiBuffer[whoamiCapacity]; //TODO check measure func for array size
      size_t n = serializeJson(whoamiJson, whoamiBuffer);
      mqttClient->publish(authTopic, whoamiBuffer, n);
    }
    else
    {
      Serial.print("failed to connect MQTT client, rc=");
      Serial.print(mqttClient->state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
