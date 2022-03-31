#pragma once

#include <stdint.h>


namespace Eloquent {
    namespace DataStructures {
        /**
         * Circular queue
         * @tparam depth
         */
        template<uint16_t depth>
        class Queue {
        public:
            float X[depth];

            /**
             * Constructor
            */
            Queue() {
                clear();
            }

            /**
             * Set all elements to 0
             */
            void clear() {
                _idx  = 0;

                for (uint16_t k = 0; k < depth; k++) {
                    X[k] = 0;
                }
            }

            /**
             * Get total number of items pushed to the queue.
             * If more than UINT32_MAX - depth have been pushed, this number becomes meaningless
             * @return
             */
            inline size_t length() {
                return _idx;
            }

            /**
             * Test if queue is full
             */
            inline bool isFull() {
                return length() >= depth;
            }

            /**
             * Add sample to queue.
             */
            void append(float x) {
                uint16_t i = isFull() ? 0 : _idx;

                X[i] = x;
                _idx  += 1;

                if (length() > depth) {
                    shift();
                }
            }

        protected:
            size_t _idx;

            /**
             * Shift queue by one position to the left
             */
            void shift() {
                float first = X[0];

                for (uint16_t k = 1; k < depth; k++) {
                    X[k - 1] = X[k];
                }

                X[depth - 1] = first;
            }
        };
    }
}