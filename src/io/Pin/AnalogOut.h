#pragma once

#include "Pin.h"

namespace Eloquent {
    namespace Pin {

        /**
         * A class to interact with analog output pins
         */
        class AnalogOut : public Pin {
        public:
            /**
             * Contructor
             * @param pin Pin number
             */
            AnalogOut(uint8_t pin) :
                Pin(pin) {

            }

            /**
             * Set pin mode to OUTPUT
             */
            void begin() {
                pinMode(_pin, OUTPUT);
            }

            /**
             * Write to pin
             * @param value
             * @return the written value
             */
            uint16_t write(uint16_t value) {
                _value = analogWrite(value);

                return this->value();
            }
        };
    }
}