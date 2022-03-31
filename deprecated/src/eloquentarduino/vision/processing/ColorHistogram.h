#pragma once


namespace Eloquent {
    namespace Vision {
        namespace Processing {

            /**
             * Abstract color histogram
             *
             * @tparam binSize
             */
            template<uint8_t numBins>
            class ColorHistogram {
            public:

                /**
                 * Get percent of pixels of histogram below a given bin (excluding)
                 * @param hist
                 * @param bin
                 * @return
                 */
                float getPercentBelowBin(uint16_t *hist, float bin) {
                    uint16_t total = 0;
                    uint16_t below = 0;

                    if (bin < 1)
                        bin = numBins * bin;

                    // count total pixels and pixels below bin
                    for (int i = 0; i < numBins; i++) {
                        uint8_t count = hist[i];
                        total += count;

                        if (i < bin)
                            below += count;
                    }

                    return ((float) below) / total;
                }

                /**
                 * Get percent of pixels of histogram above a given bin (including)
                 * @param hist
                 * @param bin
                 * @return
                 */
                float getPercentAboveBin(uint16_t *hist, float bin) {
                    uint16_t total = 0;
                    uint16_t above = 0;

                    if (bin < 1)
                        bin = numBins * bin;

                    // count total pixels and pixels above bin
                    for (int i = 0; i < numBins; i++) {
                        uint8_t count = hist[i];
                        total += count;

                        if (i >= bin)
                            above += count;
                    }

                    return ((float) above) / total;
                }
            };

        }
    }
}