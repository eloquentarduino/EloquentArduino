#pragma once

#include "Pin.h"

namespace Eloquent {
    namespace Pin {
        /**
         *
         */
        class DigitalOut : public Pin {
        public:
            DigitalOut(uint8_t pin) :
                Pin(pin),
                _positive(HIGH) {

            }

            /**
             * Set pin mode to OUTPUT
             */
            void begin() {
                pinMode(_pin, OUTPUT);
            }

            /**
             * Set output as active low
             * From now on, logical on == LOW
             */
            void activeLow() {
                _positive = LOW;
            }

            /**
             * Write logical HIGH
             */
            void turnOn() {
                write(_positive);
            }

            /**
             * Write logical LOW
             */
            void turnOff() {
                write(!_positive);
            }

            /**
             * Toggle the state
             */
            void toggle() {
                _value == _positive ? turnOff() : turnOn();
            }

            /**
             * Blink pin
             * @param times
             * @param interval in millis
             */
            void blink(uint8_t times, uint16_t interval = 100) {
                while (times-- > 0) {
                    turnOn();
                    delay(interval);
                    turnOff();
                    delay(interval);
                }
            }

        protected:
            bool _positive;

            /**
              * Write to pin
              * @param value
              */
            void write(bool value) {
                digitalWrite(_pin, value ? HIGH : LOW);
            }
        };
    }
}