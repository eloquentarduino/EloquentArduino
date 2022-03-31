#pragma once

#include "RGB565RandomAccessDecoder.h"


namespace Eloquent {
    namespace Vision {
        namespace IO {
            namespace Decoders {
                /**
                 * Decode G channel from RGB 565 images
                 */
                class Green565RandomAccessDecoder : public RGB565RandomAccessDecoder {
                public:
                    /**
                     * Get G
                     * @param x
                     * @param y
                     * @return
                     */
                    uint8_t get(uint8_t *image, uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
                        return _get(image, width, height, x, y, 0b11111100000, 5, 2);
                    }
                };
            }
        }
    }
}