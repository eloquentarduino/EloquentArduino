#pragma once

#include "InputStream.h"

namespace Eloquent {
    namespace InputStream {

        /**
         * Generate input stream from analog pin
         */
        class AnalogPinInputStream : public InputStream {
        public:
            AnalogPinInputStream(uint8_t pin) :
                    _pin(pin) {

            }

        protected:
            uint8_t _pin;

            /**
             * Read value from analog pin
             * @return
             */
            virtual float _read() {
                return analogRead(_pin);
            }
        };
    }
}