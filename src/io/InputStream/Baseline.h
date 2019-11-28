#pragma once

#include "Transformer.h"


namespace Eloquent {
    namespace InputStream {
        /**
         * Substract the average of the calibrating samples
         * from the current value
         */
        class Baseline : public Transformer {
        public:
            Baseline(uint16_t samples) :
                _samples(samples),
                _average(0),
                _i(0) {

            }

        protected:
            uint16_t _i;
            uint16_t _samples;
            float _average;

            float transform(float value) override {
                if (_i == _samples)
                    return value - _average;

                _i++;

                if (_i > 5)
                    _average += value / (_samples - 5);

                return NaN;
            }
        };
    }
}