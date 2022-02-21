#include "typewise-alert.h"
#include <stdio.h>

int (*printerFp[]) (const char* recepient) = {fpAlertNormal, fpAlertTempLow, fpAlertTempHigh};
void (*alerterFp[]) (BreachType breachType) = {sendToController, sendToEmail};

BreachType inferBreach(double value, double lowerLimit, double upperLimit) {
  if(value < lowerLimit) {
    return TOO_LOW;
  }
  if(value > upperLimit) {
    return TOO_HIGH;
  }
  return NORMAL;
}

BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC) 
{
  CoolingTypeLimit_t limitCoolingType =  coolingType();
  BreachType ret = inferBreach(temperatureInC, limitCoolingType.lowLimit, limitCoolingType.highLimit);
  return ret;
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
  BreachType breachType = classifyTemperatureBreach(batteryChar.coolingType, temperatureInC);
  int arrPtr = (int)alertTarget;
  alerterFp[arrPtr](breachType);
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  (void)printEmailContents(breachType);
}

int printEmailContents(BreachType breachType)
{
  int arrPtr = (int)breachType;
  const char* recepient = "a.b@c.com";
  return printerFp[arrPtr](recepient);
}

int fpAlertTempLow(const char* recepient)
{
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is too low\n");
  return 0;
}
int fpAlertTempHigh(const char* recepient)
{
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is too high\n");
  return 0;
}
int fpAlertNormal(const char* recepient)
{
  // printf("To: %s\n", recepient);
  // printf("Hi, the temperature is normal\n");
  return 0;
}

CoolingTypeLimit_t PASSIVE_COOLING()
{
	return setRangeWRTCoolingType(0,35);
}

CoolingTypeLimit_t HI_ACTIVE_COOLING()
{
	return setRangeWRTCoolingType(0,45);
}

CoolingTypeLimit_t MED_ACTIVE_COOLING()
{
	return setRangeWRTCoolingType(0,40);
}

CoolingTypeLimit_t setRangeWRTCoolingType(float low, float high)
{
	CoolingTypeLimit_t limit;
	limit.lowLimit = low;
	limit.highLimit = high;
	return limit;
}
