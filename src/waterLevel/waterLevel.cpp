#include "waterLevel.h"

WaterLevel::WaterLevel() : waterLevelPid(&wlPidInput, &wlPidOutput, &wlPidSetpoint, wlConsKp, wlConsKi, wlConsKd, DIRECT) //TODO maybe not correct call
{
  this->waterLevelRawMax = 0.f;
  this->waterLevelRawMin = 0.f;
  this->waterLevelConfigured = false;

  this->_waterLevel = {0, 0, 0, 0, 0, 0};

  this->wlPidInput = 0.f;
  this->wlPidOutput = 0.f;
  this->wlPidSetpoint = 0.f;

  this->wlAgKp = 4.0;
  this->wlAgKi = 0.2;
  this->wlAgKd = 1.0;

  this->wlConsKp = 1.0;
  this->wlConsKi = 0.05;
  this->wlConsKd = 0.25;

 // this->waterLevelPid(&wlPidInput, &wlPidOutput, &wlPidSetpoint, wlConsKp, wlConsKi, wlConsKd, DIRECT); //TODO maybe not correct call

#if HAS_WATER_FLOW_IN
  this->wlFlowInCalibrationFactor = 4.5;
  this->wlFlowInPulseCount = 0;
  this->wlFlowInFlowRate = 0.0f;
  this->wlFlowInFlowMilliLitres = 0;
  this->wlFlowInFTotalMilliLitres = 0;
  this->wlFlowInOldTimer = 0;

#endif

#if HAS_WATER_FLOW_OUT
  this->wlFlowOutCalibrationFactor = 4.5;
  this->wlFlowOutPulseCount = 0;
  this->wlFlowOutFlowRate = 0.0f;
  this->wlFlowOutFlowMilliLitres = 0;
  this->wlFlowOutFTotalMilliLitres = 0;
  this->wlFlowOutOldTimer = 0;
#endif
}

void WaterLevel::proccesWaterLevel()
{

  correctWaterLevel();
}

void WaterLevel::correctWaterLevel()
{
  Serial.println("------------------Correction of waterLevel");
  wlPidInput = getWaterLevelPercents();
  Serial.println(wlPidInput);
  double gap = abs(wlPidSetpoint - wlPidInput);
  Serial.print("-------------- GAP: ");
  Serial.println(gap);
  if (gap < 10)
  {
    //operate gate by using conservative PID
    this->waterLevelPid.SetTunings(wlConsKp, wlConsKi, wlConsKd);
  }
  else
  {
    //operate gate by using agresive PID
    this->waterLevelPid.SetTunings(wlAgKp, wlAgKi, wlAgKd);
  }
  waterLevelPid.Compute();
  Serial.print("--------------PID OUT ");
  Serial.println(map((int)wlPidOutput, 0, 255, 0, 100));
  setWaterLevelGate(map((int)wlPidOutput, 0, 255, 0, 100));
}

void WaterLevel::callibrateMinMaxLevel() //TODO add water flow sensors detection later
//TODO need to be finished in real installation
{
  Serial.println("-------------Entering in calibration");
  //waterGateServo.write(0); //TODO wrato to pecent function
  setWaterLevelGate(0);
  bool waterTankEmpty = false;
  double waterLevelRawDataOld = 0;
  double waterLevelRawData = 0;
  while (!waterTankEmpty)
  {
    Serial.println("--------------MIN CALIB ITERATION");
    waterLevelRawData = abs(getWaterLevelRawData()); // TODO reading need to be abs();
    if ((abs(waterLevelRawData - waterLevelRawDataOld)) >= WATER_LEVEL_DRIFT_RAW)
    {
      waterLevelRawDataOld = waterLevelRawData;
      Serial.println("-----------------MIN LEVEL CALIBRATION");
      Serial.println(waterLevelRawDataOld);
    }
    else
    {
      waterTankEmpty = true;
    }
    delay(2000);
  }
  waterLevelSensor.set_scale();
  waterLevelSensor.tare();
  waterLevelRawData = 0;

  waterLevelRawMin = getWaterLevelRawData();
  Serial.println("Waiting .........................");
  delay(5000);

  //waterGateServo.write(180); //TODO wrato to pecent function
  setWaterLevelGate(100);

  while (waterTankEmpty)
  {
    Serial.println("--------------MAX CALIB ITERATION");
    waterLevelRawData = abs(getWaterLevelRawData());
    if ((abs(waterLevelRawData - waterLevelRawData)) >= WATER_LEVEL_DRIFT_RAW)
    {
      waterLevelRawDataOld = waterLevelRawData;
      Serial.println("---------------MAX LEVEL CALIBRATION");
      Serial.println(waterLevelRawDataOld);
    }
    else
    {
      waterTankEmpty = false;
    }
    delay(2000);
  }

  waterLevelRawMax = getWaterLevelRawData();

  Serial.print(waterLevelRawMin);
  Serial.print("      ");
  Serial.println(waterLevelRawMax);

  Serial.println("Waiting .........................2");
  delay(10000);
}

