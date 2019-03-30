#pragma once

#include "EloquentLogging.h"


namespace Eloquent {

    /**
     * A sane array manipulation library
     * @tparam T 
     */
    template<class T>    
    class Array {
        public: 
            Array(uint8_t count, T* items) {
                _startIndex = 0;
                _count = count;
                _items = items;
            }

            /**
             * Apply reduce function
             * @tparam U 
             * @param reducer 
             * @param initial 
             * @return 
             */
            template<class U>
            U reduce(U (*reducer)(U carry, T item), U initial) {
                for (uint8_t i = _startIndex; i < _startIndex + _count; i++) {
                    initial = reducer(initial, _items[i]);
                }

                return initial;
            }

            /**
             * Select a sub-part of the array
             * @param startIndex 
             * @param count 
             * @return 
             */
             void slice(int8_t startIndex, uint8_t count = 0) {
                // allow for slice from the end
                if (startIndex < 0) {
                    // you can't slice more items than current count
                    startIndex = constrain(startIndex, -_count, 0);
                    _startIndex = (_count + _startIndex) - abs(startIndex);
                    // count can't exceed available items
                    _count = count > 0 ? min(count, abs(startIndex)) : abs(startIndex);

                    return *this;
                }

                _startIndex += startIndex;

                if (_startIndex >= _count) {
                    log_warning("Slice is empty");
                    _count = 0;
                }
                else {
                    // count can't exceed available items
                    _count = min(count > 0 ? count : _count, _count - startIndex);
                }
            }

            /**
             * Set item value
             * @param index 
             * @param item 
             */
            void put(uint8_t index, T item) {
                _items[index] = item;
            }

            /**
             * 
             * @return 
             */
            uint8_t count() {
                return _count;
            }

            /**
             * 
             * @return 
             */
            T getMin() {
                return reduce<T>([](T carry, T item) { return item < carry ? item : carry; }, _items[_startIndex]);
            }

            /**
             * 
             * @return 
             */
            T getMax() {
                return reduce<T>([](T carry, T item) { return item > carry ? item : carry; }, _items[_startIndex]);
            }

            /**
             * 
             * @return 
             */
            T getSum() {
                return reduce<T>([](T carry, T item) { return carry + item; }, _items[_startIndex]) - _items[_startIndex];
            }

            /**
             *
             * @return
             */
            float getAvg() {
                return (float) getSum() / count();
            }

        protected:
            uint8_t _startIndex;
            uint8_t _count;
            T *_items;
    };
}