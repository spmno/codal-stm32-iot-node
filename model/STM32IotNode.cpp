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


#include "STM32IotNode.h"
#include "Timer.h"

using namespace codal;
void STM32IotNode_dmesg_flush();

static STM32IotNode *device_instance = NULL;

/**
  * Constructor.
  *
  * Create a representation of a device, which includes member variables
  * that represent various device drivers used to control aspects of the STM32 IOT node.
  */
STM32IotNode::STM32IotNode() :
    serial(SERIAL_TX, SERIAL_RX),
    timer(),
    coordinateSpace( SIMPLE_CARTESIAN ),
    messageBus(),
    io(),
    i2c( io.sda, io.scl ),
    accelerometer( i2c, coordinateSpace ),
    distance( i2c ),
    gyroscope( i2c, coordinateSpace ),
    humidity( i2c ),
    pressure( i2c ),
    temperature( i2c ),
    buttonA(io.buttonA, DEVICE_ID_BUTTON_A, DEVICE_BUTTON_ALL_EVENTS, ACTIVE_LOW)
{
    // Clear our status
    status = 0;

    // Configure serial port for debugging
    //serial.set_flow_control(mbed::Serial::Disabled);
    serial.baud(9600);

    device_instance = this;
}

/**
  * Post constructor initialisation method.
  *
  * This call will initialised the scheduler, memory allocator and Bluetooth stack.
  *
  * This is required as the Bluetooth stack can't be brought up in a
  * static context i.e. in a constructor.
  *
  * @code
  * stm32IotNode.init();
  * @endcode
  *
  * @note This method must be called before user code utilises any functionality
  *       contained within the STM32IotNode class.
  */
int STM32IotNode::init()
{
    if (status & DEVICE_INITIALIZED)
        return DEVICE_NOT_SUPPORTED;

    status |= DEVICE_INITIALIZED;

    codal_dmesg_set_flush_fn(STM32IotNode_dmesg_flush);
    messageBus.listen(DEVICE_ID_MESSAGE_BUS_LISTENER, DEVICE_EVT_ANY, this, &STM32IotNode::onListenerRegisteredEvent);
    
    // Bring up fiber scheduler.
    //scheduler_init(messageBus);
   

    for(int i = 0; i < DEVICE_COMPONENT_COUNT; i++)
    {
        if(CodalComponent::components[i])
            CodalComponent::components[i]->init();
    }
    
    status |= DEVICE_COMPONENT_STATUS_IDLE_TICK;

    return DEVICE_OK;
}

/**
  * A periodic callback invoked by the fiber scheduler idle thread.
  * We use this for any low priority, background housekeeping.
  *
  */
void STM32IotNode::idleCallback()
{
    codal_dmesg_flush();
}

void STM32IotNode::periodicCallback(){}

/**
  * A listener to perform actions as a result of Message Bus reflection.
  *
  * In some cases we want to perform lazy instantiation of components, such as
  * the compass and the accelerometer, where we only want to add them to the idle
  * fiber when someone has the intention of using these components.
  */
void STM32IotNode::onListenerRegisteredEvent(Event evt)
{

}

