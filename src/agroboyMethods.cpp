#include <agroboyMethods.h>


#if UNIFIED_CONTROLleR
#endif

#if WATER_LEVEL
void AgroBotMethods::proccesWaterLevel()
{

  correctWaterLevel();

}

void AgroBotMethods::correctWaterLevel()
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
    waterLevelPid.SetTunings(wlConsKp, wlConsKi, wlConsKd);
  }
  else
  {
    //operate gate by using agresive PID
    waterLevelPid.SetTunings(wlAgKp, wlAgKi, wlAgKd);
  }
  waterLevelPid.Compute();
  Serial.print("--------------PID OUT ");
  Serial.println(map((int)wlPidOutput, 0, 255, 0, 100));
  setWaterLevelGate(map((int)wlPidOutput, 0, 255, 0, 100));
}

void AgroBotMethods::callibrateMinMaxLevel() //TODO add water flow sensors detection later 
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

double AgroBotMethods::getWaterLevelPercents()
{
  return valueToPercentsOf(getWaterLevelRawData(), waterLevelRawMax);
}

double AgroBotMethods::getWaterLevelRawData()
{
  while (!waterLevelSensor.is_ready())
  {
    delay(5);
  }
  return waterLevelSensor.get_value(3);

}

void AgroBotMethods::setWaterLevelGate(double percents)
{
  waterGateServo.write(map((int)percents, 0, 100, 0, 180));
}
#endif

#if LIGHT_CONTROL

void AgroBotMethods::proecessLightControl()
{

}

void AgroBotMethods::correctLightLevel()
{

}


#endif

#if NUTRITION_CONTROL

void AgroBotMethods::processNutritionControl
{

}

void AgroBotMethods::correctNutritionConcentration()
{

}
#endif
