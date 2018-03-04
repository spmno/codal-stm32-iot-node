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

/**
  * Class definition for accelerometer.
  * Represents the accelerometer on the STM IOT node.
  */

#include "CodalConfig.h"
#include "STM32IotNode.h"
#include "STM32IotNodeAccelerometer.h"

namespace codal
{

 extern STM32IotNode* device_instance;

/**
  * Constructor.
  *
  * Create a representation of the accelerometer on the STM32 IOT node
  *
  */
STM32IotNodeAccelerometer::STM32IotNodeAccelerometer( STM32IotNodeI2C& i2c )
: _i2c( i2c )
{
}

Sample3D STM32IotNodeAccelerometer::getSample()
{
 device_instance->serial.printf( " STM32IotNodeAccelerometer::getSample\n" );
 if ( !DrvContext.isInitialized )
 {
  device_instance->serial.printf( " Initialize\n" );
//  ( ( ACCELERO_Drv_t* ) DrvContext.pVTable )->Init( &DrvContext );
//  ( ( ACCELERO_Drv_t* ) DrvContext.pVTable )->Sensor_Enable( &DrvContext );
  DrvContext.isInitialized = 1;
 }

 device_instance->serial.printf( " Read Sample\n" );
 Sample3D Sample;
 SensorAxes_t Data;
 if ( ( ( ACCELERO_Drv_t* ) DrvContext.pVTable )->Get_Axes( &DrvContext, &Data ) == COMPONENT_OK )
 {
  Sample.x = Data.AXIS_X;
  Sample.y = Data.AXIS_Y;
  Sample.z = Data.AXIS_Z;
 }
 return Sample;
}

}
