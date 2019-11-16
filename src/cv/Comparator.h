#pragma once

#include "TiledImage.h"

namespace Eloquent {
    /**
     * Compare two tiled images, tile by tile
     */
    class TiledImageComparator {
    public:
        TiledImageComparator(float tileChangePercentThreshold = 0, uint8_t tileChangeAbsoluteThreshold = 0) :
                _tileChangePercentThreshold(tileChangePercentThreshold),
                _tileChangeAbsoluteThreshold(tileChangeAbsoluteThreshold) {

        }

        /**
         * Set absolute sensitivity
         * @param threshold
         */
        void setTileChangeAbsoluteThreshold(uint8_t threshold) {
            _tileChangeAbsoluteThreshold = threshold;
        }

        /**
         * Set relative sensitivity
         * @param threshold
         */
        void setTileChangePercentThreshold(float threshold) {
            _tileChangePercentThreshold = threshold;
        }

        /**
         * Get number of tiles that differ
         * @tparam rows
         * @tparam cols
         * @param first
         * @param second
         * @return
         */
        template<uint8_t rows, uint8_t cols>
        uint16_t compare(TiledImage<rows, cols>& first, TiledImage<rows, cols>& second) {
            uint16_t differentTiles = 0;

            for (uint16_t i = 0; i < rows * cols; i++) {
                float a = first.tileAt(i);
                float b = second.tileAt(i);
                float delta = abs(b - a);

                if (_tileChangeAbsoluteThreshold && delta >= _tileChangeAbsoluteThreshold)
                    differentTiles += 1;
                else if (delta / (b + a) / 2 > _tileChangePercentThreshold)
                    differentTiles += 1;
            }

            return differentTiles;
        }

    protected:
        uint8_t _tileChangeAbsoluteThreshold;
        float _tileChangePercentThreshold;
    };
}