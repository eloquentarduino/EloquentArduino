#pragma once

#if 1

#include <EEPROM.h>

namespace Eloquent {
    namespace DataStructures {

        /**
         * Backup value to EEPROM
         */
        class PersistentInt16 {
        public:
            PersistentInt16(uint16_t address) :
                _address(address),
                _value(0) {

            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt16& operator=(int16_t value) {
                write(value);

                return *this;
            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt16& operator+=(int16_t value) {
                write(_value + value);

                return *this;
            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt16& operator-=(int16_t value) {
                write(_value - value);

                return *this;
            }

            /**
             * Init EEPROM
             */
            void begin() {
                EEPROM.begin();

                _value = read();
            }

            /**
             *
             * @return
             */
            int16_t zero() {
                return write(0);
            }

            /**
             *
             * @return
             */
            int16_t increment() {
                return write(toInt() + 1);
            }

            /**
             *
             * @return
             */
            int16_t toInt() {
                return _value;
            }

        protected:
            uint16_t _address;
            int16_t _value;

            /**
             *
             * @tparam T
             * @param ee
             * @param value
             * @return
             */
            int16_t read() {
                uint8_t high = EEPROM.read(_address);
                uint8_t low = EEPROM.read(_address + 1);

                return (high << 8) | low;
            }

            /**
             *
             * @tparam T
             * @param value
             */
            int16_t write(const int16_t value) {
                _value = value;
                EEPROM.write(_address, value >> 8);
                EEPROM.update(_address + 1, value & 0xFF);

                return toInt();
            }
        };
    }
}

#endif