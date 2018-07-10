#ifndef STM32_IOT_NODE_IO_H
#define STM32_IOT_NODE_IO_H

//
// Component IDs for each pin.
// The can be user defined, but uniquely identify a pin when using the eventing APIs/
//
#define ID_PIN_P0        (DEVICE_ID_IO_P0 + 0)
#define ID_PIN_P1        (DEVICE_ID_IO_P0 + 1)
#define ID_PIN_P2        (DEVICE_ID_IO_P0 + 2)
#define ID_PIN_P3        (DEVICE_ID_IO_P0 + 3)
#define ID_PIN_P4        (DEVICE_ID_IO_P0 + 4)
#define ID_PIN_P5        (DEVICE_ID_IO_P0 + 5)
#define ID_PIN_P6        (DEVICE_ID_IO_P0 + 6)
#define ID_PIN_P7        (DEVICE_ID_IO_P0 + 7)
#define ID_PIN_P8        (DEVICE_ID_IO_P0 + 8)
#define ID_PIN_P9        (DEVICE_ID_IO_P0 + 9)
#define ID_PIN_P10       (DEVICE_ID_IO_P0 + 10)
#define ID_PIN_P11       (DEVICE_ID_IO_P0 + 11)
#define ID_PIN_P12       (DEVICE_ID_IO_P0 + 12)
#define ID_PIN_P13       (DEVICE_ID_IO_P0 + 13)
#define ID_PIN_P14       (DEVICE_ID_IO_P0 + 14)
#define ID_PIN_P15       (DEVICE_ID_IO_P0 + 15)
#define ID_PIN_P16       (DEVICE_ID_IO_P0 + 16)
#define ID_PIN_P17       (DEVICE_ID_IO_P0 + 17)
#define ID_PIN_P18       (DEVICE_ID_IO_P0 + 18)
#define ID_PIN_P19       (DEVICE_ID_IO_P0 + 19)
#define ID_PIN_P20       (DEVICE_ID_IO_P0 + 20)
#define ID_PIN_P21       (DEVICE_ID_IO_P0 + 21)
#define ID_PIN_P22       (DEVICE_ID_IO_P0 + 22)
#define ID_PIN_P23       (DEVICE_ID_IO_P0 + 23)
#define ID_PIN_P24       (DEVICE_ID_IO_P0 + 24)
#define ID_PIN_P25       (DEVICE_ID_IO_P0 + 25)
#define ID_PIN_P26       (DEVICE_ID_IO_P0 + 26)
#define ID_PIN_P27       (DEVICE_ID_IO_P0 + 27)
#define ID_PIN_P28       (DEVICE_ID_IO_P0 + 28)
#define ID_PIN_P29       (DEVICE_ID_IO_P0 + 29)
#define ID_PIN_P30       (DEVICE_ID_IO_P0 + 30)
#define ID_PIN_P31       (DEVICE_ID_IO_P0 + 31)
#define ID_PIN_SDA       (DEVICE_ID_IO_P0 + 32)
#define ID_PIN_SCL       (DEVICE_ID_IO_P0 + 33)
#define ID_PIN_MISO       (DEVICE_ID_IO_P0 + 34)
#define ID_PIN_MOSI       (DEVICE_ID_IO_P0 + 35)

namespace codal
{
    /**
     * Represents a collection of all I/O pins exposed by the device.
     */
    class STM32IotNodeIO
    {
        public:
            /**
             * Constructor.
             */
            STM32IotNodeIO();
    };
}

#endif
