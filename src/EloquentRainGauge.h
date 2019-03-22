#pragma once

#include "EloquentEEValue.h"
#include "EloquentInterruptCounter.h"


#ifndef RAING_GAUGE_TO_MM
#define RAIN_GAUGE_TO_MM 0.2794
#endif

#ifndef RAING_GAUGE_TO_INCHES
#define RAIN_GAUGE_TO_INCHES 0.011
#endif


namespace Eloquent {

    /**
     * A rain gauge sensor.
     * It listens to interrupts and adds up a counter.
     * Provides conversion to mm/inches of rain.
     * Persists the counter to EEPROM.
     */
    class RaingGauge {

    public:
        RaingGauge(uint8_t interruptPin, uint16_t eepromAddress, uint8_t mode = FALLING) :
            _eeprom(eepromAddress),
            _counter(interruptPin, mode) {

        }

        /**
         * @see Counter
         */
        RaingGauge* operator++() {
            _counter++;

            return this;
        }

        /**
         * @see Counter
         * @return
         */
        uint8_t pin() {
            return _counter.pin();
        }

        /**
         * @see Counter
         * @return
         */
        uint8_t mode() {
            return _counter.mode();
        }

        /**
         * Init sensor
         */
        void begin() {
            _eeprom.begin(0);
            _counter.begin(_eeprom.value());

            debounce(30);
        }

        /**
         * Reset counter
         */
        void reset() {
            _eeprom.set(0);
            _counter.reset();
        }

        /**
         *
         */
        void watch() {
            _eeprom = _counter.count();
        }

        /**
         * Debounce interrupt counter
         * @param interval
         */
        void debounce(uint32_t interval) {
            _counter.debounce(interval);
        }

        /**
         * Get raw count
         * @return
         */
        uint32_t count() {
            return _counter.count();
        }

        /**
         * Get fallen rain, in mm
         * @return
         */
        float mm() {
            return _counter.count() * RAIN_GAUGE_TO_MM;
        }

        /**
         * Get fallen rain, in inches
         * @return
         */
        float inches() {
            return _counter.count() * RAIN_GAUGE_TO_INCHES;
        }

    protected:
        uint8_t _pin;
        uint8_t _mode;
        eeValue<uint32_t> _eeprom;
        InterruptCounter _counter;
    };
}