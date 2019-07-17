#pragma once
#include "eTransformsNumericValue.h"


namespace Eloquent {

    /**
     * Interface for input devices that can read a numeric value
     */
    class ReadsNumericValue {
    public:

        /**
         *
         * @return
         */
        float cachedValue() {
            return _read_value;
        }

        /**
         * Public interface
         * May do some processing on the value
         * @return
         */
        float readValue() {
            float value = actualReadValue();

            // transform
            TransformsNumericValue *transformer = _first_transformer;

            while (transformer != NULL) {
                value = transformer->transform(value);
                transformer = transformer->next();
            }

            return (_read_value = value);
        }

        /**
         *
         * @param transformer
         * @return
         */
        ReadsNumericValue& transform(TransformsNumericValue* transformer) {
            if (_first_transformer == NULL) {
                _first_transformer = transformer;
                _current_transformer = transformer;
            }
            else {
                _current_transformer->chain(transformer);
            }

            return *this;
        }

    protected:
        float _read_value;
        TransformsNumericValue *_first_transformer;
        TransformsNumericValue *_current_transformer;

        /**
         * Actual implementation
         * @return
         */
        virtual float actualReadValue() = 0;
    };
}