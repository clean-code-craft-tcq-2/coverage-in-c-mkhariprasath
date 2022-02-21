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
