#pragma once

#include "eArray.h"


namespace Eloquent {
    
    /**
     * Store a fixed number of elements in an array
     * Everytime you push a new item, the eldest is discarded
     */
    template<class T>
    class RollingWindow {
    public:
        RollingWindow(uint16_t count, T* items) :
            _array(count, items),
            _head(0) {
            
        }

        /**
         * 
         * @return 
         */
        inline uint16_t count() {
            return _array.count();
        }
        
        /**
         * Push element 
         * @param item 
         */
        void push(T item) {
            _head = (_head + 1) % count();
            _array.put(_head, item);
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
            for (uint16_t i = _head; i < _head + count(); i++) {
                const j = i % count();

                initial = reducer(initial, _items[j], j);
            }

            return initial;
        }

        /**
         *
         * @return
         */
        T getMin() {
            return _array.getMin();
        }

        /**
         *
         * @return
         */
        T getMax() {
            return _array.getMax();
        }

        /**
         *
         * @return
         */
        T getSum() {
            return _array.getSum();
        }

        /**
         *
         * @return
         */
        float getAvg() {
            return _array.getAvg();
        }

        /**
         *
         * @return
         */
        uint16_t argmin() {
            return (_array.argmin() + count()) % count();
        }

        /**
         *
         * @return
         */
        uint16_t argmax() {
            return (_array.argmax() + count()) % count();
        }

    private:
        uint16_t _head;
        Array<T> _array;
    };
}