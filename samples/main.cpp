#include "stm32.h"
#include "STM32IotNode.h"

#include "Blink.h"
#include "TemperatureAlarm.h"


using namespace codal;
STM32IotNode iotNode;

int main()
{
    iotNode.init();
    Blink_main(iotNode);
    //TemperatureAlarm_main(iotNode);
}