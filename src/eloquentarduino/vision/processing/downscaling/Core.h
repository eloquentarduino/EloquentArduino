#pragma once

#include "Strategy.h"


namespace Eloquent {
    namespace Vision {
        namespace Processing {
            namespace Downscaling {

                /**
                 * Return the block's center region average
                 */
                template<uint8_t blockSizeX, uint8_t blockSizeY>
                class Core : public Strategy<blockSizeX, blockSizeY> {
                public:
                    /**
                     *
                     * @param radius
                     */
                    Core(uint8_t radius) :
                        _radius(radius),
                        _count(0),
                        _centerX(blockSizeX / 2),
                        _centerY(blockSizeY / 2) {

                    }

                    /**
                     * Return true only on center pixels within radius
                     * @param x
                     * @param y
                     * @return
                     */
                    const bool test(uint8_t x, uint8_t y) {
                        return abs(x - _centerX) <= _radius && abs(y - _centerY) <= _radius;
                    }

                    /**
                     * Save center pixel value
                     * @param x
                     * @param y
                     * @param pixel
                     */
                    void accumulate(uint8_t x, uint8_t y, uint8_t pixel) {
                        _pixel += pixel;
                        _count += 1;
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
                    uint8_t _radius;
                    uint16_t _count;
                    uint8_t _centerX;
                    uint8_t _centerY;
                    uint16_t _pixel;
                };
            }
        }
    }
}