#pragma once

typedef struct {
  double lowLimit;
  double highLimit; 
}CoolingTypeLimit_t;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

BreachType inferBreach(double value, double lowerLimit, double upperLimit);
BreachType classifyTemperatureBreach(CoolingType coolingType, double temperatureInC);

typedef enum {
  TO_CONTROLLER,
  TO_EMAIL
} AlertTarget;

typedef struct {
  CoolingType coolingType;
  char brand[48];
} BatteryCharacter;

void checkAndAlert(
  AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);

CoolingTypeLimit_t PASSIVE_COOLING();
CoolingTypeLimit_t HI_ACTIVE_COOLING();
CoolingTypeLimit_t MED_ACTIVE_COOLING();
CoolingTypeLimit_t setRangeWRTCoolingType(float, float);
