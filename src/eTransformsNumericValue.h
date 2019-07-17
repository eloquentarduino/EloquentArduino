#pragma once


namespace Eloquent {

    class TransformsNumericValue {
    public:

        /**
         *
         * @param value
         * @return
         */
        virtual float transform(float value) = 0;

        /**
         *
         * @param next
         */
        void chain(TransformsNumericValue* next) {
            _next = next;
        }

        /**
         *
         * @return
         */
        TransformsNumericValue* next() {
            return _next;
        }

    protected:
        TransformsNumericValue *_next;
    };
}