#pragma once

#include "../../io/decoders/RandomAccessDecoder.h"
#include "Strategy.h"
#include "Center.h"
#include "Core.h"
#include "FullAverage.h"

using namespace Eloquent::Vision::IO::Decoders;


namespace Eloquent {
    namespace Vision {
        namespace Processing {
            namespace Downscaling {

                /**
                 * Scale image down according to a given strategy
                 * @tparam sourceWidth
                 * @tparam sourceHeight
                 * @tparam destWidth
                 * @tparam destHeight
                 */
                template<uint16_t sourceWidth, uint16_t sourceHeight, uint8_t destWidth, uint8_t destHeight>
                class Downscaler {
                public:
                    /**
                     *
                     * @param decoder
                     * @param strategy
                     */
                    Downscaler(RandomAccessDecoder *decoder, Strategy<sourceWidth / destWidth, sourceHeight / destHeight> *strategy) :
                            _decoder(decoder),
                            _strategy(strategy),
                            _blockSizeX(sourceWidth / destWidth) ,
                            _blockSizeY(sourceHeight / destHeight) {

                    }

                    /**
                     * Downscale image according to the given strategy
                     * @param source
                     * @param dest
                     */
                    void downscale(uint8_t *source, uint8_t *dest) {
                        for (uint16_t y = 0, destY = 0; y < sourceHeight; y += _blockSizeY, destY++) {
                            for (uint16_t x = 0, destX = 0; x < sourceWidth; x += _blockSizeX, destX++) {

                                // fill the block
                                for (uint8_t blockY = 0; blockY < _blockSizeY; blockY++) {
                                    for (uint8_t blockX = 0; blockX < _blockSizeX; blockX++) {
                                        // only decode relevant pixels
                                        if (_strategy->test(blockX, blockY))
                                            _strategy->accumulate(blockX, blockY, _decoder->get(source, sourceWidth, sourceHeight, x + blockX, y + blockY));
                                    }
                                }

                                dest[destY * destWidth + destX] = _strategy->reduce();
                                _strategy->reset();
                            }
                        }
                    }

                protected:
                    RandomAccessDecoder *_decoder;
                    Strategy<sourceWidth / destWidth, sourceHeight / destHeight> *_strategy;
                    const uint8_t _blockSizeX;
                    const uint8_t _blockSizeY;
                };
            }
        }
    }
}