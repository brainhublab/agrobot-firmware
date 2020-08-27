#include "waterFlow.h"


WaterFlow::WaterFlow()
{
    this->flowPin = 0;
    this->flowPulseCount = 0;
}

WaterFlow::WaterFlow(uint8_t fpin)
{
    this->flowPin = fpin;
    this->flowPulseCount = 0;
}

void WaterFlow::begin()
{
    
    pinMode(this->flowPin, INPUT);
    digitalWrite(this->flowPin, HIGH); //TODO check if its needed;

}

void WaterFlow::handlerP()
{
    this->flowPulseCount++;
}
uint8_t WaterFlow::getPulseCount()
{
    return this->flowPulseCount;
}

unsigned int WaterFlow::getFlow()
{
}

unsigned long WaterFlow::getFlowTotal()
{
}