//
// Created by Simone on 04/03/2022.
//

#pragma once


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
                class NearestResize {
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
                     * Perform resize
                     * @tparam Image 
                     * @param src 
                     * @param dest 
                     */
                    template<typename Src, typename Dest>
                    void apply(Src *src, Dest *dest) {
                        const uint16_t sWidth = src->getWidth();
                        const uint16_t sHeight = src->getHeight();

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

                                dest->set(newOffset + newX, src->at(sourceX, sourceY));
                            }
                        }

                        dest->setWidth(destWidth);
                        dest->setHeight(destHeight);
                    }
                };
            }
        }
    }
}