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

#ifndef STM32_IOT_NODE_H
#define STM32_IOT_NODE_H

#include "CodalHeapAllocator.h"
#include "codal-core/inc/types/Event.h"
#include "CodalDevice.h"
#include "ErrorNo.h"
#include "MbedTimer.h"
#include "CodalCompat.h"
#include "CodalComponent.h"
#include "CodalDmesg.h"
#include "CoordinateSystem.h"
#include "ManagedType.h"
#include "ManagedString.h"
#include "NotifyEvents.h"

#include "Button.h"
#include "MbedSerial.h"
#include "STM32IotNodeAccelerometer.h"
#include "STM32IotNodeDistance.h"
#include "STM32IotNodeGyroscope.h"
#include "STM32IotNodeI2C.h"
#include "STM32IotNodeIO.h"
#include "STM32IotNodeHumidity.h"
#include "STM32IotNodePressure.h"
#include "STM32IotNodeTemperature.h"
#include "CodalFiber.h"
#include "MessageBus.h"


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

            codal::_mbed::Serial        serial;
            codal::_mbed::Timer         timer;
            codal::CoordinateSpace      coordinateSpace;
            MessageBus                  messageBus;
            STM32IotNodeIO              io;
            STM32IotNodeI2C             i2c;
            STM32IotNodeAccelerometer   accelerometer;
            STM32IotNodeDistance        distance;
            STM32IotNodeGyroscope       gyroscope;
            STM32IotNodeHumidity        humidity;
            STM32IotNodePressure        pressure;
            STM32IotNodeTemperature     temperature;
            Button                      buttonA;

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
