#pragma once

#include "RandomAccessDecoder.h"


namespace Eloquent {
    namespace Vision {
        namespace IO {
            namespace Decoders {
                /**
                 * Decode RGB channel from RGB 565 images
                 */
                class RGB565RandomAccessDecoder : public RandomAccessDecoder {
                protected:
                    /**
                     * Get channel value
                     * @param x
                     * @param y
                     * @param mask
                     * @param shift
                     * @return
                     */
                    uint8_t _get(uint8_t *image, uint16_t width, uint16_t height, uint16_t x, uint16_t y, uint16_t mask, uint8_t shiftRight, uint8_t shiftLeft = 0) {
                        uint32_t offset = (y * width + x) * 2;
                        uint16_t *pointer = (uint16_t *) (&image[offset]);
                        uint16_t rgb = __builtin_bswap16(*pointer);

                        return ((rgb & mask) >> shiftRight) << shiftLeft;
                    }
                };
            }
        }
    }
}