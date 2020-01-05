#pragma once

#include "Kernels.h"

using namespace Eloquent::CV::Kernels;

namespace Eloquent {
    namespace CV {
        /**
         * Downsample an image by averaging its regions
         */
        template<uint8_t cols, uint8_t rows>
        class DownsampledImage {
        public:
            DownsampledImage(uint16_t width, uint16_t height) {
                _w = width;
                _h = height;
                _tilew = ceil(_w / cols);
                _tileh = ceil(_h / rows);
            }

            /**
             *
             * @return
             */
            uint16_t height() {
                return rows;
            }

            /**
             *
             * @return
             */
            uint16_t width() {
                return cols;
            }

            /**
             *
             * @return
             */
            uint32_t length() {
                return width() * height();
            }

            /**
             * Get value at <x, y>
             * @param x
             * @param y
             * @return
             */
            uint8_t at(uint16_t x, uint16_t y) {
                return _tiles[cols * y + x];
            }

            /**
             * Copy tiles from another image
             * @param other
             */
            void copyFrom(DownsampledImage &other) {
                for (uint16_t i = 0; i < rows * cols; i++)
                    _tiles[i] = other._tiles[i];
            }

            /**
             * Reduce a frame to its tiled (compressed) version
             * @param image
             */
            void summarize(uint8_t *image, Kernel* kernel) {
                clear();

                for (uint32_t i = 0; i < _w * _h; i++) {
                    const uint16_t x = i % _w;
                    const uint16_t y = floor(i / _w);
                    const uint8_t tilex = floor(x / _tilew);
                    const uint8_t tiley = floor(y / _tileh);
                    const uint16_t idx = tiley * cols + tilex;

                    _tiles[idx] = kernel->apply(_tiles[idx], image[i]);
                }

                for (uint16_t i = 0; i < rows * cols; i++)
                    _tiles[i] = kernel->map(_tiles[i]);
            }

            /**
             * Get tile value
             * @param i
             * @return
             */
            uint8_t tileAt(uint16_t i) {
                return _tiles[i];
            }

        protected:
            uint16_t _w;
            uint16_t _h;
            uint16_t _tilew;
            uint16_t _tileh;
            uint16_t _tiles[rows * cols] = {0};

            /**
             * Set all tiles to 0
             */
            void clear() {
                for (uint16_t i = 0; i < rows * cols; i++)
                    _tiles[i] = 0;
            }
        };
    }
}