double WaterLevel::getWaterLevelPercents()
{
  return valueToPercentsOf(getWaterLevelRawData(), waterLevelRawMax);
}

double WaterLevel::getWaterLevelRawData()
{
  while (!waterLevelSensor.is_ready())
  {
    delay(5);
  }
  return waterLevelSensor.get_value(3);
}

void WaterLevel::setWaterLevelGate(double percents)
{
  waterGateServo.write(map((int)percents, 0, 100, 0, 180));
}

void WaterLevel::saveWaterLevelCfgFile()
{
  File waterLevelCfgFile = SPIFFS.open("/water_level_cfg.json", "w");
  if (!waterLevelCfgFile)
  {
    Serial.println("failed to open config file for writing");
  }
  if (waterLevelCfgFile)
  {
    Serial.println("Initializing water level config...");
    const size_t waterLevelCfgCapacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6);
    DynamicJsonDocument waterLevelJsonCfgOut(waterLevelCfgCapacity);

    waterLevelJsonCfgOut["mcuType"] = MCU_TYPE; //TODO change to shared
    waterLevelJsonCfgOut["title"] = "water level ID:" + (String)macId;
    waterLevelJsonCfgOut["isConfigured"] = waterLevelConfigured;

    JsonObject in = waterLevelJsonCfgOut.createNestedObject("in");
    in["gateTarget"] = this->_waterLevel.gateTarget;
    in["levelTarget"] = this->_waterLevel.levelTarget;

    JsonObject inPID = in.createNestedObject("PID");

    inPID["agKp"] = this->wlAgKp;
    inPID["agKi"] = this->wlAgKi;
    inPID["agKd"] = this->wlAgKd;
    inPID["consKp"] = this->wlConsKp;
    inPID["consKi"] = this->wlConsKi;
    inPID["consKd"] = this->wlConsKd;

    if (serializeJson(waterLevelJsonCfgOut, waterLevelCfgFile))
    {
      Serial.println("ERROR: failed to write water level config");
    }
    waterLevelCfgFile.close();
  }
  else
  {
    Serial.println("ERROR: Something goes wrong with water level config file");
  }
}

void WaterLevel::readWaterLevelCfgFile()
{
  if (SPIFFS.exists("/water_level_cfg.json"))
  {
    File waterLevelCfgFile = SPIFFS.open("/water_level_cfg.json", "r");
    if (waterLevelCfgFile)
    {
      Serial.println("Reading water level configs ...");

      const size_t waterLevelCfgCapacity = JSON_OBJECT_SIZE(3) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(6) + 150;
      DynamicJsonDocument waterLevelJsonCfgIn(waterLevelCfgCapacity);

      DeserializationError err = deserializeJson(waterLevelJsonCfgIn, waterLevelCfgFile);

      if (err)
      {
        Serial.println(F("ERROR: failed to read file, using default configuration"));
      }

      this->waterLevelConfigured = waterLevelJsonCfgIn["isConfigured"];
      this->_waterLevel.gateTarget = waterLevelJsonCfgIn["in"]["gateTarget"];
      this->_waterLevel.levelTarget = waterLevelJsonCfgIn["in"]["levelTarget"];

      JsonObject inPID = waterLevelJsonCfgIn["PID"];

      this->wlAgKp = inPID["agKp"];
      this->wlAgKi = inPID["agKi"];
      this->wlAgKd = inPID["agKd"];
      this->wlConsKp = inPID["consKp"];
      this->wlConsKi = inPID["consKi"];
      this->wlConsKd = inPID["consKd"];
    }
    waterLevelCfgFile.close();
  }
  else
  {
    Serial.print("ERROR: no such sonfig file with name:");
    Serial.println("/water_level_cfg.json");
  }
}