#pragma once

#include "RandomAccessDecoder.h"


namespace Eloquent {
    namespace Vision {
        namespace IO {
            namespace Decoders {
                /**
                 * Decode gray channel
                 */
                class GrayscaleRandomAccessDecoder : public RandomAccessDecoder {
                public:
                    /**
                     * @param x
                     * @param y
                     * @return
                     */
                    uint8_t get(uint8_t *image, uint16_t width, uint16_t height, uint16_t x, uint16_t y) {
                        return image[y * width + x];
                    }
                };
            }
        }
    }
}