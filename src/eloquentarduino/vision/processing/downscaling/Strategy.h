#pragma once


namespace Eloquent {
    namespace Vision {
        namespace Processing {
            namespace Downscaling {

                /**
                 * Abstract class for downscaling strategies
                 */
                 template<uint8_t blockSizeX, uint8_t blockSizeY>
                class Strategy {
                public:

                    /**
                     * Test if pixel is relevant for the strategy
                     * @param x
                     * @param y
                     * @return
                     */
                    virtual const bool test(uint8_t x, uint8_t y) = 0;

                    /**
                     * Process pixel
                     * @param x
                     * @param y
                     * @param pixel
                     */
                    virtual void accumulate(uint8_t x, uint8_t y, uint8_t pixel) = 0;

                    /**
                     * Collapse accumulated pixels to a single value
                     * @param block
                     * @param width
                     * @param height
                     * @return
                     */
                    virtual uint8_t reduce() = 0;

                    /**
                     * Reset strategy count
                     */
                    void reset() {
                        _pixel = 0;
                    }

                protected:
                    uint16_t _pixel;
                };
            }
        }
    }
}