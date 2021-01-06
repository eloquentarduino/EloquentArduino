#pragma once


namespace Eloquent {
    namespace Vision {
        namespace IO {
            namespace Decoders {
                /**
                 * Abstract API to decode images from different formats in random-access
                 */
                class RandomAccessDecoder {
                public:

                    /**
                     * Get value at (x, y)
                     */
                    virtual uint8_t get(uint8_t *image, uint16_t width, uint16_t height, uint16_t x, uint16_t y) = 0;
                };
            }
        }
    }
}