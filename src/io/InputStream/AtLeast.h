#pragma once

#include "Transformer.h"


namespace Eloquent {
    namespace InputStream {

        /**
         * Truncate values less than threshold
         */
        class AtLeast : public Transformer {
        public:
            AtLeast(float atLeast) :
                _atLeast(abs(atLeast)) {

            }

        protected:
            float _atLeast;

            /**
             *
             * @param value
             * @return
             */
            float transform(float value) override {
                return abs(value) > _atLeast ? value : 0;
            }
        };
    }
}