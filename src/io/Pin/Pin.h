#pragma once

namespace Eloquent {
    namespace Pin {
        /**
         * Pin handling made easy
         */
        class Pin {
        public:
            Pin(uint8_t pin) :
                    _pin(pin) {

            }

        protected:
            uint8_t _pin;
            uint8_t _value;
        };
    }
}