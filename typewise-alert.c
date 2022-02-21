#include "typewise-alert.h"
#include <stdio.h>

#if (WORKING_ENV == TEST_ENV)
int  printCounter = 0;
#endif

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
  #if (WORKING_ENV == TEST_ENV)
  int  printCounter++;
  return printCounter; // to assert
  #else 
  return 0;
  #endif
}
int fpAlertTempHigh(const char* recepient)
{
  printf("To: %s\n", recepient);
  printf("Hi, the temperature is too high\n");
  #if (WORKING_ENV == TEST_ENV)
  int  printCounter++;
  return printCounter; // to assert
  #else 
  return 0;
  #endif
}
int fpAlertNormal(const char* recepient)
{
  // printf("To: %s\n", recepient);
  // printf("Hi, the temperature is too high\n");
  // #if (WORKING_ENV == TEST_ENV)
  // int  printCounter++;
  // return printCounter;
  // #else 
  // return 0;
  // #endif
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
