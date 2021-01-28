#pragma once

#include <stdint.h>


namespace Eloquent {
    namespace DataStructures {
        /**
         * Rolling window implementation.
         * You can add samples as a circular queue
         * @tparam num_features
         * @tparam depth
         */
        template<uint16_t num_features, uint8_t depth>
        class NdQueue {
        public:
            float X[num_features * depth];

            /**
             * Constructor
            */
            NdQueue() {
                clear();
            }

            /**
             * Set all elements to 0
             */
            void clear() {
                _head = 0;
                _idx  = 0;

                for (uint16_t k = 0; k < depth; k++) {
                    for (uint16_t i = 0; i < num_features; i++) {
                        _samples[k][i] = 0;
                        X[k * depth + i] = 0;
                    }
                }
            }

            /**
             * Get total number of items pushed to the queue.
             * If more than UINT32_MAX - depth have been pushed, this number becomes meaningless
             * @return
             */
            size_t length() {
                return _idx;
            }

            /**
             * Get current head index.
             * It wraps when the queue gets full.
             * @return
             */
            uint8_t head() {
                return _head;
            }

            /**
             * Test if window is full
             */
            bool isFull() {
                return _idx >= depth;
            }

            /**
             * Add sample to queue.
             * @param updateX wether to update X array
             */
            void append(float *x, bool updateX = true) {
                for (uint16_t i = 0; i < num_features; i++) {
                    _samples[_head][i] = x[i];
                }

                // prevent _idx overflow
                if (_idx == UINT32_MAX)
                    _idx -= depth;

                _idx = _idx + 1;
                _head = _idx % depth;

                if (updateX)
                    update();
            }

            /**
             * Linearize samples to feature vector
             */
            void update() {
                for (uint8_t k = 0; k < depth; k++) {
                    uint8_t sampleIdx = (_head + k) % depth;
                    uint16_t offset = k * num_features;

                    //memcpy(X + offset, _samples[sampleIdx], sizeof(float) * num_features);

                    for (uint16_t i = 0; i < num_features; i++) {
                        X[offset + i] = _samples[sampleIdx][i];
                    }
                }
            }

        protected:
            uint8_t _head = 0;
            size_t _idx = 0;
            float _samples[depth][num_features];
        };
    }
}