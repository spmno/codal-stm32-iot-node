#include "STM32IotNode.h"
#include "stm32.h"
#include "TemperatureAlarm.h"

using namespace codal;
STM32IotNode IotNode;

int main()
{
    IotNode.init();
    TemperatureAlarm_main();
}