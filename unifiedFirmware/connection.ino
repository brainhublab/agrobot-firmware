
void publishErrorMessage()
{

}

void publishSuccessMessage(char* sucMsg)
{

}

void reconnectMqtt()
{
  while (!mqttClient.connected())
  {
    Serial.println("Attempting MQTT connection ...");

    if (mqttClient.connect(macId, mqttParams.mqttUser, mqttParams.mqttPass))
    {
      Serial.println("Mqtt connected");
      if (!pinsCfgFileExists()) //TODO rewrite
      {
        mqttClient.publish(cfgTopicOut, 0);
        mqttClient.subscribe(cfgTopicIn);
      }
      else
      {

      }

    }
    else
    {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
