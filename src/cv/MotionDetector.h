#pragma once

#include "DownsampledImage.h"
#include "DownsampledImageComparator.h"

namespace Eloquent {
    namespace CV {
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
                    DownsampledImageComparator& comparator,
                    Kernel *kernel,
                    uint16_t minDifferentTiles = 1) :
                    _minDifferentTiles(minDifferentTiles),
                    _curr(width, height),
                    _prev(width, height),
                    _comparator(comparator) {

                _kernel = kernel;
            }

            /**
             * Update with new image
             * @param image
             */
            void update(uint8_t *image) {
                _prev.copyFrom(_curr);
                _curr.summarize(image, _kernel);
            }

            /**
             * Detect if motion happened
             * @return
             */
            bool detect() {
                int diff = _comparator.compare(_curr, _prev);

                Serial.print("Change: "); Serial.println(diff);

                return diff > _minDifferentTiles;
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
            DownsampledImage <rows, cols> _curr;
            DownsampledImage<rows, cols> _prev;
            DownsampledImageComparator _comparator;
            Kernel *_kernel;
        };
    }
}