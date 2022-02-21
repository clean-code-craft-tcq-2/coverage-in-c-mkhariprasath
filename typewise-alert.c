#include "typewise-alert.h"
#include <stdio.h>

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
  return inferBreach(temperatureInC, limitCoolingType.lowLimit, limitCoolingType.highLimit);
}

void checkAndAlert(
    AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) {

  BreachType breachType = classifyTemperatureBreach(
    batteryChar.coolingType, temperatureInC
  );

  switch(alertTarget) {
    case TO_CONTROLLER:
      sendToController(breachType);
      break;
    case TO_EMAIL:
      sendToEmail(breachType);
      break;
  }
}

void sendToController(BreachType breachType) {
  const unsigned short header = 0xfeed;
  printf("%x : %x\n", header, breachType);
}

void sendToEmail(BreachType breachType) {
  const char* recepient = "a.b@c.com";
  switch(breachType) {
    case TOO_LOW:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too low\n");
      break;
    case TOO_HIGH:
      printf("To: %s\n", recepient);
      printf("Hi, the temperature is too high\n");
      break;
    case NORMAL:
      break;
  }
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
