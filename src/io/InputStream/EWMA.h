#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {
        /**
         * Exponentially weightened moving average
         */
        class EWMA : public Transformer {
        public:
            EWMA(float smoothingFactor) {
                _zeroed = false;
                _old = 0;
                _smoothingFactor = constrain(smoothingFactor, 0, 1);
            }

        protected:
            bool _zeroed;
            float _smoothingFactor;
            float _old;

            /**
             *
             * @param value
             * @return
             */
            virtual float transform(float value) override {
                if (_zeroed) {
                    _zeroed = true;
                    _old = value;
                    return value;
                }

                return (_old = _smoothingFactor * value + (1 - _smoothingFactor) * _old);
            }
        };
    }
}