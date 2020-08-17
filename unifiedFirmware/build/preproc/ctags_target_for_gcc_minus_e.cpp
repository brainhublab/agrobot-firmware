# 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
//#include<Arduino.h>
# 3 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2

# 5 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2

# 7 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2
# 8 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2

//ESP Web Server Library to host a web page
# 11 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2
# 12 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2
# 13 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2

# 15 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2
# 16 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2

# 18 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino" 2
# 45 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
char _errMsg[60];


//const size_t flagsCfgCapacity = JSON_OBJECT_SIZE(2) + 50;
//DynamicJsonDocument flagsJsonCfg(flagsCfgCapacity);

/*const size_t wifiCfgCapacity = JSON_OBJECT_SIZE(4) + 190;
  DynamicJsonDocument wifiJsonCfg(wifiCfgCapacity);*/

//const size_t pinsCfgCapacity = 11 * JSON_ARRAY_SIZE(4) + 11 * JSON_OBJECT_SIZE(7) + JSON_OBJECT_SIZE(12) + 890;
//DynamicJsonDocument pinsJsonCfg(pinsCfgCapacity);
//StaticJsonDocument<pinsCfgCapacity> pinsJsonCfg;

WiFiClient espClient;
PubSubClient mqttClient(espClient);

bool shouldSaveSrvCfg = false;

long lastMsg = 0;
char msg[50];
int value = 0;



//bool isConfigured = false;
int loopPinId = 0;
bool loopSetup = true;



void setup(void)
{

  /* while (WiFi.status() != WL_CONNECTED)
     {
     delay(500);
    // Serial.print(".");
    }*/

  Serial.begin(115200);

//  if (!SPIFFS.begin())
//  {
//    Serial.println("ERRPR: Failed to mount FS");
//  }
//
//  if (RESET_CONFIG)
//  {
//    resetConfig();
//    if (FORMAT_FLASH)
//    {
//      if (SPIFFS.format())
//      {
//        Serial.println("formated file system");
//      }
//    }
//
//  }
//
//  if (!srvCfgFileExists())
//  {
//    initSrvCfgFile();
//  }
//  else
//  {
//    readSrvCfgFile();
//  }
//  if (!isSrvConfigured)
//  {
//    setupWifiManager();
//  }
//  else
//  {
//    // setupAutoConnection();
//    readSrvCfgFile();
//  }
//  if (shouldSaveSrvCfg)
//  {
//    saveSrvParams(&mqttParams, &httpParams, true);
//
//  }
# 149 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
  mcuType = 3;
# 158 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/unifiedFirmware.ino"
  // initCfgFiles();
  //  setupCfgFiles();

  // initCfgFiles();
  // initIO();


  //mqttPass
  //reconnectMqtt();

  Serial.println("-------------------END SETUP");
}

void loop(void)
{
    Serial.println("------------------------------>");
    delay(20);
  Serial.print(loopPinId);
  if(loopSetup)
  {
//      callibrateMinMaxLevel();
      loopSetup = false;

  }
//  proccesWaterLevel();

  //  Serial.println("------------------------------ ENTERING LOOP");
  //  if (loopPinId < N_PINS)
  //  {
  //    if (1)
  //    {
  //      Serial.print(loopPinId);
  //
  //      Serial.println("------------------------------ ПРОЦеССИНГ LOOP");
  //      processPin(&(_managedPins[loopPinId]));
  //
  //    }
  //    loopPinId ++;
  //  }
  //  else
  //  {
  //    loopPinId = 0;
  //  }

  // delay(5000);


  Serial.println("printed from CODE");
}
# 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/connection.ino"

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
//      if (!pinsCfgFileExists()) //TODO rewrite
//      {
//        mqttClient.publish(cfgTopicOut, 0);
//        mqttClient.subscribe(cfgTopicIn);
//      }
//      else
//      {
//
//      }

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
# 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/helpers.ino"

void byteArrToStr(byte* arr, unsigned int len, char outStr[])
{
  //char outStr[len * 2];
  for (unsigned int i = 0; i < len; i++)
  {
    byte n1 = (arr[i] >> 4) & 0x0F;
    byte n2 = (arr[i] >> 0) & 0x0F;
    outStr[i * 2 + 0] = n1 < 0xA ? '0' + n1 : 'A' + n1 - 0xA;
    outStr[i * 2 + 1] = n2 < 0xA ? '0' + n2 : 'A' + n2 - 0xA;
  }
 // outStr[len * 2] = '\0';
 // return outStr;
}




void generateWhoAmi()
{


}

double mapDouble(double x, double inMin, double inMax, double outMin, double outMax)
{
  return (x-inMin) * (outMax - outMin) / (inMax - inMin) + outMin;
}

double valueToPercentsOf(double inp, double maxVal)
{
  return 100 / (maxVal /inp);

}
# 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"


char* getPinUID(byte index)
{

}

void writeParam(byte addr, byte param)
{


}

void resetConfig()
{
  Serial.println("Reseting all configs");

}
void loadCfgFiles()
{
  //  readPinsConfig(); //TODO rewrite with defines
  readSrvCfgFile();
}

