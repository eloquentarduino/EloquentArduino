#pragma once

#include "Transformer.h"

namespace Eloquent {
    namespace InputStream {
        /**
         * An abstract type for an input stream
         * That is, a source that can generate values
         * @tparam T
         */
        class InputStream {
        public:
            /**
             *
             * @return
             */
            bool isNan() {
                return isnan(value());
            }
            /**
             * Read next value, if any
             * @return
             */
            float read() {
                if (!available()) {
                    return (_value = _raw = sqrt(-1));
                }

                _value = _raw = _read();

                if (!_transformer)
                    return _value;

                return (_value = _transformer->consume(_value));
            }

            /**
             * Get value without transformers
             * @return
             */
            float raw() {
                return _raw;
            }

            /**
             * Get value with transformers
             * @return
             */
            float value() {
                return _value;
            }

            /**
             * Convert value to int
             * @return
             */
            int valueInt() {
                return _value;
            }

            /**
             * Chain a transformer
             * @param next
             * @return
             */
            InputStream& then(Transformer *next) {
                if (!_transformer)
                    _transformer = next;
                else
                    _transformer->then(next);

                return *this;
            }

        protected:
            float _value = 0;
            float _raw = 0;
            Transformer *_transformer = NULL;

            /**
             * Test if input stream has a value to be consumed
             * @return
             */
            virtual bool available() {
                return true;
            }

            /**
             * Actual reading
             * @return
             */
            virtual float _read() = 0;
        };
    }
}