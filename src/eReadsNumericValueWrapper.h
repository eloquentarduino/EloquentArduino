#pragma once

#include "eReadsNumericValue.h"


namespace Eloquent {

    /**
     *
     */
     template<class T>
    class ReadsNumericValueWrapper : public ReadsNumericValue {
    public:

        ReadsNumericValueWrapper(T& native, float (*wrapper)(T&)) :
            _native(native) {
                _read_wrapper = wrapper;
        }

        /**
         *
         * @param wrapper
         * @return
         */
        bool begin(bool (*wrapper)(T&)) {
            return wrapper(_native);
        }

    protected:
        T _native;
        float (*_read_wrapper)(T&);

        /**
         *
         * @return
         */
        float actualReadValue() {
            return _read_wrapper(_native);
        }
    };
}