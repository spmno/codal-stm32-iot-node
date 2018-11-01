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

#ifndef CODAL_EVENT_SERVICE_H
#define CODAL_EVENT_SERVICE_H

#include "CodalConfig.h"
#include "ble/BLE.h"
#include "Event.h"
#include "EventModel.h"

// UUIDs for our service and characteristics
extern const uint8_t  EventServiceUUID[];
extern const uint8_t  EventServiceEventCharacteristicUUID[];
extern const uint8_t  EventServiceClientEventCharacteristicUUID[];
extern const uint8_t  EventServiceRequirementsCharacteristicUUID[];
extern const uint8_t  EventServiceClientRequirementsCharacteristicUUID[];

struct EventServiceEvent
{
    uint16_t    type;
    uint16_t    reason;
};


/**
  * Class definition for a BLE Event Service.
  * Provides a BLE gateway onto an Event Model.
  */
class EventService : public Component
{
    public:

    /**
      * Constructor.
      * Create a representation of the EventService
      * @param _ble The instance of a BLE device that we're running on.
      * @param _messageBus An instance of an EventModel which events will be mirrored from.
      */
    EventService(BLEDevice &_ble, EventModel &_messageBus);

    /**
     * Periodic callback from  scheduler.
     * If we're no longer connected, remove any registered Message Bus listeners.
     */
    virtual void idleTick();

    /**
      * Callback. Invoked when any of our attributes are written via BLE.
      */
    void onDataWritten(const GattWriteCallbackParams *params);

    /**
      * Callback. Invoked when any events are sent on the board message bus.
      */
    void onEvent(Event evt);

    /**
      * Read callback on Requirements characteristic.
      *
      * Used to iterate through the events that the code on this micro:bit is interested in.
      */
    void onRequirementsRead(GattReadAuthCallbackParams *params);

    private:

    // Bluetooth stack we're running on.
    BLEDevice           &ble;
	EventModel	        &messageBus;

    // memory for our event characteristics.
    EventServiceEvent   clientEventBuffer;
    EventServiceEvent   EventBuffer;
    EventServiceEvent   RequirementsBuffer;
    EventServiceEvent   clientRequirementsBuffer;

    // handles on this service's characterisitics.
    GattAttribute::Handle_t EventCharacteristicHandle;
    GattAttribute::Handle_t clientRequirementsCharacteristicHandle;
    GattAttribute::Handle_t clientEventCharacteristicHandle;
    GattCharacteristic *RequirementsCharacteristic;

    // Message bus offset last sent to the client...
    uint16_t messageBusListenerOffset;

};


#endif
