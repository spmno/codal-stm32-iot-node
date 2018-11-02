#ifndef STM32_IOT_NODE_DISTANCE_H
#define STM32_IOT_NODE_DISTANCE_H

#include "CodalConfig.h"
#include "codal-core/inc/driver-models/Sensor.h"

#include "stm32l4xxPin.h"
#include "stm32l4xxI2C.h"
#include "stm32l475e_iot01.h"

#include "../vl53l0x/VL53L0X_Driver_HL.h"
#include "../vl53l0x/vl53l0x_def.h"
#include "../vl53l0x/vl53l0x_api.h"
#include "../vl53l0x/vl53l0x_tof.h"

namespace codal
{
  /**
   * Represents the gyroscope on the STM32 IOT node.
   */
 class STM32IotNodeDistance : public Sensor
 {

   VL53L0X_Dev_t VL53L0X_Dev;

//   VL53L0X_Dev_t VL53L0X_Dev =
//   {
//    .Data       = { 0 },
//    .I2cDevAddr = VL53L0X_ADDRESS_DEFAULT,
//   };

   DrvContextTypeDef DrvContext =
   {
    .who_am_i      = 0xEE,
    .ifType        = 0,
    .address       = VL53L0X_ADDRESS_DEFAULT,
    .spiDevice     = 0,
    .instance      = 0,
    .isInitialized = 0,
    .isEnabled     = 0,
    .isCombo       = 0,
    .pData         = ( void * ) &VL53L0X_Dev,
    .pVTable       = ( void * ) &VL53L0X_Drv,
    .pExtVTable    = 0,
   };

   STM32L4xxI2C& _i2c;

   public:
   /**
    * Constructor.
    */
    STM32IotNodeDistance( STM32L4xxI2C& i2c );

   protected:

    /**
     * Configures the temperature for celsuiu range and sample rate defined
     * in this object. The nearest values are chosen to those defined
     * that are supported by the hardware. The instance variables are then
     * updated to reflect reality.
     *
     * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the temperature could not be configured.
     *
     * @note This method should be overidden by the hardware driver to implement the requested
     * changes in hardware.
     */
    virtual int configure();

    /**
      * Implement this function to receive a function call after the devices'
      * device model has been instantiated.
      */
    virtual int init();

    /**
     * Read the value from underlying hardware.
     */
    virtual int readValue();


    };
}

#endif
