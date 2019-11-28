#pragma once

#ifndef NaN
#define NaN sqrt(-1)
#endif

namespace Eloquent {
    namespace InputStream {

        /**
         *
         */
        class Transformer {
        public:
            /**
             * Chain transformers
             * @param next
             * @return
             */
            virtual Transformer *then(Transformer *next) final {
                return (_next = next);
            }

            /**
             * Receive next value
             * @param value
             * @return
             */
            float consume(float value) {
                float transformed = transform(value);

                if (isnan(transformed))
                    return transformed;

                if (!_next)
                    return transformed;

                return _next->transform(transformed);
            }

        protected:
            /**
             *
             * @param value
             * @return
             */
            virtual float transform(float value) = 0;

        private:
            Transformer *_next = NULL;
        };
    }
}