void initIO()
{

}

void initSrvCfgFile()
{
  if (SPIFFS.exists("/srv_cfg.json"))
  {
    Serial.println("Warning: wifi config file exists You need to reset params first");
  }
  else
  {
    // File mqttCfgFile = SPIFFS.open("/main_cfg.json", "w");
    // flagsCfgFile.close();
    saveSrvParams(&mqttParams, &httpParams, false);
  }

}


void saveSrvParams(mqtt_params_t* mqttParamsCfg, http_params_t* httpParamsCfg, bool isConfigured)
{

  File srvCfgFile = SPIFFS.open("/srv_cfg.json", "w");
  if (srvCfgFile)
  {
    Serial.println("Initializing wifi file");
    // const size_t mqttCfgCapacity = JSON_OBJECT_SIZE(3) + 110;

    const size_t srvCfgCapacity = ((8) * sizeof(ArduinoJson6161_11::VariantSlot));
    DynamicJsonDocument srvJsonCfgOut(srvCfgCapacity);

    srvJsonCfgOut["isConfigured"] = isConfigured;
    srvJsonCfgOut["mqttUser"] = mqttParamsCfg->mqttUser;
    srvJsonCfgOut["mqttPass"] = mqttParamsCfg->mqttPass;
    srvJsonCfgOut["mqttSrv"] = mqttParamsCfg->mqttSrv;
    srvJsonCfgOut["mqttPort"] = mqttParamsCfg->mqttPort;

    srvJsonCfgOut["httpSrv"] = httpParamsCfg->httpSrv;
    srvJsonCfgOut["httpPort"] = httpParamsCfg->httpPort;
    srvJsonCfgOut["httpToken"] = httpParamsCfg->httpToken;


    serializeJson(srvJsonCfgOut, Serial);
    if (serializeJson(srvJsonCfgOut, srvCfgFile) == 0)
    {
      Serial.println(((reinterpret_cast<const __FlashStringHelper *>((__extension__({static const char __c[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "io.ino" "." "72" "." "237" "\", \"aSM\", @progbits, 1 #"))) = ("ERROR: Failed to write to srvCfgFile"); &__c[0];}))))));
    }
  }
  srvCfgFile.close();

}

void readSrvCfgFile()
{
  Serial.println("-----------------------------> READING SRV FILE");

  if (SPIFFS.exists("/srv_cfg.json"))
  {
    File srvCfgFile = SPIFFS.open("/srv_cfg.json", "r");
    if (srvCfgFile)
    {
      Serial.println("Reading mqtt config ...");
      const size_t srvCfgCapacity = ((8) * sizeof(ArduinoJson6161_11::VariantSlot)) + 460;
      DynamicJsonDocument srvJsonCfgIn(srvCfgCapacity);

      DeserializationError err = deserializeJson(srvJsonCfgIn, srvCfgFile);
      if (err)
      {
        Serial.println(((reinterpret_cast<const __FlashStringHelper *>((__extension__({static const char __c[] __attribute__((__aligned__(4))) __attribute__((section( "\".irom0.pstr." "io.ino" "." "95" "." "238" "\", \"aSM\", @progbits, 1 #"))) = ("ERROR: failed to read file, using default configuration"); &__c[0];}))))));
      }



      isSrvConfigured = srvJsonCfgIn["isConfigured"];

      strlcpy(mqttParams.mqttUser,
              srvJsonCfgIn["mqttUser"] | "exampleMqttUser",
              sizeof(mqttParams.mqttUser));
      strlcpy(mqttParams.mqttPass,
              srvJsonCfgIn["mqttPass"] | "exampleMqttPass",
              sizeof(mqttParams.mqttPass));
      strlcpy(mqttParams.mqttSrv,
              srvJsonCfgIn["mqttSrv"] | "example.com",
              sizeof(mqttParams.mqttSrv));
      strlcpy(mqttParams.mqttPort,
              srvJsonCfgIn["mqttPort"] | "1883",
              sizeof( mqttParams.mqttPort));


      strlcpy(httpParams.httpSrv,
              srvJsonCfgIn["httpSrv"] | "example.com",
              sizeof(httpParams.httpSrv));
      strlcpy(httpParams.httpPort,
              srvJsonCfgIn["httpPort"] | "80",
              sizeof(httpParams.httpPort));
      strlcpy(httpParams.httpToken,
              srvJsonCfgIn["httpToken"] | "exampleToken",
              sizeof(httpParams.httpToken));

      serializeJson(srvJsonCfgIn, Serial);


    }
    srvCfgFile.close();
  }
  else
  {
    Serial.println("ERROR mqttCfg file does not exists");
  }
}


