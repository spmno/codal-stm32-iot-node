#include "TemperatureService.h"

TemperatureService::TemperatureService(BLE& ble, codal::Sensor& temperature) 
: ble(ble),
  temperature(temperature)
{

}