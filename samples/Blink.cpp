#include "Blink.h"

void Blink_main(codal::STM32IotNode& iotNode){
	iotNode.io.led.setDigitalValue(0);
	iotNode.io.led2.setDigitalValue(0);

	int state = 1;
	while(1)
    {    
		iotNode.io.led.setDigitalValue(state);
        iotNode.io.led2.setDigitalValue(state);
        iotNode.sleep(1000);
        state = !state;
    }
}