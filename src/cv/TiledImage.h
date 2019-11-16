#pragma once

namespace Eloquent {
    /**
     * Represent a frame by summarizing it by regions
     */
    template<uint8_t rows, uint8_t cols>
    class TiledImage {
    public:
        TiledImage(uint16_t width, uint16_t height) {
            _w = width;
            _h = height;
            _tilew = ceil(_w / cols);
            _tileh = ceil(_h / rows);
        }

        /**
         *
         * @return
         */
        uint8_t getRows() {
            return rows;
        }

        /**
         *
         * @return
         */
        uint8_t getCols() {
            return cols;
        }

        /**
         * Copy tiles from another image
         * @param other
         */
        void copyFrom(TiledImage& other) {
            for (uint16_t i = 0; i < rows * cols; i++)
                _tiles[i] = other._tiles[i];
        }

        /**
         * Reduce a frame to its tiled (compressed) version
         * @param image
         */
        void summarize(uint8_t *image) {
            // clear tiles
            for (uint16_t i = 0; i < rows * cols; i++)
                _tiles[i] = 0;

            for (uint16_t i = 0; i < _w * _h; i++) {
                const uint16_t x = i % _w;
                const uint16_t y = floor(i / _w);
                const uint8_t tilex = floor(x / _tilew);
                const uint8_t tiley = floor(y / _tileh);

                _tiles[tiley * cols + tilex] = reduce(_tiles[tiley * cols + tilex], image[i]);
            }
        }

        /**
         * Get tile value
         * @param i
         * @return
         */
        uint8_t tileAt(uint16_t i) {
            return map(_tiles[i], i);
        }

    protected:
        uint16_t _w;
        uint16_t _h;
        uint16_t _tilew;
        uint16_t _tileh;
        uint16_t _tiles[rows * cols] = {0};

        /**
         *
         * @param current
         * @param pixel
         * @return
         */
        uint16_t reduce(uint16_t current, uint8_t pixel) {
            return current + pixel * 10 / (_tilew * _tileh);
        }

        /**
         *
         * @param pixel
         * @param i
         * @return
         */
        uint8_t map(uint16_t pixel, uint16_t i) {
            return pixel / 10;
        }
    };
}