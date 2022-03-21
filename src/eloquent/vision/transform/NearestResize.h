//
// Created by Simone on 04/03/2022.
//

#pragma once


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
            template<uint16_t sourceWidth, uint16_t sourceHeight>
            class NearestResize : public Transform {
            public:

                /**
                 * Constructor
                 * @param newWidth
                 * @param newHeight
                 */
                NearestResize(uint16_t newWidth, uint16_t newHeight) :
                    _newWidth(newWidth),
                    _newHeight(newHeight) {

                }

                /**
                 *
                 * @param buffer
                 */
                void apply(uint8_t *buffer, uint16_t *width, uint16_t *height) {
                    uint16_t blockSizeX = sourceWidth / _newWidth;
                    uint16_t blockSizeY = sourceHeight / _newHeight;
                    uint16_t sourceLength = sourceWidth * sourceHeight;
                    uint16_t newLength = _newWidth * _newHeight;

                    for (
                            uint16_t sourceY = blockSizeY / 2, newY = 0;
                            sourceY < sourceHeight && newY < _newHeight;
                            sourceY += blockSizeY, newY += 1
                    ) {
                        uint16_t sourceOffset = sourceY * sourceWidth;
                        uint16_t newOffset = newY * _newWidth;
                        uint8_t rowBuffer[sourceWidth] = {0};

                        for (
                                uint16_t sourceX = blockSizeX / 2, newX = 0;
                                sourceX < sourceWidth && newX < _newWidth;
                                sourceX += blockSizeX, newX += 1
                        ) {
                            rowBuffer[newX] = buffer[sourceX + sourceOffset];
                        }

                        memcpy(buffer + newOffset, rowBuffer, _newWidth);
                    }

                    memset(buffer + newLength, 0, sourceLength - newLength);
                    *width = _newWidth;
                    *height = _newHeight;
                }

            protected:
                uint16_t _newWidth;
                uint16_t _newHeight;
            };
        }
    }
}