#pragma once

#include <EEPROM.h>

#define ELOQUENT_EEVALUE_CONTROL_BYTE 0x99


namespace Eloquent {

  /**
   * Manipulate values stored in EEPROM as native types
   */
    template<class T>
    class eeValue {
    public:
  
        /**
         * 
         */
        eeValue(uint16_t address) {
            _value = 0;
            _address = address;
        }

        /**
         * 
         */
        eeValue& operator=(const T value) {
            return set(value);
        }
  
        /**
         * 
         */
        T operator+(const T value) {
            set(_value + value);

            return value();
        }
  
        /**
         * 
         */
        T operator-(const T value) {
            set(_value - value);

            return value();
        }
  
        /**
         * 
         */
        T operator++() {
            set(_value + 1);

            return value();
        }

        /**
         * 
         */
        T operator--() {
            set(_value - 1);

            return value();
        }
  
        /**
         * 
         */
        eeValue& operator+=(T value) {
            return set(_value + value);
        }

        /**
         * 
         */
        eeValue& operator-=(T value) {
            return set(_value - value);
        }
  
        /**
         * Initialize value from EEPROM, if any
         */
        void begin(const T defaultValue = 0) {
            EEPROM.begin();

            // check the control byte
            // if present, load the stored value
            if (EEPROM.read(_address) == ELOQUENT_EEVALUE_CONTROL_BYTE) {
                readAnything(_value);
            }
            // if not present, initialize to default
            else {
                EEPROM.write(_address, ELOQUENT_EEVALUE_CONTROL_BYTE);
                set(defaultValue);
            }
        }

        /**
         * Set value
         */
        eeValue& set(T value) {
            if (value != _value) {
                _value = value;
                writeAnything(_value);
            }

            return *this;
        }
  
        /**
         * Get value
         */
        T value() {
            return _value;
        }
  
    protected:
        uint16_t _address;
        T _value;

        /**
         * @from https://playground.arduino.cc/Code/EEPROMWriteAnything
         */
        void readAnything(T& value) {
            byte* p = (byte*)(void*)&value;

            for (uint16_t i = 0; i < sizeof(value); i++)
                *p++ = EEPROM.read(_address + 1 + i);
        }

        /**
         * @from https://playground.arduino.cc/Code/EEPROMWriteAnything
         */
        void writeAnything(const T& value) {
            const byte* p = (const uint8_t*)(const void*)&value;

            for (uint16_t i = 0; i < sizeof(value); i++)
                EEPROM.write(_address + 1 + i, *p++);
        }
    };


    /**
     * Some alias
     */
     typedef eeValue<uint8_t>  eeUint8;
     typedef eeValue<uint16_t> eeUint16;
     typedef eeValue<uint32_t> eeUint32;
     typedef eeValue<int8_t>   eeInt8;
     typedef eeValue<int16_t>  eeInt16;
     typedef eeValue<int32_t>  eeInt32;
}