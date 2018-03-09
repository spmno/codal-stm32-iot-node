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

#include "CodalConfig.h"
#include "Accelerometer.h"
#include "MbedPin.h"

#include "STM32IotNodeI2C.h"

#include "LSM6DSL_ACC_GYRO_driver_HL.h"

namespace codal
{
  /**
   * Represents a accelerometer on the STM32 IOT node.
   */
 class STM32IotNodeAccelerometer : protected codal::Accelerometer
 {
   LSM6DSL_X_Data_t LSM6DSL_X_Data =
   {
    &LSM6DSL_Combo_Data[ 0 ],
    0.0,
   };

   ACCELERO_Data_t ACCELERO_Data =
   {
    ( void * ) &LSM6DSL_X_Data,
    0,
   };

   DrvContextTypeDef DrvContext =
   {
    LSM6DSL_ACC_GYRO_WHO_AM_I,
    0,
    LSM6DSL_ACC_GYRO_I2C_ADDRESS_LOW,
    0,
    0,
    0,
    0,
    0,
    &ACCELERO_Data,
    ( void * ) &LSM6DSL_X_Drv,
    0,
   };

   STM32IotNodeI2C& _i2c;

   public:
   /**
    * Constructor.
    */
    STM32IotNodeAccelerometer( STM32IotNodeI2C& i2c, codal::CoordinateSpace& coordinateSpace );

    using codal::Accelerometer::getSample;
    using codal::Accelerometer::getX;
    using codal::Accelerometer::getY;
    using codal::Accelerometer::getZ;
    using codal::Accelerometer::getPitch;
    using codal::Accelerometer::getPitchRadians;
    using codal::Accelerometer::getRoll;
    using codal::Accelerometer::getRollRadians;

    /**
     * Poll to see if new data is available from the hardware. If so, update it.
     * n.b. it is not necessary to explicitly call this funciton to update data
     * (it normally happens in the background when the scheduler is idle), but a check is performed
     * if the user explicitly requests up to date data.
     *
     * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the update fails.
     *
     * @note This method should be overidden by the hardware driver to implement the requested
     * changes in hardware.
     */
    int STM32IotNodeAccelerometer::requestUpdate();

//   /**
//     * Reads the currently configured sample range of the accelerometer.
//     *
//     * @return The sample range, in g.
//     */
//    virtual int getRange();
//
//   /**
//     * Reads the last accelerometer value stored, and in the coordinate system defined in the constructor.
//     * @return The force measured in each axis, in milli-g.
//     */
//    Sample3D getSample( );
//
//   /**
//     * Reads the currently configured sample rate of the accelerometer.
//     *
//     * @return The time between samples, in milliseconds.
//     */
//    virtual int getPeriod();
//
//   /**
//     * reads the value of the x axis from the latest update retrieved from the accelerometer,
//     * using the default coordinate system as specified in the constructor.
//     *
//     * @return the force measured in the x axis, in milli-g.
//     */
//    int getX();
//
//   /**
//     * reads the value of the y axis from the latest update retrieved from the accelerometer,
//     * using the default coordinate system as specified in the constructor.
//     *
//     * @return the force measured in the y axis, in milli-g.
//     */
//    int getY();
//
//   /**
//     * reads the value of the z axis from the latest update retrieved from the accelerometer,
//     * using the default coordinate system as specified in the constructor.
//     *
//     * @return the force measured in the z axis, in milli-g.
//     */
//    int getZ();
//
//   /**
//     * Attempts to set the sample rate of the accelerometer to the specified value (in ms).
//     *
//     * @param period the requested time between samples, in milliseconds.
//     * @return DEVICE_OK on success, DEVICE_I2C_ERROR is the request fails.
//     *
//     * @note The requested rate may not be possible on the hardware. In this case, the
//     * nearest lower rate is chosen.
//     *
//     * @note This method should be overriden (if supported) by specific accelerometer device drivers.
//     */
//    virtual int setPeriod(int period);
//
//   /**
//     * Attempts to set the sample range of the accelerometer to the specified value (in g).
//     *
//     * @param range The requested sample range of samples, in g.
//     *
//     * @return DEVICE_OK on success, DEVICE_I2C_ERROR is the request fails.
//     *
//     * @note The requested range may not be possible on the hardware. In this case, the
//     * nearest lower range is chosen.
//     *
//     * @note This method should be overriden (if supported) by specific accelerometer device drivers.
//     */
//    virtual int setRange(int range);

    };
}

#endif
