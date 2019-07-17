#pragma once

namespace Eloquent {

    class AbstractPin {
    public:

        /**
         *
         * @param pin
         */
        AbstractPin(uint8_t pin) :
            _pin(pin) {

        }

        /**
         *
         */
        virtual void begin() = 0;

    protected:
        uint8_t _pin;
    };
}