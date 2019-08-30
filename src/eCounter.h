#pragma once


namespace Eloquent {

    class Counter {
    public:
        Counter* operator++() {
            return increment();
        }
        
        void begin() {
            _start = millis();  
        }

        void debounce(uint32_t debounce) {
            _debounce = debounce;
        }

        Counter* increment() {
            if (millis() > _last + _debounce) {
                _count++;
                _last = millis();
            }

            return this;
        }

        uint32_t count() {
            return _count;
        }

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