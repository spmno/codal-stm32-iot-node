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

    uint32_t Data;

	IotNode.i2c.read( 0x2, 1, ( uint8_t* ) &Data, 4 );
	IotNode.serial.printf("   Data: 0x%08X\n", Data);
}

int
main()
{
    IotNode.init();
    IotNode.serial.printf("*** STM32_IOT_NODE BLINKY TEST ***\r\n");
    IotNode.serial.printf( "sda: 0x%04X\r\n", i2c.sda.name );
    IotNode.serial.printf( "scl: 0x%04X\r\n", i2c.scl.name );

    IotNode.messageBus.listen(DEVICE_ID_BUTTON_A, DEVICE_BUTTON_EVT_CLICK, onClick);

    IotNode.i2c.setFrequency( 400000 );

    while(1)
    {
    	IotNode.io.led.setDigitalValue(1);
        IotNode.sleep(200);

        IotNode.io.led.setDigitalValue(0);
        IotNode.sleep(200);
    }
}
