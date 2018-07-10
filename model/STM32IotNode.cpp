#include "STM32IotNode.h"
#include "CodalDmesg.h"

using namespace codal;
void STM32IotNode_dmesg_flush();

static STM32IotNode *device_instance = NULL;

/**
  * Constructor.
  *
  * Create a representation of a device, which includes member variables
  * that represent various device drivers used to control aspects of the STM32 IOT node.
  */
STM32IotNode::STM32IotNode() : io()
{
    // Clear our status
    status = 0;
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

void STM32IotNode_Trace( const char* Format )
{
/*
 if ( device_instance )
  device_instance->serial.printf( Format );
*/
}

void STM32IotNode_TraceU16( const char* Format, uint16_t Value )
{
/*
 if ( device_instance )
  device_instance->serial.printf( Format, Value );
*/
}

void STM32IotNode_dmesg_flush()
{
#if CONFIG_ENABLED(DMESG_SERIAL_DEBUG)
/*
#if DEVICE_DMESG_BUFFER_SIZE > 0
    if (codalLogStore.ptr > 0 && device_instance)
    {
        for (uint32_t i=0; i<codalLogStore.ptr; i++)
            ((STM32IotNode *)device_instance)->serial.putc(codalLogStore.buffer[i]);

        codalLogStore.ptr = 0;
    }
#endif
*/
#endif
}
