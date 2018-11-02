/**
  * Class definition for humidity.
  * Represents the humidity on the STM IOT node.
  */

#include "CodalConfig.h"
#include "STM32IotNode.h"
#include "STM32IotNodeHumidity.h"

namespace codal
{
  /**
    * Constructor.
    *
    * Create a representation of the humidity on the STM32 IOT node
    *
    */
  STM32IotNodeHumidity::STM32IotNodeHumidity( STM32L4xxI2C& i2c )
  :  Sensor(DEVICE_ID_HUMIDITY), 
    _i2c( i2c ),
    hsensor_drv(&HTS221_H_Drv),
    isInitialized(false)
  {
    configure();
    updateSample( );
  }

  /**
  * Configures output data rate register
  *
  *
  */

  void updateODR(uint8_t odr){
    uint8_t tmp;
    /* Read CTRL_REG1 */
    tmp = SENSOR_IO_Read(HTS221_I2C_ADDRESS, HTS221_CTRL_REG1);
    
    /* Set default ODR */
    tmp &= ~HTS221_ODR_MASK;
    tmp |= odr & HTS221_ODR_MASK; /*Set ODR*/
    
    /* Apply settings to CTRL_REG1 */
    SENSOR_IO_Write(HTS221_I2C_ADDRESS, HTS221_CTRL_REG1, tmp);
  }

  uint8_t getBestAdaptedODRValue(float& frequency){
    uint8_t odr = 0; 

    if(frequency <= 5.f){
      odr = 1; //frequency = 1Hz
      frequency = 1.f;
    }
    else if (frequency <= 10.f){
      odr = 2; //frequency = 7Hz
      frequency = 7.f;
    }
    else if (frequency > 10.f){
      odr = 3; //frequency = 12.5Hz
      frequency = 12.5f;    
    }
    else{
      odr = 0; //one shot
      frequency = 0;
    }
    return odr;

  }

  /**
  * Configures the humidity range defined
  * in this object. The nearest values are chosen to those defined
  * that are supported by the hardware. The instance variables are then
  * updated to reflect reality.
  *
  * @return DEVICE_OK on success, DEVICE_I2C_ERROR if the humidity could not be configured.
  *
  */

  int STM32IotNodeHumidity::configure()
  {
    int ret = DEVICE_OK;
    
    if(hsensor_drv->ReadID(HTS221_I2C_ADDRESS) != HTS221_WHO_AM_I_VAL){
      ret = DEVICE_I2C_ERROR;
    }
    else{ 
      hsensor_drv->Init(HTS221_I2C_ADDRESS);
    }
    
    if ( !samplePeriod )
      samplePeriod = 1;

    float frequency = 1000.0f / (float) samplePeriod;

    uint8_t odr = getBestAdaptedODRValue(frequency); 
    updateODR(odr);

    samplePeriod = 1000.0f / frequency;

    isInitialized = true;
    return ret;
  }


  /**
  * Poll to see if new data is available from the hardware. If so, update it.
  * n.b. it is not necessary to explicitly call this function to update data
  * (it normally happens in the background when the scheduler is idle), but a check is performed
  * if the user explicitly requests up to date data.
  *
  * @return The value on success, DEVICE_I2C_ERROR if the update fails.
  *
  */

  int STM32IotNodeHumidity::readValue()
  {
    if(!isInitialized)
      configure();
    return (int) hsensor_drv->ReadHumidity(HTS221_I2C_ADDRESS) * 10;
  }

}
