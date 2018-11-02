/**
  * Class definition for accelerometer.
  * Represents the accelerometer on the STM IOT node.
  */

#include "CodalConfig.h"
#include "STM32IotNode.h"
#include "STM32IotNodeMagnetometer.h"

namespace codal
{

  /**
    * Constructor.
    *
    * Create a representation of the accelerometer on the STM32 IOT node
    *
    */
  STM32IotNodeMagnetometer::STM32IotNodeMagnetometer( STM32L4xxI2C& i2c, CoordinateSpace& coordinateSpace )
  : Compass( coordinateSpace ), 
    _i2c( i2c ),
    magnetoDrv(&Lis3mdlMagDrv),
    isInitialized(false)
  {
  }

  uint8_t STM32IotNodeMagnetometer::getBestAdaptedODRValue(){
    if ( !samplePeriod )
      samplePeriod = 1;

    float frequency = 1000.0f / (float) samplePeriod;
    uint8_t odr = LIS3MDL_MAG_ODR_0_625_HZ;

    odr  = LIS3MDL_MAG_ODR_40_HZ;
    frequency = 40;
    
    samplePeriod = 1000.0f / frequency;
    return odr;
  }

  /**
  * Configures the accelerometer for G range and sample rate defined
  * in this object. The nearest values are chosen to those defined
  * that are supported by the hardware. The instance variables are then
  * updated to reflect reality.
  *
  * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the accelerometer could not be configured.
  *
  */
  int STM32IotNodeMagnetometer::configure( )
  {
    int ret = DEVICE_OK;
    MAGNETO_InitTypeDef LIS3MDL_InitStructureMag;

    if(Lis3mdlMagDrv.ReadID() != I_AM_LIS3MDL)
    {
      return DEVICE_I2C_ERROR;
    }
      
    /* MEMS configuration ------------------------------------------------------*/
    /* Fill the MAGNETO magnetometer structure */
    LIS3MDL_InitStructureMag.Register1 = LIS3MDL_MAG_TEMPSENSOR_DISABLE | LIS3MDL_MAG_OM_XY_HIGH | getBestAdaptedODRValue();
    LIS3MDL_InitStructureMag.Register2 = LIS3MDL_MAG_FS_4_GA | LIS3MDL_MAG_REBOOT_DEFAULT | LIS3MDL_MAG_SOFT_RESET_DEFAULT;
    LIS3MDL_InitStructureMag.Register3 = LIS3MDL_MAG_CONFIG_NORMAL_MODE | LIS3MDL_MAG_CONTINUOUS_MODE;
    LIS3MDL_InitStructureMag.Register4 = LIS3MDL_MAG_OM_Z_HIGH | LIS3MDL_MAG_BLE_LSB;
    LIS3MDL_InitStructureMag.Register5 = LIS3MDL_MAG_BDU_MSBLSB;
    /* Configure the MAGNETO magnetometer main parameters */
    magnetoDrv->Init(LIS3MDL_InitStructureMag);

    return ret;  
  }

  /**
  * Poll to see if new data is available from the hardware. If so, update it.
  * n.b. it is not necessary to explicitly call this function to update data
  * (it normally happens in the background when the scheduler is idle), but a check is performed
  * if the user explicitly requests up to date data.
  *
  * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the update fails.
  *
  */
  int STM32IotNodeMagnetometer::requestUpdate()
  {
    if ( !isInitialized )
      configure();
    int16_t piData[3];

    if(magnetoDrv != NULL)
    {
      if(magnetoDrv->GetXYZ!= NULL)
      {
        magnetoDrv->GetXYZ(piData);
        sample.x = piData[0] / 100;
        sample.y = piData[1] / 100;
        sample.z = piData[2] / 100;
        return DEVICE_OK;
      }
    }
    return DEVICE_I2C_ERROR;
  }

}