void initCfgFile()
{
  if (SPIFFS.exists("/pins_cfg.json"))
  {
    Serial.print("WARNING: pins config file already exists  You need to reset params first");
  }
  else
  {
    Serial.println("Initializing pins");
    //setPinsCfgFile(_managedPins);







    //saveLightControlCfgFile();




  }
}
# 572 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void saveLightControlCfgFile(lightControlCfg* lcCfg, bool isConfigured)
{
  File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json", "w");

  if (lightControlCfgFile)
  {
    Serial.println("Initializing light control config file for writing ...");

    const size_t lightControlCfgCapacity = ((96) * sizeof(ArduinoJson6161_11::VariantSlot)) + ((7) * sizeof(ArduinoJson6161_11::VariantSlot));
    DynamicJsonDocument lightControlJsonCfgOut(lightControlCfgCapacity);

    lightControlJsonCfgOut["mcuType"] = mcuType; // TODO refactor
    lightControlJsonCfgOut["title"] = "light control ID:" + (String)macId;
    lightControlJsonCfgOut["isConfigured"] = isConfigured;

    lightControlJsonCfgOut["lightMode"] = lcCfg->lightMode;
    lightControlJsonCfgOut["targetLightLevel"] = lcCfg->targetLightLevel;
    //lightControlJsonCfgOut["currentTime"] = lcCfg->currentTime;
    char tmpTime[6];
    snprintf(tmpTime, 6,
             "%d:%d",
             lcCfg->currentTime.hours,
             lcCfg->currentTime.minutes);
    lightControlJsonCfgOut["currentTime"] = tmpTime;

    JsonArray lightIntensityMap = lightControlJsonCfgOut.createNestedArray("lightIntensityMap");
    for (byte i = 0; i < (sizeof (lcCfg->lightIntensityMap) / sizeof (lcCfg->lightIntensityMap[0])); i++)
    {
      lightIntensityMap[i] = lcCfg->lightIntensityMap[i];
    }

    if (serializeJson(lightControlJsonCfgOut, lightControlCfgFile) == 0) // TODO write it for each
    {
      Serial.println("ERROR: failed to write light control config");
    }
    lightControlCfgFile.close();
  }
  else
  {
    Serial.println("ERROR: Failed to open light control config for writing");

  }



}

void readLightControlCfgFile()
{
  if (SPIFFS.exists("/light_control_cfg.json"))
  {
    File lightControlCfgFile = SPIFFS.open("/light_control_cfg.json" , "r");

    if (lightControlCfgFile)
    {
      Serial.println("Reading light control config file ...");

      const size_t lightControlCfgCapacity = ((96) * sizeof(ArduinoJson6161_11::VariantSlot)) + ((6) * sizeof(ArduinoJson6161_11::VariantSlot)) + 150;
      DynamicJsonDocument lightControlJsonCfgIn(lightControlCfgCapacity);

      DeserializationError err = deserializeJson(lightControlJsonCfgIn, lightControlCfgFile);

      if (err)
      {
        Serial.println("ERROR: failed to read file, using default configuration");
      }

      lightControlConfigured = lightControlJsonCfgIn["isConfigured"];
      _lightControlCfg.lightMode = lightControlJsonCfgIn["lightMode"];
      _lightControlCfg.targetLightLevel = lightControlJsonCfgIn["targetLightLevel"];
      //      _lightControlCfg.currentDateTime = lightControlJsonCfgIn["currentDateTime"];
      if (2 != sscanf(lightControlJsonCfgIn["currentDateTime"],
                      "%hhu%*[^0123456789]%hhu",
                      &_lightControlCfg.currentTime.hours,
                      &_lightControlCfg.currentTime.minutes))
      {
        Serial.println("ERROR: Cannot extract current time please check formating");
      }
      JsonArray lightIntensityMap = lightControlJsonCfgIn["lightIntensityMap"];
      for(byte i=0; i<(sizeof (_lightControlCfg.lightIntensityMap) / sizeof (_lightControlCfg.lightIntensityMap[0])); i++)
      {
        _lightControlCfg.lightIntensityMap[i] = lightIntensityMap[i];
      }
    }
    lightControlCfgFile.close();

  }
  else
  {
    Serial.print("ERROR: no such sonfig file with name:");
    Serial.println("/light_control_cfg.json");
  }

}
# 764 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/io.ino"
void dataCallback(char* topic, byte* payload, unsigned int length)
{

}
# 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/methods.ino"
# 127 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/methods.ino"
void proecessLightControl()
{

}

void correctLightLevel()
{

}
# 1 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
# 216 "/home/h3lgi/code/agroBotFirmware/unifiedFirmware/setup.ino"
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

void configModeCallback (WiFiManager * myWiFiManager)
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
  WiFiManagerParameter httpTokenParam("http_token", "http token", httpParams.httpToken, 128);//for now is placed 128 token length


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

  Serial.println( httpTokenParam.getValueLength());
  Serial.println( strlen(httpTokenParam.getValue()));

  byte mac[6];
  WiFi.macAddress(mac);
  byteArrToStr(mac, 6, macId);


}


void setupMqtt()
{
  // mqttClient.set
  mqttClient.setServer(WiFi.gatewayIP(), 1883); //TODO move to another function
  mqttClient.setCallback(dataCallback);
}

void saveSrvCfgCallback()
{
  shouldSaveSrvCfg = true;
}



void resetParamFlags()
{

}

void setCfgFlag(byte addr, byte flag)
{
}
