#pragma once

namespace Eloquent {

    /**
     * Pack arbitrary length values together
     * @tparam bytes
     */
    template<uint8_t bytes>
    class PackedBitArray {
    public:
        PackedBitArray() {
            clear();
        }

        /**
         * Append value to the tail of the array occupying
         * a fixed amount of bits
         * @param value
         * @param numberOfBits
         * @return
         */
        bool append(uint32_t value, uint8_t numberOfBits) {
            if (_index + numberOfBits > bits) {
                return false;
            }

            for (uint8_t i = 0; i < numberOfBits; i++)
                write((value >> i) & 1);

            return true;
        }

        /**
         * Get the buffer array
         * @return
         */
        uint8_t* toArray() {
            return _array;
        }

        /**
         * Get the occupied bits
         * @return
         */
        uint8_t size() {
            return _index;
        }

        /**
         * Reset all bits to 0
         */
        void clear() {
            for (uint8_t i = 0; i < bytes; i++)
                _array[i] = 0;
        }

    protected:
        const uint8_t bits = bytes * 8;
        uint8_t _index;
        uint8_t _array[bytes];

        /**
         * Append bit
         * @param bit
         */
        void write(uint8_t bit) {
            const uint8_t i = _index / 8;
            const uint8_t k = _index % 8;

            _array[i] = bit ? (_array[i] | (1UL << k)) : (_array[i] & ~(1UL << k));
            _index++;
        }
    };
}