#pragma once

#include "EloquentLogging.h"

/**
 * A pin management library.
 * Stop using analogWrite and the likes.
 */


namespace Eloquent {

    /**
     * Enum for pin modes
     */
    enum class PinMode {
        DIGITAL,
        ANALOG
    };


    /**
     * Aliased type for INPUT, OUTPUT, INPUT_PULLUP
     **/
    typedef uint8_t PinType;


    /**
     *
     */
    class Pin {
    public:

        Pin(uint8_t pin, PinType type, PinMode mode) {
            _pin = pin;
            _mode = mode;
            _type = type;
            _curr = _prev = 0;
        }

        /**
         * Alias for `write`
         * @param value
         * @return
         */
        Pin& operator=(uint8_t value) {
            write(value);

            return *this;
        }

        /**
         * Alias for `increment`
         * @param value
         * @return
         */
        Pin& operator+=(uint8_t value) {
            increment(value);

            return *this;
        }

        /**
         * Alias for `decrement`
         * @param value
         * @return
         */
        Pin& operator-=(uint8_t value) {
            decrement(value);

            return *this;
        }

        /**
         * Test pin value
         * @param value
         * @return
         */
        bool operator==(uint8_t value) {
            return _curr == value;
        }

        /**
         * Test pin value
         * @param value
         * @return
         */
        bool operator!=(uint8_t value) {
            return _curr != value;
        }

        /**
         * Test pin value
         * @param value
         * @return
         */
        bool operator<(uint8_t value) {
            return _curr < value;
        }

        /**
         * Test pin value
         * @param value
         * @return
         */
        bool operator<=(uint8_t value) {
            return _curr <= value;
        }

        /**
         * Test pin value
         * @param value
         * @return
         */
        bool operator>(uint8_t value) {
            return _curr > value;
        }

        /**
         * Test pin value
         * @param value
         * @return
         */
        bool operator>=(uint8_t value) {
            return _curr >= value;
        }

        /**
         * Init pin
         */
        void begin() {
            pinMode(_pin, _type);
        }

        /**
         * Check if pin is set as digital
         */
        bool isDigital() {
            return _mode == PinMode::DIGITAL;
        }

        /**
         * Check if pin is set as analog
         */
        bool isAnalog() {
            return _mode == PinMode::ANALOG;
        }

        /**
         * Check if pin is set as input
         */
        bool isInput() {
            return _type == INPUT;
        }

        /**
         * Check if pin is set as output
         */
        bool isOutput() {
            return _type == OUTPUT;
        }

        /**
         * Check if pin is set as pullup
         */
        bool isPullup() {
            return _type == INPUT_PULLUP;
        }

        /**
         * Set pin as digital
         */
        void asDigital() {
            _mode = PinMode::DIGITAL;
        }

        /**
         * Set pin as analog
         */
        void asAnalog() {
            _mode = PinMode::ANALOG;
        }

        /**
         * Set pin as input
         */
        void asInput() {
            setType(INPUT);
        }

        /**
         * Set pin as output
         */
        void asOutput() {
            setType(OUTPUT);
        }

        /**
         * Set pin as input
         */
        void asPullup() {
            setType(INPUT_PULLUP);
        }

        /**
         * Get pin value
         */
         uint16_t read() {
             begin();
             log_warning_if(isOutput(), "Pin is set as output, you should not read from it")

             _prev = _curr;
             _curr = isDigital() ? digitalRead(_pin) : analogRead(_pin);

             return _curr;
         }

         /**
          * Set pin value
          * @param value
          */
         void write(uint8_t value) {
             begin();
             log_warning_if(isInput(), "Pin is set as input, you should not write to it")

            _prev = _curr;
            _curr = value;

            isDigital() ? digitalWrite(_pin, value) : analogWrite(_pin, value);
         }

         /**
          * Get pin current value
          * !!! Does not actually read the value !!!
          * @return
          */
         uint8_t value() {
             return _curr;
         }

        /**
        * Get pin previous value
        */
        uint8_t prev() {
            return _prev;
        }

        /**
         * Get difference from current and previous value
         */
        int16_t delta() {
            return _curr - _prev;
        }

         /**
          * Test if pin is on
          * @return
          */
         bool isOn() {
             return _curr > 0;
         }

        /**
         * Alias for `isOn`
         * @return
         */
        bool isHigh() {
            return isOn();
        }

        /**
         * Test if pin is off
         * @return
         */
        bool isOff() {
            return !isOn();
        }

        /**Alias for `isOff`
          * @return
          */
        bool isLow() {
            return isOff();
        }

        /**
         * Test if pin changed value
         * @return
         */
        bool changed() {
            return _curr != _prev;
        }

        /**
         * Test if current value is greater than prev
         */
        bool rising() {
            return delta() > 0;
        }

        /**
         * Test if current value is lower than prev
         */
        bool falling() {
            return delta() < 0;
        }

        /**
         * For digital pins, set pin to HIGH.
         * For analog pins, set pin to 255.
         */
        void turnOn() {
            write(isDigital() ? HIGH : 255);
        }

        /**
         * Set pin value to 0
         */
        void turnOff() {
            write(0);
        }

        /**
         * Turn on/off the pin if it is off/on.
         */
        void toggle() {
            isOn() ? turnOff() : turnOn();
        }

        /**
         * Blink the pin synchronously.
         */
        void blink(uint8_t blinkTimes, uint16_t singleBlinkDuration, uint8_t value = 255) {
            for (; blinkTimes > 0; blinkTimes--) {
                write(value);
                delay(max(1, singleBlinkDuration / 2));
                turnOff();
                delay(max(1, singleBlinkDuration / 2));
            }
        }

        /**
         *
         * @param incr
         * @return
         */
        void increment(uint8_t incr = 1) {
            if (isDigital())
                return write(HIGH);

            write(min(255, (int) _curr + incr));
        }

        /**
         *
         * @param decr
         * @return
         */
        void decrement(uint8_t decr) {
            if (isDigital())
                return turnOff();

            write(max(0, (int) _curr - decr));
        }


    protected:
         uint8_t _pin;
         uint16_t _prev;
         uint16_t _curr;
         PinMode _mode;
         PinType _type;

         void setType(PinType type) {
             _type = type;
             pinMode(_pin, _type);
         }
    };
}