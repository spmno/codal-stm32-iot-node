/*
The MIT License (MIT)

Copyright (c) 2016 Lancaster University, UK.
Copyright (c) 2018 Paul ADAM, Europe.

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

#ifndef STM32_IOT_NODE_ACCEL_H
#define STM32_IOT_NODE_ACCEL_H

#include "mbed.h"
#include "CodalConfig.h"
#include "CoordinateSystem.h"
#include "MbedPin.h"

#include "LSM6DSL_ACC_GYRO_driver_HL.h"

namespace codal
{
    /**
     * Represents a accelerometer on the STM32 IOT node.
     */
    class STM32IotNodeAccelerometer
    {
        DrvContextTypeDef DrvContext =
        {
            LSM6DSL_ACC_GYRO_WHO_AM_I,
            0,
            LSM6DSL_ACC_GYRO_I2C_ADDRESS_HIGH,
            0,
            0,
            0,
            0,
            0,
            &LSM6DSL_Combo_Data[ 0 ],
            ( void * ) &LSM6DSL_X_Drv,
            0,
        };
        /**
         * Constructor.
         */
        STM32IotNodeAccelerometer();

        /**
          * Reads the last accelerometer value stored, and in the coordinate system defined in the constructor.
          * @return The force measured in each axis, in milli-g.
          */
        Sample3D getSample();

    };
}

#endif
