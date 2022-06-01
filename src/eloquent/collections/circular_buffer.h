//
// Created by Simone on 24/05/2022.
//

#pragma once


namespace Eloquent {
    namespace Collections {
        /**
         * Circular (endless) buffer
         * @tparam size
         */
        template<typename T, uint16_t size>
        class CircularBuffer {
        public:
            T values[size];


            /**
             * Constructor
             */
            CircularBuffer() :
                _i(0),
                _count(0),
                _batchSize(1),
                _batchCount(0) {

            }

            /**
             * Clear the buffer
             * @param deep
             */
            void clear(bool deep = false) {
                _i = 0;
                _count = 0;
                _batchCount = 0;

                if (deep)
                    for (uint16_t i = 0; i < size; i++)
                        values[i] = 0;
            }

            /**
             *
             * @param batchSize
             */
            void batch(uint16_t batchSize) {
                _batchSize = batchSize > 0 ? batchSize : 1;
            }

            /**
             *
             * @param value
             * @return
             */
             template<typename U>
            bool push(U value) {
                return push(value, 1);
            }

            /**
             *
             * @param values
             * @param count
             * @return
             */
             template<typename U>
            bool push(U values, uint16_t length) {
                // there's space for all items
                if (_count + length <= size) {
                    for (uint16_t i = 0; i < length; i++)
                        this->values[i + _count] = values[i];
                }
                // we need to shift items to the left to make room
                else {
                    uint16_t shift = _count >= size ? length : size - _count;
                    uint16_t head = size - length;

                    for (uint16_t i = 0; i < size - shift; i++)
                        this->values[i] = this->values[i + shift];

                    for (uint16_t i = 0; i < length; i++)
                        this->values[head + i] = values[i];
                }

                _batchCount += length;
                _count += length;

                return testBatch();
            }

            /**
             * Get mean value of elements
             * @return
             */
            float mean() {
                return eloquent::math::arrayMean(values, size);
            }

            /**
             *
             * @tparam Printer
             * @param printer
             * @param separator
             * @param end
             */
            template<typename Printer>
            void printTo(Printer printer, char separator = ',', char end = '\n') {
                printer.print(values[0]);

                for (uint16_t i = 1; i < size; i++) {
                    printer.print(separator);
                    printer.print(values[i]);
                }

                printer.print(end);
            }


        protected:
            uint16_t _i;
            uint16_t _batchSize;
            uint16_t _batchCount;
            uint32_t _count;

            /**
             * Test if the given number of elements was pushed since last check
             * @return
             */
            bool testBatch() {
                if (_batchCount >= _batchSize) {
                    _batchCount -= _batchSize;

                    return _count >= size;
                }

                return false;
            }
        };

        /**
         * Specialized template class for uint8_t values
         * @tparam size
         */
        template<uint16_t size>
        class Uint8CircularBuffer : public CircularBuffer<uint8_t, size> {

        };

        /**
         * Specialized template class for int values
         * @tparam size
         */
        template<uint16_t size>
        class IntCircularBuffer : public CircularBuffer<int, size> {

        };

        /**
         * Specialized template class for float values
         * @tparam size
         */
        template<uint16_t size>
        class FloatCircularBuffer : public CircularBuffer<float, size> {

        };
    }
}