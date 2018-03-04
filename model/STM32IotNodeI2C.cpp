/*
The MIT License (MIT)

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


#include "CodalConfig.h"
#include "STM32IotNode.h"
#include "STM32IotNodeI2C.h"

namespace codal
{

 extern STM32IotNode* device_instance;

int STM32IotNodeI2C::read( uint32_t address, uint8_t reg, uint8_t* data, uint32_t len )
{

 I2C_HandleTypeDef* Handle = ( I2C_HandleTypeDef* ) &_i2c.i2c.handle;
 device_instance->serial.printf( " STM32IotNodeI2C::read\n" );
 device_instance->serial.printf( "  Handle          = %08X\n", Handle );
 device_instance->serial.printf( "  address         = %08X\n", address );
 device_instance->serial.printf( "  reg             = %02X\n", reg );
 device_instance->serial.printf( "  len             = %04X\n", len );
 device_instance->serial.printf( "  data            = %08X\n", data );
 if ( HAL_I2C_Mem_Read( Handle, address | 1, ( uint16_t ) reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000 ) == HAL_OK )
  return DEVICE_OK;
 return DEVICE_I2C_ERROR;
}

int STM32IotNodeI2C::write( uint32_t address, uint8_t reg, const uint8_t* data, uint32_t len )
{
 I2C_HandleTypeDef* Handle = ( I2C_HandleTypeDef* ) &_i2c.i2c.handle;
 device_instance->serial.printf( " STM32IotNodeI2C::write\n" );
 device_instance->serial.printf( "  Handle          = %08X\n", Handle );
 device_instance->serial.printf( "  address         = %08X\n", address );
 device_instance->serial.printf( "  reg             = %02X\n", reg );
 device_instance->serial.printf( "  len             = %04X\n", len );
 device_instance->serial.printf( "  data            = %08X\n", data );
 if ( HAL_I2C_Mem_Write( Handle, address, ( uint16_t ) reg, I2C_MEMADD_SIZE_8BIT, data, len, 1000 ) == HAL_OK )
  return DEVICE_OK;
 return DEVICE_I2C_ERROR;
}

}
