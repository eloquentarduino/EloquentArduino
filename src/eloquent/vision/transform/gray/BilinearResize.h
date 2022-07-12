//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./NearestResize.h"


namespace Eloquent {
    namespace Vision {
        namespace Transform {
            namespace Gray {

                /**
                 *
                 * @tparam sourceWidth
                 * @tparam sourceHeight
                 * @tparam newWidth
                 * @tparam newHeight
                 */
                template<uint16_t sourceWidth, uint16_t sourceHeight, uint16_t destWidth, uint16_t destHeight>
                class BilinearResize  {
                public:

                    /**
                     *
                     * @tparam Image
                     * @param src
                     */
                    template<typename Image>
                    void apply(Image *src) {
                        apply(src, src);
                    }

                    /**
                     *
                     * @param src
                     * @param width
                     * @param height
                     */
                    template<typename Image>
                    void apply(Image *src, Image *dest) {
                        const uint16_t sWidth = src->getWidth();
                        const uint16_t sHeight = src->getHeight();

                        while (dest->getWidth() >= destWidth * 2 && dest->getHeight() >= destHeight * 2) {
                            halve(src, dest);
                        }

                        // uneven resize
                        //if (dest->getWidth() > destWidth) {
                        //    NearestResize<sourceWidth, sourceHeight, destWidth, destHeight> resize;

                        //    resize.apply(src, &currentWidth, &currentHeight);
                        //}

                        dest->setWidth(destWidth);
                        dest->setHeight(destHeight);
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
                    template<typename Image>
                    void halve(Image *src, Image *dest) {
                        uint16_t i = 0;
                        uint16_t height = src->getHeight();
                        uint16_t width = src->getWidth();

                        // @perf on ESP32 it is not much slower than a more optimized implementation
                        // 3500 us vs 3000 us
                        for (uint16_t y = 0; y < height; y += 2) {
                            const uint16_t offset = y * width;
                            //uint16_t row[sourceWidth] = {0};

                            for (uint16_t x = 0; x < width; x += 2) {
                                uint16_t a = src->get(offset + x);
                                uint16_t b = src[offset + x + 1];
                                uint16_t c = src[offset + width + x];
                                uint16_t d = src[offset + width + x + 1];

                                dest->set(i++, (a + b + c + d) / 4);
                            }
                        }

                        dest->setWidth(src->getWidth() / 2);
                        dest->setHeight(src->getHeight() / 2);
                    }
                };
            }
        }
    }
}