//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./BaseTransform.h"


namespace Eloquent {
    namespace Vision {
        namespace Transform {
            namespace Gray {
                /**
                 * Resize image by subsampling
                 * No interpolation
                 *
                 * @tparam sourceWidth
                 * @tparam sourceHeight
                 * @tparam newWidth
                 * @tparam newHeight
                 */
                template<uint16_t sourceWidth, uint16_t sourceHeight, uint16_t destWidth, uint16_t destHeight>
                class NearestResize : public BaseTransform {
                public:

                    template<typename Image>
                    void apply(Image *image) {
                        const uint16_t sWidth = image->getWidth();
                        const uint16_t sHeight = image->getHeight();

                        const float blockSizeX = sWidth / destWidth;
                        const float blockSizeY = sHeight / destHeight;

                        const uint16_t sourceLength = sWidth * sHeight;
                        const uint16_t newLength = destWidth * destHeight;

                        for (float sourceY = blockSizeY / 2, newY = 0; sourceY < sHeight && newY < destHeight; sourceY += blockSizeY, newY += 1) {
                            uint16_t sourceOffset = sourceY * sWidth;
                            uint16_t newOffset = newY * destWidth;
                            uint8_t rowBuffer[sourceWidth] = {0};

                            for (
                                    float sourceX = blockSizeX / 2, newX = 0;
                                    sourceX < sWidth && newX < destWidth;
                                    sourceX += blockSizeX, newX += 1
                                    ) {

                                image->set(newOffset + newX, image->at(sourceX, sourceY));
                                //rowBuffer[(uint16_t) newX] = src[(uint16_t)(sourceX + sourceOffset)];
                            }

                            //memcpy(dest + newOffset, rowBuffer, destWidth);
                        }

                        image->setWidth(destWidth);
                        image->setHeight(destHeight);
                    }

                    /**
                     * In-place apply
                     * @param buffer
                     * @param width
                     * @param height
                     */
                    void apply(uint8_t *src, uint16_t *width, uint16_t *height) override {
                        apply(src, src, width, height);
                    }

                    /**
                     *
                     * @tparam Target
                     * @param src
                     * @param target
                     * @param width
                     * @param height
                     */
                    template<typename Target>
                    void apply(uint8_t *src, Target &target, uint16_t *width, uint16_t *height) {
                        apply(src, target.buffer, width, height);
                    }

                    /**
                     *
                     * @param src
                     * @param width
                     * @param height
                     */
                    void apply(uint8_t *src, uint8_t *dest, uint16_t *width, uint16_t *height) override {
                        const uint16_t sWidth = *width;
                        const uint16_t sHeight = *height;

                        const float blockSizeX = sWidth / destWidth;
                        const float blockSizeY = sHeight / destHeight;

                        const uint16_t sourceLength = sWidth * sHeight;
                        const uint16_t newLength = destWidth * destHeight;

                        for (float sourceY = blockSizeY / 2, newY = 0; sourceY < sHeight && newY < destHeight; sourceY += blockSizeY, newY += 1) {
                            uint16_t sourceOffset = sourceY * sWidth;
                            uint16_t newOffset = newY * destWidth;
                            uint8_t rowBuffer[sourceWidth] = {0};

                            for (
                                    float sourceX = blockSizeX / 2, newX = 0;
                                    sourceX < sWidth && newX < destWidth;
                                    sourceX += blockSizeX, newX += 1
                                    ) {

                                rowBuffer[(uint16_t) newX] = src[(uint16_t)(sourceX + sourceOffset)];
                            }

                            memcpy(dest + newOffset, rowBuffer, destWidth);
                        }

                        //memset(dest + newLength, 0, sourceLength - newLength);
                        *width = destWidth;
                        *height = destHeight;
                    }
                };
            }
        }
    }
}