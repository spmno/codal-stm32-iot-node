#include "STM32IotNode.h"
using namespace codal;

STM32IotNode IotNode;

int main()
{
    IotNode.io.led2.setDigitalValue(true);
    IotNode.init();
    //IotNode.serial.printf("*** STM32_IOT_NODE BLINKY TEST ***\r\n");

    int state = 0;

    while(1)
    {
        IotNode.io.led.setDigitalValue(state);
        IotNode.io.led2.setDigitalValue(state);
        fiber_sleep(1000);
        state = !state;
    }
}
