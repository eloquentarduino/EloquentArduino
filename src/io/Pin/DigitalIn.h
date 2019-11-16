#pragma once

#include "Pin.h"

namespace Eloquent {
    namespace Pin {
        /**
         *
         */
        class DigitalIn : public Pin {
        public:
            DigitalIn(uint8_t pin) : Pin(pin) {

            }

            /**
             *
             */
            void begin() {
                pinMode(_pin, INPUT);
            }

            /**
             *
             */
            void activeLow() {
                _active_low = true;
            }

            /**
             * Test if pin is ON
             * @param read
             * @return
             */
            bool isOn(bool read = true) {
                if (read)
                    _value = digitalRead(_pin);

                return _active_low ? _value == LOW : _value == HIGH;
            }

        protected:
            bool _active_low = false;
        };
    }
}