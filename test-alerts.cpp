#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

TEST_CASE("infers the breach according to limits") {
  REQUIRE(inferBreach(18, 20, 30) == TOO_LOW); // low check
  REQUIRE(inferBreach(19, 20, 30) == TOO_LOW); // low boundary check
  REQUIRE(inferBreach(20, 20, 30) == NORMAL);  // normal low boundary check
  REQUIRE(inferBreach(21, 20, 30) == NORMAL);  // normal check
  REQUIRE(inferBreach(22, 20, 30) == NORMAL);  // normal check
  REQUIRE(inferBreach(29, 20, 30) == NORMAL);  // normal check
  REQUIRE(inferBreach(30, 20, 30) == NORMAL);  // normal high boundary check
  REQUIRE(inferBreach(31, 20, 30) == TOO_HIGH); // high boundary check
  REQUIRE(inferBreach(35, 20, 30) == TOO_HIGH);  // high check
}

TEST_CASE("Classification of Temperature Breach") {
  REQUIRE((classifyTemperatureBreach(HI_ACTIVE_COOLING, 0) == NORMAL));
  REQUIRE((classifyTemperatureBreach(HI_ACTIVE_COOLING,20) == NORMAL)); // low boundary check
  REQUIRE((classifyTemperatureBreach(HI_ACTIVE_COOLING,45) == NORMAL)); // high boundary check
  REQUIRE((classifyTemperatureBreach(HI_ACTIVE_COOLING,-1) == TOO_LOW));
  REQUIRE((classifyTemperatureBreach(HI_ACTIVE_COOLING,46) == TOO_HIGH));

  REQUIRE((classifyTemperatureBreach(PASSIVE_COOLING,20) == NORMAL));
  REQUIRE((classifyTemperatureBreach(PASSIVE_COOLING, 0) == NORMAL)); // low boundary check
  REQUIRE((classifyTemperatureBreach(PASSIVE_COOLING,35) == NORMAL)); // high boundary check
  REQUIRE((classifyTemperatureBreach(PASSIVE_COOLING,-1) == TOO_LOW));
  REQUIRE((classifyTemperatureBreach(PASSIVE_COOLING,36) == TOO_HIGH));
  
  REQUIRE((classifyTemperatureBreach(MED_ACTIVE_COOLING,20) == NORMAL));
  REQUIRE((classifyTemperatureBreach(MED_ACTIVE_COOLING, 0) == NORMAL)); // low boundary check
  REQUIRE((classifyTemperatureBreach(MED_ACTIVE_COOLING,40) == NORMAL)); // high boundary check
  REQUIRE((classifyTemperatureBreach(MED_ACTIVE_COOLING,-1) == TOO_LOW));
  REQUIRE((classifyTemperatureBreach(MED_ACTIVE_COOLING,41) == TOO_HIGH));
}

TEST_CASE("checkAndAlert function") {

  BatteryCharacter batteryCharacter;

  batteryCharacter.coolingType = PASSIVE_COOLING;
  checkAndAlert(TO_EMAIL,batteryCharacter, 0); //normal low boundary
  checkAndAlert(TO_EMAIL,batteryCharacter,10); //normal
  checkAndAlert(TO_EMAIL,batteryCharacter,35); //normal high boundary
  checkAndAlert(TO_EMAIL,batteryCharacter,-1); // low check
  checkAndAlert(TO_EMAIL,batteryCharacter,36); // hign check
  checkAndAlert(TO_CONTROLLER,batteryCharacter, 0); //normal low boundary
  checkAndAlert(TO_CONTROLLER,batteryCharacter,10); //normal
  checkAndAlert(TO_CONTROLLER,batteryCharacter,35); //normal high boundary
  checkAndAlert(TO_CONTROLLER,batteryCharacter,-1); // low check
  checkAndAlert(TO_CONTROLLER,batteryCharacter,36); // hign check

  batteryCharacter.coolingType = HI_ACTIVE_COOLING;

  checkAndAlert(TO_EMAIL,batteryCharacter, 0); //normal low boundary
  checkAndAlert(TO_EMAIL,batteryCharacter,10); //normal
  checkAndAlert(TO_EMAIL,batteryCharacter,45); //normal high boundary
  checkAndAlert(TO_EMAIL,batteryCharacter,-1); // low check
  checkAndAlert(TO_EMAIL,batteryCharacter,46); // hign check
  checkAndAlert(TO_CONTROLLER,batteryCharacter, 0); //normal low boundary
  checkAndAlert(TO_CONTROLLER,batteryCharacter,10); //normal
  checkAndAlert(TO_CONTROLLER,batteryCharacter,45); //normal high boundary
  checkAndAlert(TO_CONTROLLER,batteryCharacter,-1); // low check
  checkAndAlert(TO_CONTROLLER,batteryCharacter,46); // hign check
 
  batteryCharacter.coolingType = MED_ACTIVE_COOLING;

  checkAndAlert(TO_EMAIL,batteryCharacter, 0); //normal low boundary
  checkAndAlert(TO_EMAIL,batteryCharacter,10); //normal
  checkAndAlert(TO_EMAIL,batteryCharacter,40); //normal high boundary
  checkAndAlert(TO_EMAIL,batteryCharacter,-1); // low check
  checkAndAlert(TO_EMAIL,batteryCharacter,41); // hign check
  checkAndAlert(TO_CONTROLLER,batteryCharacter, 0); //normal low boundary
  checkAndAlert(TO_CONTROLLER,batteryCharacter,10); //normal
  checkAndAlert(TO_CONTROLLER,batteryCharacter,40); //normal high boundary
  checkAndAlert(TO_CONTROLLER,batteryCharacter,-1); // low check
  checkAndAlert(TO_CONTROLLER,batteryCharacter,41); // hign check
}
