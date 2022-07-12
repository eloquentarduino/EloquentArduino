//
// Created by Simone on 30/06/2022.
//

#pragma once

#define RGB565_QQVGA_BUFFER_SIZE (160 * 120 * 3)
#define RGB565_QVGA_BUFFER_SIZE (320 * 240 * 3)
#define RGB565_VGA_BUFFER_SIZE (640 * 480 * 3)


namespace Eloquent {
    namespace Vision {
        /**
         * @tparam T
         * @tparam width
         * @tparam height
         * @tparam depth
         */
        template<typename T, uint16_t width, uint16_t height, uint8_t depth>
        class Image {
        public:
            T buffer[width * height * depth];

            /**
             * Constructor
             * @param memoryBuffer
             */
            Image() :
                _width(width),
                _height(height),
                _depth(depth) {

                for (size_t i = 0; i < getLength(); i++)
                    buffer[i] = 0;
            }

            /**
             *
             * @return
             */
            uint16_t getWidth() {
                return _width;
            }

            /**
             *
             * @return
             */
            uint16_t getHeight() {
                return _height;
            }

            /**
             *
             * @return
             */
            uint16_t getDepth() {
                return _depth;
            }

            /**
             *
             * @return
             */
            size_t getLength() {
                return getWidth() * getHeight() * getDepth();
            }

            /**
             *
             * @param newWidth
             */
            void setWidth(uint16_t newWidth) {
                _width = newWidth;
            }

            /**
             *
             * @param setHeight
             */
            void setHeight(uint16_t setHeight) {
                _height = setHeight;
            }

            /**
             *
             * @param newDepth
             */
            void setDepth(uint8_t newDepth) {
                _depth = newDepth;
            }

            /**
             * Get pixel at (x, y)
             * @param x
             * @param y
             * @return
             */
            T at(uint16_t x, uint16_t y) {
                float accumulator = 0;

                for (uint8_t i = 0; i < _depth; i++)
                    accumulator += at(x, y, i);

                return accumulator / _depth;
            }

            /**
             * Get pixel by (x, y, z)
             * @param x
             * @param y
             * @param z
             * @return
             */
            T at(uint16_t x, uint16_t y, uint8_t z) {
                return at(((size_t) y) * _width * _depth + x * _depth + z);
            }

            /**
             * Get pixel by index
             * @param index
             * @return
             */
            T at(size_t index) {
                return buffer[index];
            }

            /**
             * Set pixel at coordinates (x, y)
             * @param x
             * @param y
             * @param value
             */
            void setXY(uint16_t x, uint16_t y, T value) {
                const size_t offset = ((size_t) y) * _width * _depth + x * _depth;

                for (uint8_t i = 0; i < _depth; i++) {
                    buffer[offset + i] = value;
                }
            }

            /**
             * Set pixel at coordinates (x, y)
             * @param x
             * @param y
             * @param r
             * @param g
             * @param b
             */
            void setXY(uint16_t x, uint16_t y, uint8_t r, uint8_t g, uint8_t b) {
                const size_t offset = y * _width * _depth + x * _depth;

                if (_depth == 3) {
                    buffer[offset + 0] = r;
                    buffer[offset + 1] = g;
                    buffer[offset + 2] = b;
                }
                else {
                    buffer[offset] = (((uint16_t) r) + g + b) / 3;
                }
            }

            /**
             * Shift all pixels to the right by a given number of bits
             * @param shift
             */
            void rshift(uint8_t shift) {
                map([shift](T pixel) {
                    return pixel >> shift;
                });
            }

            /**
             * Shift all pixels to the left by a given number of bits
             * @param shift
             */
            void lshift(uint8_t shift) {
                map([shift](T pixel) {
                    return pixel << shift;
                });
            }

            /**
             * Add value to each pixel
             * @param offset
             */
            void add(T offset) {
                map([offset](T pixel) {
                    return pixel + offset;
                });
            }

            /**
             * Add value to each pixel.
             * If result is out of range, cap
             * @param offset
             * @param m
             * @param M
             */
            void addInRange(T offset, T m, T M) {
                const float low = m - offset;
                const float high = M - offset;

                map([offset, m, M, low, high](T pixel) {
                    return pixel >= high ? M : (pixel <= low ? m : pixel + offset);
                });
            }

            /**
             * Multiply each pixel by a given scale
             * @tparam U
             * @param scale
             */
            template<typename U>
            void mult(U scale) {
                map([scale](T pixel) {
                    return pixel * scale;
                });
            }

            /**
             * Multiply each pixel by a given scale
             * If result is out of range, cap
             * @param scale
             * @param m
             * @param M
             */
            template<typename U>
            void multInRange(U scale, T m, T M) {
                const float low = m / scale;
                const float high = M / scale;

                map([scale, m, M, low, high](T pixel) {
                    return pixel >= high ? M : (pixel <= low ? m : pixel * scale);
                });
            }

            /**
             * Power each pixel by a given exponent
             * @param exponent
             */
            void power(float exponent) {
                map([exponent](T pixel) {
                    return pow(pixel, exponent);
                });
            }

            /**
             * Power each pixel by a given exponent
             * If result is out of range, cap
             * @param exponent
             * @param m
             * @param M
             */
            void powerInRange(float exponent, T m, T M) {
                const float low = pow(m, 1 / exponent);
                const float high = pow(M, 1 / exponent);

                map([exponent, m, M, low, high](T pixel) {
                    return pixel >= high ? M : (pixel <= low ? m : pow(pixel, exponent));
                });
            }

            /**
             * Map each pixel to a new value
             * @tparam Map
             * @param mapper
             */
            template<typename Map>
            void map(Map mapper) {
                for (size_t i = 0; i < getLength(); i++)
                    buffer[i] = mapper(buffer[i]);
            }

            /**
             *
             * @tparam Printer
             * @tparam Config
             * @param printer
             * @param config
             */
            template<class Printer, typename Config>
            void printTo(Printer& printer, Config& config) {
                printTo(printer, config.precision, config.byteSeparator, config.pixelSeparator, config.rowSeparator, config.end);
            }

            /**
             *
             * @tparam Printer
             * @param printer
             * @param precision
             * @param byteSeparator
             * @param pixelSeparator
             * @param rowSeparator
             * @param end
             * @return
             */
            template<class Printer>
            void printTo(Printer& printer, uint8_t precision, char byteSeparator = ',', char pixelSeparator = ' ', char rowSeparator = '\n', char end = '\0') {
                for (uint16_t y = 15; y < _height; y++) {
                    for (uint16_t x = 0; x < _width; x++) {
                        for (uint8_t z = 0; z < _depth; z++) {
                            printer.print(at(x, y, z), precision);

                            if (z != _depth - 1)
                                printer.print(byteSeparator);
                        }

                        if (x != _width - 1)
                            printer.print(pixelSeparator);
                    }

                    if (y != _height - 1)
                        printer.print(rowSeparator);
                }

                if (end != '\0')
                    printer.print(end);
            }

            /**
             * Write byte data
             * @tparam Writer
             * @param writer
             */
            template<class Writer>
            void writeTo(Writer& writer) {
                for (size_t i = 0; i < getLength(); i++)
                    writer.write((uint8_t) at(i));
            }

        protected:
            uint16_t _width;
            uint16_t _height;
            uint16_t _depth;
        };
    }
}