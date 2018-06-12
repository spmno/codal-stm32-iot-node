/*
The MIT License (MIT)

Copyright (c) 2017 Lancaster University.

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

#ifndef CODAL_STM32_IOT_NODE_SPI_H
#define CODAL_STM32_IOT_NODE_SPI_H

#include "MbedSPI.h"
#include "CThunk.h"

namespace codal
{
/**
 * Class definition for SPI service, derived from ARM mbed.
 */
class STM32IotNodeSPI : public MbedSPI
{
protected:
    CThunk<STM32IotNodeSPI> _irq;
    PVoidCallback doneHandler;
    void *doneArg;
public:
    void _transferDone();
    /**
     * Initialize SPI instance with given pins.
     *
     * Default setup is 1 MHz, 8 bit, mode 0.
     */
    STM32IotNodeSPI(codal::Pin &mosi, codal::Pin &miso, codal::Pin &sclk);

    /**
     * Writes and reads from the SPI bus concurrently. Finally, calls doneHandler (possibly in IRQ context).
     *
     * Either buffer can be NULL.
     */
    virtual int startTransfer(const uint8_t *txBuffer, uint32_t txSize, uint8_t *rxBuffer,
                         uint32_t rxSize, PVoidCallback doneHandler, void *arg);


};
}

#endif