#pragma once


namespace Eloquent {

    class Wind {
    public:
        Wind(uint16_t *thresholds, uint8_t dim, uint8_t minCount = 10) {
            _thresholds = thresholds;
            _dim = dim;
            _minCount = minCount;
            _prev = 0;
        }

        uint8_t current() {
            return _prev;
        }

        /**
         *
         * @param reading
         * @return
         */
        uint8_t update(uint16_t reading) {
            uint8_t curr;

            for (uint8_t i = 0; i < _dim * 3; i += 3) {
                if (reading >= _thresholds[i] && reading <= _thresholds[i+1])
                    curr = _thresholds[i+2];
            }

            // update counter
            if (curr == _prev)
                _count++;
            else
                _count = 0;

            _prev = curr;

            // if counter >= threshold, return current
            if (_count >= _minCount)
                return curr;

            return 0;
        }

    protected:
        uint8_t _dim;
        uint8_t _prev;
        uint8_t _count;
        uint8_t _minCount;
        uint16_t *_thresholds;
    };
}