#pragma once


namespace Eloquent {
    namespace Vision {
        namespace Processing {

            /**
             * Get histogram of R, G, B channels
             *
             * @tparam binSize
             */
            template<uint8_t numBins>
            class RGBHistogram {
            public:
                uint16_t rHistogram[numBins];
                uint16_t gHistogram[numBins];
                uint16_t bHistogram[numBins];

                /**
                 * Constructor
                 */
                RGBHistogram() {
                    isPowerOfTwo = (numBins & (numBins - 1)) == 0;
                    uint8_t maxBins = numBins > 64 ? 64 : numBins;

                    // pre-compute conversion constants
                    if (isPowerOfTwo) {
                        float log2 = log(2);

                        rShift = log(32.0f  / maxBins) / log2;
                        gShift = log(64.0f / maxBins) / log2;
                        bShift = log(32.0f  / maxBins) / log2;
                    }
                    else {
                        rDx = (maxBins > 32 ? 32 : maxBins) / 32.0f;
                        gDx = maxBins / 64.0f;
                        bDx = (maxBins > 32 ? 32 : maxBins) / 32.0f;
                    }

                    clear();
                }

                /**
                 * Compute histogram of given frame
                 * @param frame camera frame
                 * @param len frame length
                 */
                void update(uint8_t *frame, uint16_t len) {
                    uint8_t r, g, b;

                    clear();

                    // decode RGB565 format
                    // try to optimize for speed

                    // if numBins is power of 2, use bit shifts for binning
                    if (isPowerOfTwo) {
                        for (uint16_t i = 0; i < len; i += 2) {
                            next(frame + i, &r, &g, &b);

                            rHistogram[r >> rShift] += 1;
                            gHistogram[g >> gShift] += 1;
                            bHistogram[b >> bShift] += 1;
                        }
                    }
                    // else use slow multiplication
                    else {
                        for (uint16_t i = 0; i < len; i += 2) {
                            next(frame + i, &r, &g, &b);

                            rHistogram[(int) (r * rDx)] += 1;
                            gHistogram[(int) (g * gDx)] += 1;
                            bHistogram[(int) (b * bDx)] += 1;
                        }
                    }
                }

            protected:
                bool isPowerOfTwo;
                float rDx;
                float gDx;
                float bDx;
                uint8_t rShift;
                uint8_t gShift;
                uint8_t bShift;

                /**
                 * Clear existing histogram
                 */
                void clear() {
                    for (uint8_t i = 0; i < numBins; i++) {
                        rHistogram[i] = 0;
                        gHistogram[i] = 0;
                        bHistogram[i] = 0;
                    }
                }

                /**
                 * Read next pixel
                 *
                 * @param buf
                 * @param r
                 * @param g
                 * @param b
                 */
                void next(uint8_t *buf, uint8_t *r, uint8_t *g, uint8_t *b) {
                    uint8_t high = *buf;
                    uint8_t low = *(buf + 1);

                    *r = (high & 0b11111000) >> 3;
                    *g = ((high & 0b111) << 3) | ((low & 0b11100000) >> 5);
                    *b = low & 0b00011111;
                }
            };

        }
    }
}