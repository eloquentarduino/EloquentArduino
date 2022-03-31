#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {
        /**
         * Constrain value to a given range
         */
        class Constrain : public Transformer {
        public:
            Constrain(float low, float high) :
                    _low(low),
                    _high(high) {

            }

        protected:
            float _low;
            float _high;

            /**
             *
             * @param value
             * @return
             */
            virtual float transform(float value) override {
                return constrain(value, _low, _high);
            }
        };
    }
}