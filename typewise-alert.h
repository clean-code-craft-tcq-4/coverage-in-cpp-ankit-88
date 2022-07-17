#pragma once
#include<iostream>
#include<vector>
#include<string>

typedef enum {
	PASSIVE_COOLING,
	HI_ACTIVE_COOLING,
	MED_ACTIVE_COOLING
} CoolingType;

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

struct Limits {
	int lowerLimit;
	int upperLimit;

	int getLowerLimit()
	{
		return lowerLimit;
	}
	int getUpperLimit()
	{
		return upperLimit;
	}
};


/*class CoolingLimits
{
public:
	virtual Limits& setlimit() = 0;
};

class PassiveCoolingLimit : public CoolingLimits
{
	const int lower_limit = 0;
	const int upper_limit = 35;
public:
	Limits l;
	Limits& setlimit()
	{
		l.lowerLimit = lower_limit;
		l.upperLimit = upper_limit;
		return l;
	}

};

class HiActiveCoolingLimit : public CoolingLimits
{
	const int lower_limit = 0;
	const int upper_limit = 45;
public:
	Limits l;
	Limits& setlimit()
	{
		l.lowerLimit = lower_limit;
		l.upperLimit = upper_limit;
		return l;
	}

};

class MidActiveCoolingLimit : public CoolingLimits
{
	const int lower_limit = 0;
	const int upper_limit = 40;
public:
	Limits l;
	Limits& setlimit()
	{
		l.lowerLimit = lower_limit;
		l.upperLimit = upper_limit;
		return l;
	}

};*/

extern std::vector<Limits*> CoolingBaseClass;
extern std::vector<void (*)(BreachType)> alertTargetFuncPtrVector;
void checkAndAlert(
	AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC);

void sendToController(BreachType breachType);
void sendToEmail(BreachType breachType);
std::string constructMessage(const unsigned short header, BreachType breachType);
std::string constructMessage(const char*  recepient, BreachType breachType);
void printToConsole(std::string);
