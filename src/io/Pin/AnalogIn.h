#pragma once

#include "Pin.h"

namespace Eloquent {
    namespace Pin {

        /**
         * A class to interact with analog input pins
         */
        class AnalogIn : public Pin {
        public:
            /**
             * Contructor
             * @param pin Pin number
             */
            AnalogIn(uint8_t pin) :
                Pin(pin),
                _prev(0) {

            }

            /**
             * Set pin mode to INPUT
             */
            void begin() {
                pinMode(_pin, INPUT);
            }

            /**
             * Read the pin
             * @return whether the pin is ON
             */
            uint16_t read() {
                _prev = _value;
                _value = analogRead(_pin);

                return value();
            }

            /**
             * Get pin's previous value
             * @return
             */
            uint16_t prev() {
                return _prev;
            }

            /**
             * Get pin's change from last read
             * @return
             */
            int16_t delta() {
                return _value - _prev;
            }

            /**
             * Get absolute value of delta()
             * @return
             */
            uint16_t absDelta() {
                return abs(delta());
            }

        protected:
            uint16_t _prev;
        };
    }
}