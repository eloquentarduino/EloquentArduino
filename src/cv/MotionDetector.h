#pragma once

#include "TiledImage.h"
#include "Comparator.h"

namespace Eloquent {
    /**
      * Detect motion between two frames
      * Here motion is really a change in the tiled versions
      * of the two frames
      * @tparam rows
      * @tparam cols
      */
    template<uint8_t rows, uint8_t cols>
    class MotionDetector {
    public:
        MotionDetector(
                uint16_t width,
                uint16_t height,
                uint16_t minDifferentTiles = 1,
                float tileChangePercentThreshold = 0,
                float tileChangeAbsoluteThreshold = 0) :
                _minDifferentTiles(minDifferentTiles),
                _curr(width, height),
                _prev(width, height),
                _comparator(tileChangePercentThreshold, tileChangeAbsoluteThreshold) {

        }

        /**
         *
         * @param threshold
         */
        void setTileChangeAbsoluteThreshold(uint8_t threshold) {
            _comparator.setTileChangeAbsoluteThreshold(threshold);
        }

        /**
         *
         * @param threshold
         */
        void setTileChangePercentThreshold(float threshold) {
            _comparator.setTileChangePercentThreshold(threshold);
        }

        /**
         * Update with new image
         * @param image
         */
        void update(uint8_t *image) {
            _prev.copyFrom(_curr);
            _curr.summarize(image);
        }

        /**
         * Detect if motion happened
         * @return
         */
        bool detect() {
            return _comparator.compare(_curr, _prev) > _minDifferentTiles;
        }

        /**
         * Update and detect motion
         * @param image
         * @return
         */
        bool detect(uint8_t *image) {
            update(image);

            return detect();
        }

    protected:
        uint16_t _minDifferentTiles;
        TiledImage<rows, cols> _curr;
        TiledImage<rows, cols> _prev;
        TiledImageComparator _comparator;
    };
}