#pragma once

#include "InputStream.h"

namespace Eloquent {
    namespace InputStream {
        /**
         * Generate values from an array
         */
        class ArrayInputStream : public InputStream {
        public:
            ArrayInputStream(float *array, uint16_t count) {
                _array = array;
                _index = 0;
                _count = count;
            }

        protected:
            uint16_t _index;
            uint16_t _count;
            float *_array;

            /**
             * Values are available until end of array
             * @return
             */
            bool available() override {
                return _index < _count;
            }

            /**
             * Read next array element
             * @return
             */
            float _read() override {
                return _array[_index++];
            }
        };
    }
}