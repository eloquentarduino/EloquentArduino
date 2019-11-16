#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {

        class Derivative : public Transformer {
        protected:
            float _old = 0;

            /**
             *
             * @param value
             * @return
             */
            virtual float transform(float value) override {
                float derivative = value - _old;

                _old = value;

                return derivative;
            }
        };
    }
}