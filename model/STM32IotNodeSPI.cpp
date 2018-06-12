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

#include "STM32IotNodeSPI.h"
#include "ErrorNo.h"
#include "CodalDmesg.h"
#include "codal-core/inc/driver-models/Timer.h"

namespace codal
{

/**
 * Constructor.
 */
STM32IotNodeSPI::STM32IotNodeSPI(Pin &mosi, Pin &miso, Pin &sclk)
    : MbedSPI(mosi, miso, sclk), _irq(this, &STM32IotNodeSPI::_transferDone)
{
}

void STM32IotNodeSPI::_transferDone()
{
    //DMESG("done: this=%p", this);
    if (doneHandler) {
        auto f = doneHandler;
        doneHandler = NULL;
        f(doneArg);
    }
}

static DMA_HandleTypeDef hdma_tx;
static STM32IotNodeSPI *instance;
extern "C" void HAL_SPI_TxCpltCallback(SPI_HandleTypeDef *hspi)
{
    instance->_transferDone();
}

static void DMA_IRQ_Handler(void) {
    HAL_DMA_IRQHandler(&hdma_tx);
}

/**
 * Writes a given command to SPI bus, and afterwards reads the response. Finally, calls doneHandler
 * (possibly in IRQ context).
 *
 * Note that bytes recieved while sending command are ignored.
 */
int STM32IotNodeSPI::startTransfer(const uint8_t *command, uint32_t commandSize, uint8_t *response,
                           uint32_t responseSize, PVoidCallback doneHandler, void *arg)
{
    if (doneHandler == NULL)
        return DEVICE_INVALID_PARAMETER;

    if (responseSize)
    {
        // both command and response, fallback to slow mode
        return codal::SPI::startTransfer(command, commandSize, response, responseSize, doneHandler,
                                         arg);
    }
    else if (commandSize)
    {
        struct spi_s *spiobj = &_spi.spi;
        SPI_HandleTypeDef *handle = &(spiobj->handle);

        instance = this;

        __HAL_RCC_DMA1_CLK_ENABLE();

        hdma_tx.Instance                 = DMA1_Channel3;
        hdma_tx.Init.Direction           = DMA_MEMORY_TO_PERIPH;
        hdma_tx.Init.PeriphInc           = DMA_PINC_DISABLE;
        hdma_tx.Init.MemInc              = DMA_MINC_ENABLE;
        hdma_tx.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        hdma_tx.Init.MemDataAlignment    = DMA_MDATAALIGN_BYTE;
        hdma_tx.Init.Mode                = DMA_NORMAL;
        hdma_tx.Init.Priority            = DMA_PRIORITY_LOW;

    HAL_DMA_Init(&hdma_tx);

    /* Associate the initialized DMA handle to the the SPI handle */
    __HAL_LINKDMA(handle, hdmatx, hdma_tx);

        IRQn_Type irq_n = DMA1_Channel3_IRQn;

        NVIC_SetVector(irq_n, (uint32_t)DMA_IRQ_Handler);
        NVIC_SetPriority(irq_n, 1);
        NVIC_ClearPendingIRQ(irq_n);
        NVIC_EnableIRQ(irq_n);

        this->doneHandler = doneHandler;
        this->doneArg = arg;

#if defined(SPI_FLAG_FRLVL) // STM32F0 STM32F3 STM32F7 STM32L4
        // flush FIFO
        HAL_SPIEx_FlushRxFifo(handle);
#endif

        //DMESG("start: h=%p data=%p sz=%d this=%p", handle, command, commandSize, this);

        auto rc = HAL_SPI_Transmit_DMA(handle, (uint8_t*)command, commandSize);

        //DMESG("rc=%d", rc);

        return rc ? DEVICE_SPI_ERROR : DEVICE_OK;
    }
    else
    {
        return DEVICE_INVALID_PARAMETER;
    }
}
}
