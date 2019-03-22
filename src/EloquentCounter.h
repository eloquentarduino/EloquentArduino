#pragma once


/**
 * A simple counter you can only increment.
 * It provides also the average count per seconds and debounce facilities
 */


namespace Eloquent {


    class Counter {
    public:
        /**
         * Just an alias for `increment()`
         */
        Counter* operator++() {
            increment();

            return this;
        }
        
        /**
         * Init the counter
         */
        void begin(uint32_t initial = 0) {
            _start = millis();
            _last  = _start;
            _count = initial;
        }

        /**
         * Reset count to 0
         */
        void reset() {
            _count = 0;
            _start = millis();
            _last  = _start;
        }

        /**
         * Set debounce interval, in milliseconds
         */
        void debounce(uint32_t debounce) {
            _debounce = debounce;
        }

        /**
         * Increment the counter, if debounced 
         */
        void increment(uint32_t increment = 1) {
            uint32_t now = millis();

            if (now - _last >= _debounce) {
                _count += increment;
                _last = now;
            }
        }

        /**
         * Get current count
         */
        uint32_t count() {
            return _count;
        }

        /**
         * Get count per second
         */
        float countPerSecond() {
            return 1000.0 * _count / (millis() - _start);
        }

    protected:
        uint32_t _start;
        uint32_t _count;
        uint32_t _debounce;
        uint32_t _last;
    };

}