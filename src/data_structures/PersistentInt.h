#pragma once

#ifndef ESP8266

#include <EEPROM.h>

namespace Eloquent {
    namespace DataStructures {

        /**
         * Backup value to EEPROM
         */
        class PersistentInt {
        public:
            PersistentInt(uint16_t address) :
                _address(address),
                _value(0) {

            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt& operator=(const int value) {
                write(value);

                return *this;
            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt& operator+=(const int value) {
                write(_value + value);

                return *this;
            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt& operator-=(const int value) {
                write(value > _value ? 0 : _value - value);

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
            int toInt() {
                return _value;
            }

        protected:
            uint16_t _address;
            int _value;

            /**
             *
             * @tparam T
             * @param ee
             * @param value
             * @return
             */
            int read() {
                uint8_t high = EEPROM.read(_address);
                uint8_t low = EEPROM.read(_address + 1);

                return (high << 8) | low;
            }

            /**
             *
             * @tparam T
             * @param value
             */
            void write(const int value) {
                _value = value;
                EEPROM.write(_address, value >> 8);
                EEPROM.update(_address + 1, value & 0xFF);
            }
        };
    }
}

#endif