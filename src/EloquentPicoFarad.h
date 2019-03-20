#pragma once


/**
 * Read a capacitance in the range 1pF ~ 1nF.
 * @from http://www.electronoobs.com/eng_arduino_tut10_1.php
 */

#define PICOFARAD_CONVERSION 24.48
#ifndef PICOFARAD_MAX_ADC
#define PICOFARAD_MAX_ADC 1023
#endif


namespace Eloquent {

    class PicoFarad {
        public:

            PicoFarad(uint8_t pinIn, uint8_t pinOut) {
                _pinIn  = pinIn;
                _pinOut = pinOut;
                _value  = 0;
            }

            /**
             * Init sensor
             */
            void begin() {
                pinMode(_pinIn, OUTPUT);
                pinMode(_pinOut, OUTPUT);
                // discard first
                read();
            }

            /**
             * Get value, fresh or stale
             */
            float value(bool fresh = true) {
                if (fresh)
                    read();

                return _value;
            }

            /**
             * Read current value 
             */
            float read() {
                pinMode(_pinIn, INPUT);
                digitalWrite(_pinOut, HIGH);

                _value = analogRead(_pinIn);

                digitalWrite(_pinOut, LOW);
                pinMode(_pinIn, OUTPUT);

                _value *= PICOFARAD_CONVERSION / (PICOFARAD_MAX_ADC - _value);

                while (micros() % 1000 != 0);

                return _value;
            }

        protected: 
            uint8_t _pinIn;
            uint8_t _pinOut;
            float _value;
    };
}