#pragma once

#include "ColorHistogram.h"


namespace Eloquent {
    namespace Vision {
        namespace Processing {

            /**
             * Get histogram of Y, U, V channels
             *
             * @tparam binSize
             */
            template<uint8_t numBins>
            class YUVHistogram : public ColorHistogram<numBins> {
            public:
                uint16_t yHistogram[numBins];
                uint16_t uHistogram[numBins];
                uint16_t vHistogram[numBins];

                /**
                 * Constructor
                 */
                YUVHistogram() {
                    isPowerOfTwo = (numBins & (numBins - 1)) == 0;
                    uint8_t maxBins = numBins > 256 ? 256 : numBins;

                    // pre-compute conversion constants
                    if (isPowerOfTwo) {
                        shift = log(256.0f  / maxBins) / log(2);
                    }
                    else {
                        dx = maxBins / 256.0f;
                    }

                    clear();
                }

                /**
                 * Compute histogram of given frame
                 * @param frame camera frame
                 * @param len frame length
                 */
                void update(uint8_t *frame, uint16_t len) {
                    uint8_t y1, y2, u, v;

                    clear();

                    // decode YUV422 format
                    // try to optimize for speed

                    // if numBins is power of 2, use bit shifts for binning
                    if (isPowerOfTwo) {
                        for (uint16_t i = 0; i < len; i += 4) {
                            next(frame + i, &y1, &u, &y2, &v);

                            yHistogram[y1 >> shift] += 1;
                            yHistogram[y2 >> shift] += 1;
                            uHistogram[u  >> shift] += 1;
                            vHistogram[v  >> shift] += 1;
                        }
                    }
                    // else use slow multiplication
                    else {
                        for (uint16_t i = 0; i < len; i += 4) {
                            next(frame + i, &y1, &u, &y2, &v);

                            yHistogram[(int) (y1 * dx)] += 1;
                            yHistogram[(int) (y1 * dx)] += 1;
                            uHistogram[(int) (u  * dx)] += 1;
                            vHistogram[(int) (v  * dx)] += 1;
                        }
                    }
                }

                /**
                 * Test if image looks like dark
                 * @param threshBin
                 * @param threshPercent
                 * @return
                 */
                bool looksDark(float threshBin = 0.25, float threshPercent = 0.9) {
                    // test if first 1/5 of Y bins yield 90%+ of values
                    return this->getPercentBelowBin(yHistogram, threshBin) >= threshPercent;
                }

                /**
                 * Test if image looks like bright
                 * @param threshBin
                 * @param threshPercent
                 * @return
                 */
                bool looksBright(float threshBin = 0.75, float threshPercent = 0.9) {
                    // test if first 1/5 of Y bins yield 90%+ of values
                    return this->getPercentAboveBin(yHistogram, threshBin) >= threshPercent;
                }


            protected:
                bool isPowerOfTwo;
                float dx;
                uint8_t shift;

                /**
                 * Clear existing histogram
                 */
                void clear() {
                    for (uint8_t i = 0; i < numBins; i++) {
                        yHistogram[i] = 0;
                        uHistogram[i] = 0;
                        vHistogram[i] = 0;
                    }
                }

                /**
                 * Read next pixel
                 *
                 * @param buf
                 * @param y1
                 * @param u
                 * @param y2
                 * @param v
                 */
                void next(uint8_t *buf, uint8_t *y1, uint8_t *u, uint8_t *y2, uint8_t *v) {
                    *y1 = *buf;
                    *u  = *(buf + 1);
                    *y2 = *(buf + 2);
                    *v  = *(buf + 3);
                }
            };

        }
    }
}