//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./NearestResize.h"


namespace Eloquent {
    namespace Vision {
        namespace Transform {

            /**
             *
             * @tparam sourceWidth
             * @tparam sourceHeight
             * @tparam newWidth
             * @tparam newHeight
             */
            template<uint16_t sourceWidth, uint16_t sourceHeight, uint16_t destWidth, uint16_t destHeight>
            class BilinearResize : public Transform {
            public:

                /**
                 *
                 * @param src
                 * @param width
                 * @param height
                 */
                void apply(uint8_t *src, uint16_t *width, uint16_t *height) {
                    uint16_t currentWidth = *width;
                    uint16_t currentHeight = *height;

                    while (currentWidth >= destWidth * 2 && currentHeight >= destHeight * 2) {
                        halve(src, currentWidth, currentHeight);
                        currentWidth /= 2;
                        currentHeight /= 2;
                    }

                    // uneven resize
                    if (currentWidth > destWidth) {
                        NearestResize<sourceWidth, sourceHeight, destWidth, destHeight> resize;

                        resize.apply(src, &currentWidth, &currentHeight);
                    }


                    *width = currentWidth;
                    *height = currentHeight;
                }

            protected:
                /**
                 * Scale down image by half
                 *
                 * @param src
                 * @param dest
                 * @param width
                 * @param height
                 */
                void halve(uint8_t *src, uint16_t width, uint16_t height) {
                    uint16_t i = 0;

                    // @perf on ESP32 it is not much slower than a more optimized implementation
                    // 3500 us vs 3000 us
                    for (uint16_t y = 0; y < height; y += 2) {
                        const uint16_t offset = y * width;
                        //uint16_t row[sourceWidth] = {0};

                        for (uint16_t x = 0; x < width; x += 2) {
                            uint16_t a = src[offset + x];
                            uint16_t b = src[offset + x + 1];
                            uint16_t c = src[offset + width + x];
                            uint16_t d = src[offset + width + x + 1];

                            src[i++] = (a + b + c + d) / 4;
                        }
                    }
                }
            };
        }
    }
}