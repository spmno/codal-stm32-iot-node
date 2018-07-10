#ifndef STM32_IOT_NODE_H
#define STM32_IOT_NODE_H

#include "CodalDevice.h"
#include "CodalComponent.h"
#include "CodalCompat.h"

#include "NotifyEvents.h"
#include "MessageBus.h"

#include "STM32IotNodeIO.h"

// Status flag values
#define DEVICE_INITIALIZED                    0x01

/**
 * Class definition for a STM32 IOT node.
 *
 * Represents the device as a whole, and includes member variables that represent various device drivers
 * used to control aspects of the STM32 IOT node.
 */
namespace codal
{
    class STM32IotNode : public CodalDevice, public CodalComponent
    {
        public:
            MessageBus                  messageBus;
            STM32IotNodeIO              io;
            /**
             * Constructor.
             */
            STM32IotNode();

            /**
             * Post constructor initialisation method.
             */
            virtual int init();

            /**
             * A periodic callback invoked by the fiber scheduler idle thread.
             * We use this for any low priority, background housekeeping.
             */
            virtual void idleCallback();

            /**
             * A periodic callback invoked by the fiber scheduler every SCHEDULER_TICK_PERIOD_MS.
             */
            virtual void periodicCallback();

            /**
             * A listener to perform actions as a result of Message Bus reflection.
             *
             * In some cases we want to perform lazy instantiation of components, such as
             * the compass and the accelerometer, where we only want to add them to the idle
             * fiber when someone has the intention of using these components.
             */
            void onListenerRegisteredEvent(Event evt);
    };
}
#endif
