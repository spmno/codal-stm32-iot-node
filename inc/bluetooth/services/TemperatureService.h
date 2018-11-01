/*
The MIT License (MIT)

Copyright (c) 2016 British Broadcasting Corporation.
This software is provided by Lancaster University by arrangement with the BBC.

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

#ifndef CODAL_TEMPERATURE_SERVICE_H
#define CODAL_TEMPERATURE_SERVICE_H

#include "CodalConfig.h"
#include "BLE.h"
#include "GattAttribute.h"
#include "GattCallbackParamTypes.h"
#include "Sensor.h"
#include "EventModel.h"

// UUIDs for our service and characteristics
extern const uint8_t  TemperatureServiceUUID[];
extern const uint8_t  TemperatureServiceDataUUID[];
extern const uint8_t  TemperatureServicePeriodUUID[];


/**
  * Class definition for the custom  Temperature Service.
  * Provides a BLE service to remotely read the temperature of the onboard sensor.
  */
class TemperatureService
{
  public:

    /**
      * Constructor.
      * Create a representation of the TemperatureService
      * @param ble The instance of a BLE device that we're running on.
      * @param temperature An instance of Sensor to use as our temperature source.
      */
    TemperatureService(BLE& ble, codal::Sensor& temperature);

    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten(const GattWriteCallbackParams *params);

    /**
     * Temperature update callback
     */
    void temperatureUpdate(codal::Event e);

  private:

    // Bluetooth stack we're running on.
    BLE& ble;
    codal::Sensor& temperature;

    // memory for our 8 bit temperature characteristic.
    int8_t temperatureDataCharacteristicBuffer;
    uint16_t temperaturePeriodCharacteristicBuffer;

    // Handles to access each characteristic when they are held by Soft Device.
    GattAttribute::Handle_t temperatureDataCharacteristicHandle;
    GattAttribute::Handle_t temperaturePeriodCharacteristicHandle;
};


#endif
