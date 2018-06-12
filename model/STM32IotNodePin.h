#ifndef STM32_IOT_NODE_PIN_H
#define STM32_IOT_NODE_PIN_H

#include "MbedPin.h"
#include "mbed.h"

namespace codal {
    class STM32IotNodePin : public codal::_mbed::Pin {
    protected:
        void* pin;

    public:
        int getAnalogValue() override;

        STM32IotNodePin(int id, PinNumber name, PinCapability capability);
    };
}

#endif