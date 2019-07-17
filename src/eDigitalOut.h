#pragma once

#include "Elo__WritesNumericValue.h"


namespace Eloquent {

    /**
     *
     */
    class DigitalOut : public WritesNumericValue {
    public:
        DigitalOut(uint8_t pin) :
            _pin(pin),
            _active_low(false) {
        }

        /**
         *
         */
        void begin() {
            pinMode(_pin, OUTPUT);
            turnOff();
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
            _wrote_value != LOW ? turnOff() : turnOn();
        }

    protected:
        uint8_t _pin;
        bool _active_low;


        void _write(float value) {
            digitalWrite(_pin, value != LOW ? HIGH : LOW);
        }
    };
}