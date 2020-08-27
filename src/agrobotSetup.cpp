#include "agrobotSetup.h"

#if UNIFIED_CONTROLLER

#endif

#if WATER_LEVEL


#endif
bool srvCfgFileExists()
{
  if (SPIFFS.exists("/srv_cfg.json"))
  {
    Serial.println("---------------------------SRV FILE  EXISTS");
    return true;
  }
  Serial.println("---------------------------SRV FILE  NOT EXISTS");

  return false;
}
bool cfgFilesExists()
{

  if (srvCfgFileExists()) //TODO need to add for rest of cfg
  {

    Serial.println("---------------------------ALL  FILE  EXISTS");

    return true;
  }
  return false;
}

void configModeCallback(WiFiManager *myWiFiManager)
{
  Serial.println("Entered config mode");
  Serial.println(WiFi.softAPIP());
  //if you used auto generated SSID, print it
  Serial.println(myWiFiManager->getConfigPortalSSID());
  Serial.print("-------------------------------------->");
  // myWiFiManager->resetSettings();
  // ESP.reset();

  Serial.println("on faild");
}

void runAutoConnect()
{
}
void setupWifiManager()
{
  Serial.println("---------------------------------_>Enter in config");
  WiFiManager wifiManager;
  char customhtml[24] = "type=\"checkbox\"";
  strcat(customhtml, " checked");

  //  memset(httpToken, 0, SIZEOF_ARRAY(httpToken));

  if (reseteWifiSettings)
  {
    wifiManager.resetSettings();
  }

  WiFiManagerParameter mqttUserParam("mqtt_user", "mqtt user", mqttParams.mqttUser, 32);
  WiFiManagerParameter mqttPassParam("mqtt_pass", "mqtt pass", mqttParams.mqttPass, 32);
  WiFiManagerParameter mqttSrvParam("mqtt_srv", "mqtt srv", mqttParams.mqttSrv, 64); //for now is 64 length
  WiFiManagerParameter mqttPortParam("mqtt_port", "mqtt port", mqttParams.mqttPort, 6);

  WiFiManagerParameter httpSrvParam("http_srv", "http srv", httpParams.httpSrv, 64);
  WiFiManagerParameter httpPortParam("http_port", "http port", httpParams.httpPort, 6);
  WiFiManagerParameter httpTokenParam("http_token", "http token", httpParams.httpToken, 128); //for now is placed 128 token length

  wifiManager.addParameter(&mqttUserParam);
  wifiManager.addParameter(&mqttPassParam);
  wifiManager.addParameter(&mqttSrvParam);
  wifiManager.addParameter(&mqttPortParam);

  wifiManager.addParameter(&httpSrvParam);
  wifiManager.addParameter(&httpPortParam);
  wifiManager.addParameter(&httpTokenParam);

  wifiManager.setMinimumSignalQuality();

  wifiManager.setAPCallback(configModeCallback);

  wifiManager.setSaveConfigCallback(saveSrvCfgCallback);
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect("AutoConnectAP");

  if (!isSrvConfigured)
  {
    Serial.println("--------------------------------> ENTERING NON AUITOCONECT");
    if (!wifiManager.startConfigPortal())
    {
      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      // ESP.reset();
      delay(5000);
    }
  }
  else
  {
    Serial.println("--------------------------------> ENTERING NON AUITOCONECT");
    if (!wifiManager.autoConnect())
    {

      Serial.println("failed to connect and hit timeout");
      delay(3000);
      //reset and try again, or maybe put it to deep sleep
      ESP.reset();
      delay(5000);
    }
  }

  Serial.println("connected...yeey :)");

  strlcpy(mqttParams.mqttUser,
          mqttUserParam.getValue(),
          mqttUserParam.getValueLength());

  strlcpy(mqttParams.mqttPass,
          mqttPassParam.getValue(),
          mqttPassParam.getValueLength());

  strlcpy(mqttParams.mqttSrv,
          mqttSrvParam.getValue(),
          mqttSrvParam.getValueLength());

  strlcpy(mqttParams.mqttPort,
          mqttPortParam.getValue(),
          mqttPortParam.getValueLength());

  strlcpy(httpParams.httpSrv,
          httpSrvParam.getValue(),
          httpSrvParam.getValueLength());

  strlcpy(httpParams.httpPort,
          httpPortParam.getValue(),
          httpPortParam.getValueLength());

  strlcpy(httpParams.httpToken,
          httpTokenParam.getValue(),
          httpTokenParam.getValueLength());

  Serial.println("----------------------------------------------------------------------------SIZE");
  //Serial.println(httpTokenParam.getValueLength());

  Serial.println(httpTokenParam.getValueLength());
  Serial.println(strlen(httpTokenParam.getValue()));

  uint8_t mac[6]; //changed from byte
  WiFi.macAddress(mac);
  byteArrToStr(mac, WL_MAC_ADDR_LENGTH, macId);
}

void setupMqtt(PubSubClient *mqttClient) //TODO refact
{
  // mqttClient.set
  mqttClient->setServer(WiFi.gatewayIP(), 1883); //TODO move to another function
  mqttClient->setCallback(dataCallback);
}

void saveSrvCfgCallback()
{
  shouldSaveSrvCfg = true;
}

void resetParamFlags()
{
}

void setCfgFlag(int8_t addr, int8_t flag) //changed from byte
{
}
