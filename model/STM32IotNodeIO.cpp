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

/**
  * Class definition for STM32 IOT node IO.
  * Represents a collection of all I/O pins on the device.
  */

#include "CodalConfig.h"
#include "STM32IotNodeIO.h"

namespace codal
{

/**
  * Constructor.
  *
  * Create a representation of all given I/O pins on the edge connector
  *
  * Accepts a sequence of unique ID's used to distinguish events raised
  * by MicroBitPin instances on the default EventModel.
  */
STM32IotNodeIO::STM32IotNodeIO() :
    A0 (ID_PIN_P0, PinName::A0, PIN_CAPABILITY_AD),
    A1 (ID_PIN_P1, PinName::A1, PIN_CAPABILITY_AD),
    A2 (ID_PIN_P2, PinName::A2, PIN_CAPABILITY_AD),
    A3 (ID_PIN_P3, PinName::A3, PIN_CAPABILITY_AD),
    A4 (ID_PIN_P4, PinName::A4, PIN_CAPABILITY_AD),
    A5 (ID_PIN_P5, PinName::A5, PIN_CAPABILITY_AD),
    D0 (ID_PIN_P6, PinName::D0, PIN_CAPABILITY_AD),
    D1 (ID_PIN_P7, PinName::D1, PIN_CAPABILITY_AD),
    D2 (ID_PIN_P8, PinName::D2, PIN_CAPABILITY_AD),
    D3 (ID_PIN_P9, PinName::D3, PIN_CAPABILITY_AD),
    D4 (ID_PIN_P10, PinName::D4, PIN_CAPABILITY_AD),
    D5 (ID_PIN_P11, PinName::D5, PIN_CAPABILITY_AD),
    D6 (ID_PIN_P12, PinName::D6, PIN_CAPABILITY_AD),
    D7 (ID_PIN_P13, PinName::D7, PIN_CAPABILITY_AD),
    D8 (ID_PIN_P14, PinName::D8, PIN_CAPABILITY_AD),
    D9 (ID_PIN_P15, PinName::D9, PIN_CAPABILITY_AD),
    D10 (ID_PIN_P16, PinName::D10, PIN_CAPABILITY_AD),
    D11 (ID_PIN_P17, PinName::D11, PIN_CAPABILITY_AD),
    D12 (ID_PIN_P18, PinName::D12, PIN_CAPABILITY_AD),
    D13 (ID_PIN_P19, PinName::D13, PIN_CAPABILITY_AD),
    D14 (ID_PIN_P20, PinName::D14, PIN_CAPABILITY_AD),
    D15 (ID_PIN_P21, PinName::D15, PIN_CAPABILITY_AD),
    
    led (ID_PIN_P19, PinName::LED1, PIN_CAPABILITY_AD),
    led2 (ID_PIN_P22, PinName::LED2, PIN_CAPABILITY_AD),

    buttonA (DEVICE_ID_BUTTON_A, PinName::USER_BUTTON, PIN_CAPABILITY_DIGITAL),

    sda(ID_PIN_SDA, PinName::I2C_SDA, PIN_CAPABILITY_DIGITAL),
    scl(ID_PIN_SCL, PinName::I2C_SCL, PIN_CAPABILITY_DIGITAL),

    miso(ID_PIN_MISO, PinName::SPI_MISO, PIN_CAPABILITY_DIGITAL),
    mosi(ID_PIN_MOSI, PinName::SPI_MOSI, PIN_CAPABILITY_DIGITAL)
{
}

}
