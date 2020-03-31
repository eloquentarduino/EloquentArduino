#pragma once

#if defined(EEPROM_h)

#include <EEPROM.h>

namespace Eloquent {
    namespace DataStructures {

        /**
         * Backup value to EEPROM
         */
        class PersistentInt32 {
        public:
            PersistentInt32(uint16_t address) :
                _address(address),
                _value(0) {

            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt32& operator=(const int32_t value) {
                write(value);

                return *this;
            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt32& operator+=(const int32_t value) {
                write(_value + value);

                return *this;
            }

            /**
             *
             * @param value
             * @return
             */
            PersistentInt32& operator-=(const int32_t value) {
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
            int32_t toInt() {
                return _value;
            }

        protected:
            uint16_t _address;
            int32_t _value;

            /**
             *
             * @tparam T
             * @param ee
             * @param value
             * @return
             */
            int32_t read() {
                uint8_t a = EEPROM.read(_address);
                uint8_t b = EEPROM.read(_address + 1);
                uint8_t c = EEPROM.read(_address + 2);
                uint8_t d = EEPROM.read(_address + 3);

                return (a << 24) | (b << 16) | (c << 8) | d;
            }

            /**
             *
             * @tparam T
             * @param value
             */
            void write(const int32_t value) {
                _value = value;
                EEPROM.write(_address + 0, value >> 24);
                EEPROM.write(_address + 1, value >> 16);
                EEPROM.write(_address + 2, value >> 8);
                EEPROM.update(_address + 4, value & 0xFF);
            }
        };
    }
}

#endif