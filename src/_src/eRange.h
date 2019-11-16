#pragma once

#ifndef log_warn_if
#define log_warn_if(x, y)
#endif

#define _range_walk for (int32_t n = _from; _from < _to && n < _to || _from > _to && n > _to; n += _step)


namespace Eloquent {

    /**
     * Generates a range, from A to B
     */
    class Range {
    public:
        Range(int32_t from, int32_t to, int16_t step = 1) :
            _from(from),
            _to(to),
            _step(step) {

            log_warn_if(_from > _to && _step >= 0, "from is greater than to with a positive step: nothing will be generated")
            log_warn_if(_from < _to && _step <= 0, "from is less than to with a negative step: nothing will be generated")
        }

        /**
         * @param f
         */
        void each(void (*f)(int32_t n)) {
            _range_walk {
                f(n);
            };
        }

        /**
         *
         * @tparam T
         */
        template<class T>
        T reduce(T (*f)(T reduced, int32_t n), T initial = 0) {
            _range_walk {
                initial = f(initial, n);
            };

            return initial;
        }

        /**
         *
         * @return
         */
        int32_t sum() {
            return reduce([](int32_t sum, int32_t n) { return sum + n; }, 0);
        }

    protected:
        int32_t _from;
        int32_t _to;
        int16_t _step;
    };
}

#undef _range_walk