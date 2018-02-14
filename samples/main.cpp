//#include "mbed.h"
//
//DigitalOut led1(LED1);
//
//// main() runs in its own thread in the OS
//int main() {
//    while (true) {
//        led1 = !led1;
//        wait(2);
//    }
//}

#include "STM32IotNode.h"

STM32IotNode IotNode;

void
onClick(Event)
{
    IotNode.serial.printf("CLICK\r\n");
}

int
main()
{
	printf("Trace 1\n");
    IotNode.init();
    IotNode.serial.printf(" *** STM32_IOT_NODE BLINKY TEST ***\r\n");

    IotNode.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onClick);

    while(1)
    {
        IotNode.io.led.setDigitalValue(1);
        IotNode.sleep(100);

        IotNode.io.led.setDigitalValue(0);
        IotNode.sleep(100);
    }
}
