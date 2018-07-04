/*
The MIT License (MIT)

Copyright (c) 2016 Lancaster University, UK.


Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the "Software"),
to deal in the Software without restriction, including without limitation
the rights to use, copy, modify, merge, publish, distribute, sublicense,
and/or sell copies of the Software, and to permit persons to whom the
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef STM32_IOT_NODE_IO_H
#define STM32_IOT_NODE_IO_H

#include "mbed.h"
#include "CodalConfig.h"
#include "MbedPin.h"

//
// Unique Pin number for each pin (synonymous with mbedos PinName)
//


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
            _mbed::Pin        A0;
            _mbed::Pin        A1;
            _mbed::Pin        A2;
            _mbed::Pin        A3;
            _mbed::Pin        A4;
            _mbed::Pin        A5;
            
            _mbed::Pin        D0;
            _mbed::Pin        D1;
            _mbed::Pin        D2;
            _mbed::Pin        D3;
            _mbed::Pin        D4;
            _mbed::Pin        D5;
            _mbed::Pin        D6;
            _mbed::Pin        D7;
            _mbed::Pin        D8;
            _mbed::Pin        D9;
            _mbed::Pin        D10;
            _mbed::Pin        D11;
            _mbed::Pin        D12;
            _mbed::Pin        D13;
            _mbed::Pin        D14;
            _mbed::Pin        D15;


            _mbed::Pin        led;
            _mbed::Pin        led2;
            
            _mbed::Pin        buttonA;
            
            _mbed::Pin        sda;
            _mbed::Pin        scl;

            _mbed::Pin        miso;
            _mbed::Pin        mosi;

            /**
             * Constructor.
             */
            STM32IotNodeIO();
    };

    enum class PinNumber:uint8_t {
        PA_0  = 0x00,
        PA_1  = 0x01,
        PA_2  = 0x02,
        PA_3  = 0x03,
        PA_4  = 0x04,
        PA_5  = 0x05,
        PA_6  = 0x06,
        PA_7  = 0x07,
        PA_8  = 0x08,
        PA_9  = 0x09,
        PA_10 = 0x0A,
        PA_11 = 0x0B,
        PA_12 = 0x0C,
        PA_13 = 0x0D,
        PA_14 = 0x0E,
        PA_15 = 0x0F,

        PB_0  = 0x10,
        PB_1  = 0x11,
        PB_2  = 0x12,
        PB_3  = 0x13,
        PB_4  = 0x14,
        PB_5  = 0x15,
        PB_6  = 0x16,
        PB_7  = 0x17,
        PB_8  = 0x18,
        PB_9  = 0x19,
        PB_10 = 0x1A,
        PB_11 = 0x1B,
        PB_12 = 0x1C,
        PB_13 = 0x1D,
        PB_14 = 0x1E,
        PB_15 = 0x1F,

        PC_0  = 0x20,
        PC_1  = 0x21,
        PC_2  = 0x22,
        PC_3  = 0x23,
        PC_4  = 0x24,
        PC_5  = 0x25,
        PC_6  = 0x26,
        PC_7  = 0x27,
        PC_8  = 0x28,
        PC_9  = 0x29,
        PC_10 = 0x2A,
        PC_11 = 0x2B,
        PC_12 = 0x2C,
        PC_13 = 0x2D,
        PC_14 = 0x2E,
        PC_15 = 0x2F,

        PD_0  = 0x30,
        PD_1  = 0x31,
        PD_2  = 0x32,
        PD_3  = 0x33,
        PD_4  = 0x34,
        PD_5  = 0x35,
        PD_6  = 0x36,
        PD_7  = 0x37,
        PD_8  = 0x38,
        PD_9  = 0x39,
        PD_10 = 0x3A,
        PD_11 = 0x3B,
        PD_12 = 0x3C,
        PD_13 = 0x3D,
        PD_14 = 0x3E,
        PD_15 = 0x3F,

        PE_0  = 0x40,
        PE_1  = 0x41,
        PE_2  = 0x42,
        PE_3  = 0x43,
        PE_4  = 0x44,
        PE_5  = 0x45,
        PE_6  = 0x46,
        PE_7  = 0x47,
        PE_8  = 0x48,
        PE_9  = 0x49,
        PE_10 = 0x4A,
        PE_11 = 0x4B,
        PE_12 = 0x4C,
        PE_13 = 0x4D,
        PE_14 = 0x4E,
        PE_15 = 0x4F,

        PH_0  = 0x70,
        PH_1  = 0x71,

        // ADC internal channels
        ADC_TEMP = 0xF0,
        ADC_VREF = 0xF1,
        ADC_VBAT = 0xF2,

        // Arduino connector namings
        A0          = PC_5,
        A1          = PC_4,
        A2          = PC_3,
        A3          = PC_2,
        A4          = PC_1,
        A5          = PC_0,
        D0          = PA_1,
        D1          = PA_0,
        D2          = PD_14,
        D3          = PB_0,
        D4          = PA_3,
        D5          = PB_4,
        D6          = PB_1,
        D7          = PA_4,
        D8          = PB_2,
        D9          = PA_15,
        D10         = PA_2,
        D11         = PA_7,
        D12         = PA_6,
        D13         = PA_5,
        D14         = PB_9,
        D15         = PB_8,
        // STDIO for console print
        STDIO_UART_TX = PB_6,
        STDIO_UART_RX = PB_7,
        // Generic signals namings
        LED1        = D13, // Green LED (LD1)
        LED2        = PB_14, // Green LED (LD2)
        LED3        = PC_9, // Yellow LED (LD3 WIFI) / Blue LED (LD4 BLE)
        LED4        = LED3,
        USER_BUTTON = PC_13,
        BUTTON1     = USER_BUTTON,
        BUTTON2     = USER_BUTTON,
        BUTTON3     = USER_BUTTON,
        BUTTON4     = USER_BUTTON,
        BUTTON5     = USER_BUTTON,
        SERIAL_TX   = STDIO_UART_TX,
        SERIAL_RX   = STDIO_UART_RX,
        USBTX       = STDIO_UART_TX,
        USBRX       = STDIO_UART_RX,
        I2C_SCL     = D15,
        I2C_SDA     = D14,
        SPI_MOSI    = D11,
        SPI_MISO    = D12,
        SPI_SCK     = D13,
        SPI_CS      = D10,
        PWM_OUT     = D9,

        /**** USB pins ****/
        USB_OTG_FS_DM = PA_11,
        USB_OTG_FS_DP = PA_12,
        USB_OTG_FS_ID = PA_10,
        USB_OTG_FS_NOE = PC_9,
        USB_OTG_FS_NOE_ALT0 = PA_13,
        USB_OTG_FS_SOF = PA_8,
        USB_OTG_FS_VBUS = PA_9,

        /**** OSCILLATOR pins ****/
        RCC_OSC32_IN = PC_14,
        RCC_OSC32_OUT = PC_15,
        RCC_OSC_IN = PH_0,
        RCC_OSC_OUT = PH_1,

        /**** DEBUG pins ****/
        SYS_JTCK_SWCLK = PA_14,
        SYS_JTDI = PA_15,
        SYS_JTDO_SWO = PB_3,
        SYS_JTMS_SWDIO = PA_13,
        SYS_JTRST = PB_4,
        SYS_PVD_IN = PB_7,
        SYS_TRACECLK = PE_2,
        SYS_TRACED0 = PE_3,
        SYS_TRACED1 = PE_4,
        SYS_TRACED2 = PE_5,
        SYS_TRACED3 = PE_6,
        SYS_WKUP1 = PA_0,
        SYS_WKUP2 = PC_13,
        SYS_WKUP3 = PE_6,
        SYS_WKUP4 = PA_2,
        SYS_WKUP5 = PC_5,

        // Not connected
        NC = (uint8_t)(0xFF)
    };
}

#endif