extern "C"
{

void STM32IotNode_Trace( const char* Format )
{
 if ( device_instance )
  device_instance->serial.printf( Format );
}

void STM32IotNode_TraceU16( const char* Format, uint16_t Value )
{
 if ( device_instance )
  device_instance->serial.printf( Format, Value );
}

#define I2C_TIME_OUT_BASE   10
#define I2C_TIME_OUT_BYTE   1

int Sensor_IO_I2CRead( uint8_t Addr, uint8_t *pdata, uint32_t count)
{
 STM32IotNode_TraceU16( "Sensor_IO_I2CRead, Addr:   %02X\n", Addr );
 int status = HAL_OK;
 int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;
// device_instance->serial.printf( "Sensor_IO_I2CRead\n" );
// device_instance->serial.printf( " handle          = %08X\n", device_instance->i2c.getHandle( ) );
// device_instance->serial.printf( " Addr            = %02X\n", Addr | 1 );
// device_instance->serial.printf( " count           = %04X\n", count );
// device_instance->serial.printf( " pdata           = %08X\n", pdata );
 status = HAL_I2C_Master_Receive( device_instance->i2c.getHandle( ), Addr | 1, pdata, count, i2c_time_out);
 STM32IotNode_TraceU16( "Sensor_IO_I2CRead, status: %04X\n", status );
 return status;
}

int Sensor_IO_I2CWrite( uint8_t Addr, uint8_t *pdata, uint32_t count)
{
 STM32IotNode_TraceU16( "Sensor_IO_I2CWrite, Addr: %02X\n", Addr );
 int status = HAL_OK;
 int i2c_time_out = I2C_TIME_OUT_BASE+ count* I2C_TIME_OUT_BYTE;
// device_instance->serial.printf( "Sensor_IO_I2CWrite\n" );
// device_instance->serial.printf( " handle          = %08X\n", device_instance->i2c.getHandle( ) );
// device_instance->serial.printf( " Addr            = %02X\n", Addr );
// device_instance->serial.printf( " count           = %04X\n", count );
// device_instance->serial.printf( " pdata           = %08X\n", pdata );
 status = HAL_I2C_Master_Transmit( device_instance->i2c.getHandle( ), Addr, pdata, count, i2c_time_out);
 STM32IotNode_TraceU16( "Sensor_IO_I2CWrite, status: %04X\n", status );
 return status;
}

uint8_t Sensor_IO_Write(void *handle, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t nBytesToWrite)
{
 uint8_t Return = 0;
// device_instance->serial.printf( "Sensor_IO_Write\n" );
// device_instance->serial.printf( " handle          = %08X\n", handle );
// device_instance->serial.printf( " handle->address = %08X\n", ( ( DrvContextTypeDef* ) handle )->address );
// device_instance->serial.printf( " WriteAddr       = %02X\n", WriteAddr );
// device_instance->serial.printf( " nBytesToWrite   = %04X\n", nBytesToWrite );
// device_instance->serial.printf( " pBuffer         = %08X\n", pBuffer );
// for ( int i = 0; i < nBytesToWrite; i ++ )
//  device_instance->serial.printf( "  pBuffer[ %2d ]  = %02X\n", i, pBuffer[ i ] );
 Return = device_instance->i2c.write( ( ( DrvContextTypeDef* ) handle )->address, WriteAddr, pBuffer, nBytesToWrite );
// device_instance->serial.printf( " Return          = %02X = %d\n", Return, Return );
 return Return;
}

uint8_t Sensor_IO_Read(void *handle, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t nBytesToRead)
{
 uint8_t Return = 0;
// device_instance->serial.printf( "Sensor_IO_Read\n" );
// device_instance->serial.printf( " handle          = %08X\n", handle );
// device_instance->serial.printf( " handle->address = %08X\n", ( ( DrvContextTypeDef* ) handle )->address );
// device_instance->serial.printf( " ReadAddr        = %02X\n", ReadAddr );
// device_instance->serial.printf( " nBytesToRead    = %04X\n", nBytesToRead );
// device_instance->serial.printf( " pBuffer         = %08X\n", pBuffer );
 Return = device_instance->i2c.read( ( ( DrvContextTypeDef* ) handle )->address, ReadAddr, pBuffer, nBytesToRead);
// device_instance->serial.printf( " Return          = %02X = %d\n", Return, Return );
// for ( int i = 0; i < nBytesToRead; i ++ )
//  device_instance->serial.printf( "  pBuffer[ %2d ]  = %02X\n", i, pBuffer[ i ] );
 return Return;
}

};

void STM32IotNode_dmesg_flush()
{
#if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
#if DEVICE_DMESG_BUFFER_SIZE > 0
    if (codalLogStore.ptr > 0 && device_instance)
    {
        for (uint32_t i=0; i<codalLogStore.ptr; i++)
            ((STM32IotNode *)device_instance)->serial.putc(codalLogStore.buffer[i]);

        codalLogStore.ptr = 0;
    }
#endif
#endif
}
