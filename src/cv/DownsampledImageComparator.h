#pragma once

#include "DownsampledImage.h"

namespace Eloquent {
    namespace CV {
        /**
         * Compare two downsampled images, tile by tile
         */
        class DownsampledImageComparator {
        public:
            DownsampledImageComparator(float tileChangePercentThreshold = 0, uint8_t tileChangeAbsoluteThreshold = 0) :
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
            uint16_t compare(DownsampledImage <rows, cols> &first, DownsampledImage <rows, cols> &second) {
                uint16_t differentTiles = 0;

                for (uint16_t i = 0; i < rows * cols; i++) {
                    float a = first.tileAt(i);
                    float b = second.tileAt(i);
                    float delta = abs(b - a);

                    if (_tileChangeAbsoluteThreshold && delta >= _tileChangeAbsoluteThreshold)
                        differentTiles += 1;
                    else if (delta / ((b + a) / 2) > _tileChangePercentThreshold)
                        differentTiles += 1;
                }

                return differentTiles;
            }

        protected:
            uint8_t _tileChangeAbsoluteThreshold;
            float _tileChangePercentThreshold;
        };
    }
}