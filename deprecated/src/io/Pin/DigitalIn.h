// @public
#pragma once

#include "Pin.h"

namespace Eloquent {
    namespace Pin {
        /**
         * A class to interact with digital input pins
         */
        class DigitalIn : public Pin {
        public:
            /**
             * Contructor
             * @param pin Pin number
             */
            DigitalIn(uint8_t pin) :
                Pin(pin),
                _positive(HIGH) {

            }

            /**
             * Set pin mode to INPUT
             */
            void begin() {
                pinMode(_pin, INPUT);
            }

            /**
             * Set pin mode to INPUT_PULLUP
             */
            void pullup() {
                pinMode(_pin, INPUT_PULLUP);
            }

            /**
             * Active low means that the pin is `ON`
             * when digitalRead returns LOW
             */
            void activeLow() {
                _positive = LOW;
            }

            /**
             * Read the pin
             * @return whether the pin is ON
             */
            bool read() {
                _prev = isOn();
                _value = digitalRead(_pin);

                return isOn();
            }

            /**
             * Test if pin is ON
             * @return
             */
            bool isOn() {
                return _value == _positive;
            }

            /**
             * Test if pin is OFF
             * @return
             */
            bool isOff() {
                return !isOn();
            }

            /**
             * Test if the value changed from the last read
             * @return
             */
            bool changed() {
                return _prev != isOn();
            }

        protected:
            bool _positive;
            bool _prev;
        };
    }
}
