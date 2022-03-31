#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {

        /**
         * Average multiple values
         */
        class Average : public Transformer {
        public:
            Average(uint16_t count) :
                    _count(count),
                    _counter(0),
                    _average(0) {

            }

        protected:
            const uint16_t _count;
            uint16_t _counter;
            float _average;

            /**
             *
             * @param value
             * @return
             */
            virtual float transform(float value) override {
                _counter = (_counter + 1) % _count;
                _average += value / _count;

                if (_counter != 0)
                    return NaN;

                const float average = _average;

                _average = 0;

                return average;
            }
        };
    }
}