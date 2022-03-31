#pragma once


namespace Eloquent {
    /**
     * Queue data structure (FIFO)
     * @tparam T
     * @tparam size
     */
    template <class T, uint16_t size>
    class Queue {
    public:
        Queue() :
            _count(0) {
        }

        /**
         * Get items count
         * @return
         */
        uint16_t count() {
            return _count;
        }

        /**
         * Test if queue is empty
         * @return
         */
        bool isEmpty() {
            return count() == 0;
        }

        /**
         * Test if queue is full
         * @return
         */
        bool isFull() {
            return count() >= size;
        }

        /**
         * Get current index
         * @return
         */
        uint16_t index() {
            return count() % size;
        }

        /**
         * (Lazy) Delete all items.
         * It really resets the index to the start so it will ovewrite
         * existing items as the queue fills up
         */
        void wipe() {
            _count = 0;
        }

        /**
         * Append new item
         * @param e
         */
        void push(T e) {
            _queue[index()] = e;
            _count++;
        }

        /**
         * Get item at given index
         * @param i
         * @return
         */
        T get(int16_t i) {
            return _queue[toActualIndex(i)];
        }

        /**
         * Apply a reducer
         * @param reducer
         * @return
         */
        template<class Treduced>
        T reduce(Treduced (*reducer)(Treduced& reduced, T e, uint16_t i, uint16_t totalSize), Treduced& initial) {
            for (uint16_t i = 0; i < min(size, count()); i++) {
                initial = reducer(initial, get(i), i, min(size, count()));
            }

            return initial;
        }

        /**
         * Copy items to a regular array
         * @param dest
         */
        void toArray(T* dest) {
            for (uint16_t i = 0; i < size; i++)
                dest[i] = _queue[(index() + i) % size];
        }

    protected:
        uint32_t _count;
        T _queue[size];

        /**
         * Translate "logical" index to "physical" index
         * @param i
         * @return
         */
        uint16_t toActualIndex(int16_t i) {
            return ((int32_t) i + index() + count()) % count();
        }
    };
}