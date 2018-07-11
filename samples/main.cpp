#include "STM32IotNode.h"
#include "stm32.h"

using namespace codal;
STM32IotNode IotNode;

int main()
{
    IotNode.init();
    int state = 0;
    while(1)
    {
        IotNode.io.led.setDigitalValue(state);
        IotNode.io.led2.setDigitalValue(!state);
        IotNode.sleep(1000);
        state = !state;
    }
}