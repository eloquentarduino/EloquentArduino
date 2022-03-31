#pragma once

#include "../../../src/dev/logging.h"


namespace Eloquent {

    /**
     * Count, extended
     */
    class Counter {
    public:

        /**
         * @see increment
         * @return
         */
        Counter* operator++() {
            return increment();
        }

        /**
         * Start timer
         */
        void begin() {
            _start = millis();  
        }

        /**
         * Set debounce interval
         * @param debounce
         */
        void debounce(uint32_t debounce) {
            _debounce = debounce;
        }

        /**
         * Increment if debounced
         * @return
         */
        Counter* increment() {
            if (millis() > _last + _debounce) {
                _count++;
                _last = millis();
            }
            else {
                library_log_warning("increment ignored because of debouncing");
            }

            return this;
        }

        /**
         * Get count
         * @return
         */
        uint32_t count() {
            return _count;
        }

        /**
         * Get count per second
         * @return
         */
        float countPerSecond() {
            return 1000.0 * _count / (millis() - _start);
        }

    protected:
        uint32_t _start;
        uint32_t _last;
        uint32_t _debounce;
        uint32_t _count;
    };

}