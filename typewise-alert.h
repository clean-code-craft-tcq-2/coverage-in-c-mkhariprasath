#pragma once

#define TEST_ENV    0
#define PROD_ENV    1

#ifndef WORKING_ENV
#define WORKING_ENV PROD_ENV //default is production environment
#endif

extern int  printCounter; //to use in the testing environment to assert on print functionality


typedef struct {
  double lowLimit;
  double highLimit; 
}CoolingTypeLimit_t;

typedef enum {
  NORMAL,
  TOO_LOW,
  TOO_HIGH
} BreachType;

typedef CoolingTypeLimit_t (*CoolingType)();
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

int fpAlertNormal(const char* recepient);
int fpAlertTempLow(const char* recepient);
int fpAlertTempHigh(const char* recepient);
int printEmailContents();


int (*printerFp[]) () = {fpAlertNormal, fpAlertTempLow, fpAlertTempHigh};
int (*alerterFp[]) () = {sendToController, sendToEmail};

