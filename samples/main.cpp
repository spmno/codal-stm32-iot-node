#include "STM32IotNode.h"
#include "stm32.h"
#include "TemperatureAlarm.h"

using namespace codal;
STM32IotNode iotNode;

int main()
{
    iotNode.init();
    TemperatureAlarm_main(iotNode);
}