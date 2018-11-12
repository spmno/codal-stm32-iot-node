/*
#include "stm32.h"
#include "STM32IotNode.h"

#include "Blink.h"
#include "TemperatureAlarm.h"

using namespace codal;
STM32IotNode iotNode;

int main()
{
    iotNode.init();
    #if defined(BLE_TEMPERATURE_ALARM_SAMPLE)
    TemperatureAlarm_main(iotNode);
    #elif defined(HTS221_SAMPLE)
    HTS221_main(iotNode)
    #elif defined(LIS3MDL_SAMPLE)
    LIS3MDL_main(iotNode)
    #elif defined(LSM6DSL_SAMPLE)
    LSM6DSL_main(iotNode)
    #elif defined(LSM6DSL_GYRO_SAMPLE)
    LSM6DSLGyro_main(iotNode)
    #elif defined(LSM6DSL_ACCELERO_SAMPLE)
    LSM6DSLAccelero_main(iotNode)
    #elif defined(LPS22HB_SAMPLE)
    LPS22HB_main(iotNode)
    #elif defined(VL53L0X_SAMPLE)
    _main(iotNode)
    #elif defined(BUTTON_SAMPLE)
    BUTTON_main(iotNode)
    #elif defined(GPIO_SAMPLE)
    GPIO_main(iotNode)
    #elif defined(ADC_SAMPLE)
    ADC_main(iotNode)
    #elif defined(FLASH_MEMORY_SAMPLE)
    FLASH_MEMORY_main(iotNode)
    #else
    Blink_main(iotNode);
    #endif
}
*/

int main() {
    return 0;
}