#pragma once

#include "eSerialLog.h"

#define ARRAY_ITEM_NOT_FOUND 255

namespace Eloquent {

    /**
     * A sane array manipulation library
     * @tparam T 
     */
    template<class T>    
    class Array {
        public: 
            Array(uint16_t count, T* items) {
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
            U reduce(U (*reducer)(U carry, T item, uint16_t index), U initial) {
                for (uint16_t i = _startIndex; i < _startIndex + _count; i++) {
                    initial = reducer(initial, _items[i], i);
                }

                return initial;
            }

            /**
             * Select a sub-part of the array
             * @param startIndex 
             * @param count 
             * @return 
             */
             Array slice(int8_t startIndex, uint16_t count = 0) {
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

                return *this;
            }

            /**
             * Set item value
             * @param index 
             * @param item 
             */
            void put(uint16_t index, T item) {
                if (_startIndex + index > _count) {
                    log_error("Array index out of bounds")
                    return;
                }

                _items[_startIndex + index] = item;
            }

            /**
             *
             * @param needle
             * @return
             */
            uint16_t indexOf(T needle) {
                for (uint16_t i = _startIndex; i < _startIndex + _count; i++) {
                    if (_items[i] == needle)
                        return i;
                }

                return ARRAY_ITEM_NOT_FOUND;
            }

            /**
             * 
             * @return 
             */
            uint16_t count() {
                return _count;
            }

            /**
             * 
             * @return 
             */
            T getMin() {
                return reduce<T>(
                        [](T carry, T item, uint16_t i) { return item < carry ? item : carry; },
                        _items[_startIndex]);
            }

            /**
             * 
             * @return 
             */
            T getMax() {
                return reduce<T>(
                        [](T carry, T item, uint16_t i) { return item > carry ? item : carry; },
                        _items[_startIndex]);
            }

            /**
             * 
             * @return 
             */
            T getSum() {
                return reduce<T>(
                        [](T carry, T item, uint16_t i) { return carry + item; },
                        0);
            }

            /**
             *
             * @return
             */
            float getAvg() {
                return (float) getSum() / count();
            }

            /**
             *
             * @return
             */
            uint16_t argmin() {
                return indexOf(getMin());
            }

            /**
             *
             * @return
             */
            uint16_t argmax() {
                return indexOf(getMax());
            }

        protected:
            uint16_t _startIndex;
            uint16_t _count;
            T *_items;
    };
}