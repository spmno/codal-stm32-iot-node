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

    uint8_t Data = 0xFF;
    int Return = IotNode.i2c.write( 0xD5, 0x10, Data );
	IotNode.serial.printf("   Return: 0x%08X = %d\n", Return, Return);
    int Return = IotNode.i2c.write( 0xD7, 0x10, Data );
	IotNode.serial.printf("   Return: 0x%08X = %d\n", Return, Return);

    Return = IotNode.i2c.read( 0xD7, 0x0F, &Data, sizeof( Data ) );
	IotNode.serial.printf("   Return: 0x%08X = %d\n", Return, Return);
	IotNode.serial.printf("   Data:   0x%02X\n", Data);

//	codal::Sample3D Sample = IotNode.accelerometer.getSample( );
//	IotNode.serial.printf("   x: 0x%04X = %d\n", Sample.x, Sample.x );
//	IotNode.serial.printf("   y: 0x%04X = %d\n", Sample.y, Sample.y );
//	IotNode.serial.printf("   z: 0x%04X = %d\n", Sample.z, Sample.z );

}

int
main()
{
    IotNode.init();
    IotNode.serial.printf("*** STM32_IOT_NODE BLINKY TEST ***\r\n");
    IotNode.serial.printf( "sda: 0x%04X\r\n", IotNode.io.sda.name );
    IotNode.serial.printf( "scl: 0x%04X\r\n", IotNode.io.scl.name );

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
