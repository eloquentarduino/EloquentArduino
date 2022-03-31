#pragma once

#include "Strategy.h"


namespace Eloquent {
    namespace Vision {
        namespace Processing {
            namespace Downscaling {

                /**
                 * Return the block's center pixel value
                 */
                template<uint8_t blockSizeX, uint8_t blockSizeY>
                class FullAverage : public Strategy<blockSizeX, blockSizeY> {
                public:

                    /**
                     *
                     */
                    FullAverage() :
                        _count(blockSizeX * blockSizeY) {

                    }

                    /**
                     * Return always true
                     * @param x
                     * @param y
                     * @return
                     */
                    const bool test(uint8_t x, uint8_t y) {
                        return true;
                    }

                    /**
                     * Save center pixel value
                     * @param x
                     * @param y
                     * @param pixel
                     */
                    void accumulate(uint8_t x, uint8_t y, uint8_t pixel) {
                        _pixel += pixel;
                    }

                    /**
                     * Return pixel value
                     * @param block
                     * @return
                     */
                    uint8_t reduce() {
                        return _pixel / _count;
                    }

                protected:
                    uint16_t _count;
                    uint16_t _pixel;
                };
            }
        }
    }
}