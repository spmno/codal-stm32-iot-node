#ifndef STM32_IOT_NODE_GYRO_H
#define STM32_IOT_NODE_GYRO_H

#include "CodalConfig.h"
#include "codal-core/inc/driver-models/Gyroscope.h"

#include "stm32l4xxPin.h"
#include "stm32l4xxI2C.h"
#include "stm32l475e_iot01.h"

#include "gyro.h"
#include "lsm6dsl.h"

namespace codal
{
  /**
   * Represents the gyroscope on the STM32 IOT node.
   */
 class STM32IotNodeGyroscope : protected Gyroscope
 {  
   STM32L4xxI2C& _i2c;
   GYRO_DrvTypeDef* gyroscopeDrv;
   bool isInitialized;

   public:
   /**
    * Constructor.
    */
    STM32IotNodeGyroscope( STM32L4xxI2C& i2c, CoordinateSpace& coordinateSpace );

    using Gyroscope::getPeriod;
    using Gyroscope::getRange;
    using Gyroscope::getSample;
    using Gyroscope::getX;
    using Gyroscope::getY;
    using Gyroscope::getZ;

   protected:

    /**
     * Configures the gyroscope for G range and sample rate defined
     * in this object. The nearest values are chosen to those defined
     * that are supported by the hardware. The instance variables are then
     * updated to reflect reality.
     *
     * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the gyroscope could not be configured.
     *
     * @note This method should be overidden by the hardware driver to implement the requested
     * changes in hardware.
     */
    virtual int configure();

    /**
     * Poll to see if new data is available from the hardware. If so, update it.
     * n.b. it is not necessary to explicitly call this function to update data
     * (it normally happens in the background when the scheduler is idle), but a check is performed
     * if the user explicitly requests up to date data.
     *
     * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the update fails.
     *
     * @note This method should be overidden by the hardware driver to implement the requested
     * changes in hardware.
     */
    virtual int requestUpdate();
    
    private:
    uint8_t getBestAdaptedODRValue();
    uint8_t getBestAdaptedFSValue();

    };
}

#endif
