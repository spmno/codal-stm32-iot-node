#include "TemperatureService.h"
#include "CodalConfig.h"
#include "UUID.h"
#include "GattCharacteristic.h"

using namespace codal;
/**
  * Constructor.
  * Create a representation of the TemperatureService
  * @param _ble The instance of a BLE device that we're running on.
  * @param _temperature An instance of Thermometer to use as our temperature source.
  */
TemperatureService::TemperatureService(BLE &_ble, codal::Sensor &_temperature) :
        ble(_ble), temperature(_temperature)
{
    // Create the data structures that represent each of our characteristics in Soft Device.
    GattCharacteristic  temperatureDataCharacteristic(TemperatureServiceDataUUID, (uint8_t *)&temperatureDataCharacteristicBuffer, 0,
    sizeof(temperatureDataCharacteristicBuffer), GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY);

    GattCharacteristic  temperaturePeriodCharacteristic(TemperatureServicePeriodUUID, (uint8_t *)&temperaturePeriodCharacteristicBuffer, 0,
    sizeof(temperaturePeriodCharacteristicBuffer), GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_WRITE);

    // Initialise our characteristic values.
    temperatureDataCharacteristicBuffer = 0;
    temperaturePeriodCharacteristicBuffer = temperature.getPeriod();

    // Set default security requirements
    temperatureDataCharacteristic.requireSecurity(SecurityManager::SECURITY_MODE_ENCRYPTION_OPEN_LINK);
    temperaturePeriodCharacteristic.requireSecurity(SecurityManager::SECURITY_MODE_ENCRYPTION_OPEN_LINK);

    GattCharacteristic *characteristics[] = {&temperatureDataCharacteristic, &temperaturePeriodCharacteristic};
    GattService         service(TemperatureServiceUUID, characteristics, sizeof(characteristics) / sizeof(GattCharacteristic *));

    ble.addService(service);

    temperatureDataCharacteristicHandle = temperatureDataCharacteristic.getValueHandle();
    temperaturePeriodCharacteristicHandle = temperaturePeriodCharacteristic.getValueHandle();

    ble.gattServer().write(temperatureDataCharacteristicHandle,(uint8_t *)&temperatureDataCharacteristicBuffer, sizeof(temperatureDataCharacteristicBuffer));
    ble.gattServer().write(temperaturePeriodCharacteristicHandle,(uint8_t *)&temperaturePeriodCharacteristicBuffer, sizeof(temperaturePeriodCharacteristicBuffer));

    ble.onDataWritten(this, &TemperatureService::onDataWritten);
    if (EventModel::defaultEventBus)
        EventModel::defaultEventBus->listen(DEVICE_ID_THERMOMETER, SENSOR_UPDATE_NEEDED, this, &TemperatureService::temperatureUpdate, MESSAGE_BUS_LISTENER_IMMEDIATE);
}

/**
  * Temperature update callback
  */
void TemperatureService::temperatureUpdate(codal::Event)
{
    if (ble.getGapState().connected)
    {
        temperatureDataCharacteristicBuffer = temperature.getValue();
        ble.gattServer().write(temperatureDataCharacteristicHandle,(uint8_t *)&temperatureDataCharacteristicBuffer, sizeof(temperatureDataCharacteristicBuffer));
    }
}

/**
  * Callback. Invoked when any of our attributes are written via BLE.
  */
void TemperatureService::onDataWritten(const GattWriteCallbackParams *params)
{
    if (params->handle == temperaturePeriodCharacteristicHandle && params->len >= sizeof(temperaturePeriodCharacteristicBuffer))
    {
        temperaturePeriodCharacteristicBuffer = *((uint16_t *)params->data);
        temperature.setPeriod(temperaturePeriodCharacteristicBuffer);

        // The accelerometer will choose the nearest period to that requested that it can support
        // Read back the ACTUAL period it is using, and report this back.
        temperaturePeriodCharacteristicBuffer = temperature.getPeriod();
        ble.gattServer().write(temperaturePeriodCharacteristicHandle, (const uint8_t *)&temperaturePeriodCharacteristicBuffer, sizeof(temperaturePeriodCharacteristicBuffer));
    }
}


const uint8_t  TemperatureServiceUUID[] = {
    0xe9,0x5d,0x61,0x00,0x25,0x1d,0x47,0x0a,0xa0,0x62,0xfa,0x19,0x22,0xdf,0xa9,0xa8
};

const uint8_t  TemperatureServiceDataUUID[] = {
    0xe9,0x5d,0x92,0x50,0x25,0x1d,0x47,0x0a,0xa0,0x62,0xfa,0x19,0x22,0xdf,0xa9,0xa8
};

const uint8_t  TemperatureServicePeriodUUID[] = {
    0xe9,0x5d,0x1b,0x25,0x25,0x1d,0x47,0x0a,0xa0,0x62,0xfa,0x19,0x22,0xdf,0xa9,0xa8
};