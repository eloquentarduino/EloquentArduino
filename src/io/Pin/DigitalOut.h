#pragma once

#include "Pin.h"

namespace Eloquent {
    namespace Pin {
        /**
         *
         */
        class DigitalOut : public Pin {
        public:
            DigitalOut(uint8_t pin) : Pin(pin) {

            }

            /**
             *
             */
            void begin() {
                pinMode(_pin, OUTPUT);
            }

            /**
             *
             */
            void activeLow() {
                _active_low = true;
            }

            /**
             *
             */
            void turnOn() {
                write(HIGH);
            }

            /**
             *
             */
            void turnOff() {
                write(LOW);
            }

            /**
             *
             */
            void toggle() {
                _value == LOW ? turnOn() : turnOff();
            }

            /**
             *
             * @param times
             * @param interval
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
            bool _active_low = false;

            /**
              * Write to pin
              * @param value
              */
            void write(float value) {
                if (_active_low)
                    digitalWrite(_pin, value == LOW ? HIGH : LOW);
                else
                    digitalWrite(_pin, value == LOW ? LOW : HIGH);
            }
        };
    }
}