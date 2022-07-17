#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"
#include "typewise-alert.h"

createCoolingLimitsVector();
createalertTargetFuncPtrVector();
TEST_CASE("infers the breach according to limits") {
	REQUIRE(inferBreach(12, 20, 30) == TOO_LOW);
	REQUIRE(inferBreach(40, 20, 30) == TOO_HIGH);
	REQUIRE(inferBreach(25, 20, 30) == NORMAL);
}

TEST_CASE("classify Temperature breach with different value") {
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING,20) == NORMAL);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, -20) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(PASSIVE_COOLING, 40) == TOO_HIGH);

	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 20) == NORMAL);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, -20) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(HI_ACTIVE_COOLING, 50) == TOO_HIGH);

	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 20) == NORMAL);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, -20) == TOO_LOW);
	REQUIRE(classifyTemperatureBreach(MED_ACTIVE_COOLING, 40) == TOO_HIGH);

}
