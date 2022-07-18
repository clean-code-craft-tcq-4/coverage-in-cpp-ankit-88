#include "typewise-alert.h"
#include <stdio.h>

std::vector<Limits*> CoolingLimitVector;
std::vector<void (*)(BreachType)> alertTargetFuncPtrVector;
void createCoolingLimitsVector()
{
    Limits* passiveCoolingLimit = new Limits{ 0,35 };
    Limits* hiActiveCoolingLimit = new Limits{ 0,45 };
    Limits* midActiveCoolingLimit = new Limits{ 0,40 };

    // Elements inside Vector to be assigned in same order as ENUM Cooling-Type elements.
    CoolingLimitVector = { passiveCoolingLimit, hiActiveCoolingLimit, midActiveCoolingLimit };
}
void createalertTargetFuncPtrVector()
{
    // Elements inside Vector to be assigned in same order as ENUM Alert Target elements.
    alertTargetFuncPtrVector = { sendToController, sendToEmail };
}
BreachType inferBreach(double value, double lowerLimit, double upperLimit) 
{
    if (value < lowerLimit) 
    {
        return TOO_LOW;
    }
    if (value > upperLimit) 
    {
        return TOO_HIGH;
    }
    return NORMAL;
}
Limits* getLimits(CoolingType coolingType)
{
    return CoolingLimitVector.at(coolingType);
}
BreachType classifyTemperatureBreach( CoolingType coolingType, double temperatureInC)
{
    Limits* currentCoolingLimit = getLimits(coolingType);
    return inferBreach(temperatureInC, currentCoolingLimit->lowerLimit, currentCoolingLimit->upperLimit);
}

void checkAndAlert(AlertTarget alertTarget, BatteryCharacter batteryChar, double temperatureInC) 
{
    createCoolingLimitsVector();
    createalertTargetFuncPtrVector();
    BreachType breachType = classifyTemperatureBreach( batteryChar.coolingType, temperatureInC);
    (* (alertTargetFuncPtrVector.at(alertTarget)))(breachType);
}

void sendToController(BreachType breachType) 
{
    const unsigned short header = 0xfeed;
    std::string message {constructMessage(header, breachType)};
    printToConsole(message);
}

void sendToEmail(BreachType breachType) 
{
    const char* recepient = "a.b@c.com";
    std::string message  {constructMessage(recepient, breachType)};
    printToConsole(message);
}
std::string constructMessage(const unsigned short header, BreachType breachType)
{
    std::string message =  std::to_string(header) + ": " + std::to_string(breachType);
    return message;
}
std::string constructMessage(const char*  recepient, BreachType breachType)
{
    std::cout << "testing receipt "<< ( recepient) << std::endl;
    std::string message {};

    switch (breachType) {
    case TOO_LOW:
        message.append("To:");
        message.append(recepient);
        message.append("\n");
        message.append("Hi, the temperature is too low \n");
        break;
    case TOO_HIGH:
        message.append("To:").append(recepient).append("\n").append("Hi, the temperature is too High\n");
        break;
    default:
        //covers normal senario.
        break;
    }
    return message;
}
void printToConsole(std::string message)
{
    std::cout << message << std::endl;
}
