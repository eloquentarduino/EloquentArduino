#pragma once


namespace Eloquent {
    namespace DataStructures {

        /**
         * Array manipulation made easy
         * @tparam T
         */
        template<typename T, uint16_t size>
        class Array {
        public:
            /**
             * Constructor
             * @param defaultValue
             */
            Array(T defaultValue) :
                index(0),
                zero(defaultValue) {

                for (int i = 0; i < size; i++)
                    items[i] = zero;
            }

            /**
             * Access array with subscript syntax
             * @param index 
             * @return 
             */
            T& operator[](uint16_t index) {
                return at(index);
            }

            /**
             *
             */
            T& at(uint16_t index) {
                if (index < size)
                    return items[index];

                return zero;
            }

            /**
             * Push element at the end of the array
             * @param e
             * @return whether the element was pushed
             */
            bool push(T e) {
                if (index < size) {
                    items[index++] = e;

                    return true;
                }

                return false;
            }

            /**
             * Get index of given value.
             * Returns NaN if not found.
             * @param needle
             * @return
             */
            uint16_t indexOf(T needle) {
                for (uint16_t i = 0; i < size; i++) {
                    if (at(i) == needle)
                        return i;
                }

                return sqrt(-1);
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
                for (uint16_t i = 0; i < size; i++) {
                    initial = reducer(initial, at(i), i);
                }

                return initial;
            }

            /**
             *
             * @return
             */
            uint16_t length() {
                return index;
            }

            /**
             *
             * @return
             */
            T getMin() {
                return reduce<T>(
                        [](T carry, T item, uint16_t i) { return item < carry ? item : carry; },
                        at(0));
            }

            /**
             *
             * @return
             */
            T getMax() {
                return reduce<T>(
                        [](T carry, T item, uint16_t i) { return item > carry ? item : carry; },
                        at(0));
            }

            /**
             *
             * @return
             */
            T getSum(T zero = 0) {
                return reduce<T>(
                        [](T carry, T item, uint16_t i) { return carry + item; },
                        zero);
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
            uint16_t index;
            T& zero;
            T items[size];
        };
    }
}