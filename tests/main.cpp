

#include "mbed.h"

DigitalOut myled(LED1);

int main()
{
    // check that myled object is initialized and connected to a pin
    if(myled.is_connected()) {
        printf("myled is initialized and connected!\n\r");
    }

    // Blink LED
    while(1) {
        myled = 1;          // set LED1 pin to high
        printf("\n\r myled = %d", (uint8_t)myled );
        wait(0.5);

        myled.write(0);     // set LED1 pin to low
        printf("\n\r myled = %d",myled.read() );
        wait(0.5);
    }
    return 0;
}
