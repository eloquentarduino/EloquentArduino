//
// Created by Simone on 18/06/2022.
//

#pragma once


namespace Eloquent {
    namespace Vision {
        namespace Features {
            /**
             * Local Binary Pattern with R=? and P=8
             */
             template<uint8_t r>
             class LocalBinaryPatternP8 {
             public:

                /**
                 *
                 * @tparam Image
                 * @param src
                 * @param dest
                 */
                template<typename Image>
                void transform(Image *src, Image *dest = NULL) {
                    const uint16_t height = src->getHeight();
                    const uint16_t width = src->getWidth();
                    uint32_t i = 0;

                    if (dest == NULL)
                        dest = src;

                    for (uin16_t y = r; y < height - r; y++) {
                        for (uint16_t x = r; x < width - r; x++) {
                            const uint8_t pixel = src->at(x, y);
                            const uint8_t p0 = this->at(src, x, y, -1, -1);
                            const uint8_t p1 = this->at(src, x, y, 0, -1);
                            const uint8_t p2 = this->at(src, x, y, 1, -1);
                            const uint8_t p3 = this->at(src, x, y, 1, 0);
                            const uint8_t p4 = this->at(src, x, y, 1, 1);
                            const uint8_t p5 = this->at(src, x, y, 0, 1);
                            const uint8_t p6 = this->at(src, x, y, 1, 1);
                            const uint8_t p7 = this->at(src, x, y, -1, 0);

                            const uint8_t lbp =
                                    (p0 > pixel)
                                    | ((p1 > pixel) << 1)
                                    | ((p2 > pixel) << 2)
                                    | ((p3 > pixel) << 3)
                                    | ((p4 > pixel) << 4)
                                    | ((p5 > pixel) << 5)
                                    | ((p6 > pixel) << 6)
                                    | ((p7 > pixel) << 7);

                            const uint8_t robustLbp = this->robust(lbp);

                            dest.set(i, robustLbp);
                            i += 1;
                        }

                        dest.setWidth(width - 2 * r);
                        dest.setHeight(height - 2 * r);
                    }
                }

             protected:
                 const uint8_t uniformLookup[256] = {1, 2, 3, 4, 5, 0, 6, 7, 8, 0, 0, 0, 9, 0, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14, 0, 15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 20, 0, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 27, 0, 28, 29, 30, 31, 0, 32, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 37, 38, 0, 39, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 43, 44, 0, 45, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 47, 48, 49, 0, 50, 0, 0, 0, 51, 52, 53, 0, 54, 55, 56, 57, 58};


                /**
                 * Get pixel value at given (x, y) with offset
                 * @param src
                 * @param x
                 * @param y
                 * @param xOffset
                 * @param yOffset
                 * @return
                 */
                 template<typename Image>
                virtual uint8_t at(Image *src, uint16_t x, uint16_t y, uint8_t xOffset, uint8_t yOffset) = 0;

                 /**
                  * Convert raw LBP value to robust, if any
                  * @param lbp
                  * @return
                  */
                virtual uint8_t robust(uint8_t lbp) = 0;
             };

            /**
             * Local Binary Pattern with R=1 and P=8
             */
            class LocalBinaryPatternR1P8 : public LocalBinaryPatternP8<1> {
            protected:

                /**
                 *
                 * @param src
                 * @param x
                 * @param y
                 * @param xOffset
                 * @param yOffset
                 * @return
                 */
                uint8_t at(Image *src, uint16_t x, uint16_t y, uint8_t xOffset, uint8_t yOffset) {
                    return src->at(x - xOffset, y - yOffset);
                }

                /**
                  * Convert raw LBP value to robust, if any
                  * @param lbp
                  * @return
                  */
                virtual uint8_t robust(uint8_t lbp) {
                    return lbp;
                }
            };

            /**
             * Local Binary Pattern with R=2 and P=8
             */
            class LocalBinaryPatternR2P8 : public LocalBinaryPatternP8<2> {
                /**
                 *
                 * @param src
                 * @param x
                 * @param y
                 * @param xOffset
                 * @param yOffset
                 * @return
                 */
                uint8_t at(Image *src, uint16_t x, uint16_t y, uint8_t xOffset, uint8_t yOffset) {
                    if (yOffset == -1) {
                        switch (xOffset) {
                            case -1:
                                return src->at(x - 1, y - 1);
                            case 0:
                                return src->at(x, y - 2);
                            case 1:
                                return src->at(x + 1, y - 1);
                            default:
                                return 0;
                        }
                    }

                    if (yOffset == 1) {
                        switch (xOffset) {
                            case -1:
                                return src->at(x - 1, y + 1);
                            case 0:
                                return src->at(x, y + 2);
                            case 1:
                                return src->at(x + 1, y + 1);
                            default:
                                return 0;
                        }
                    }

                    if (yOffset == 0) {
                        switch (xOffset) {
                            case -1:
                                return src->at(x - 2, y);
                            case 1:
                                return src->at(x + 2, y);
                            default:
                                return 0;
                        }
                    }

                    return 0;
                }

                /**
                  * Convert raw LBP value to robust, if any
                  * @param lbp
                  * @return
                  */
                virtual uint8_t robust(uint8_t lbp) {
                    return lbp;
                }
            };

            /**
             * LBP with uniform patterns
             */
            class UniformLocalBinaryPatternR1P8 : public LocalBinaryPatternR1P8 {
            protected:
                const uint8_t uniformLookup[256] = {1, 2, 3, 4, 5, 0, 6, 7, 8, 0, 0, 0, 9, 0, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14, 0, 15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 20, 0, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 27, 0, 28, 29, 30, 31, 0, 32, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 37, 38, 0, 39, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 43, 44, 0, 45, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 47, 48, 49, 0, 50, 0, 0, 0, 51, 52, 53, 0, 54, 55, 56, 57, 58};

                /**
                  * Convert raw LBP value to robust, if any
                  * @param lbp
                  * @return
                  */
                virtual uint8_t robust(uint8_t lbp) {
                    return uniformLookup[lbp];
                }
            };

            /**
             * LBP with uniform patterns
             */
            class UniformLocalBinaryPatternR2P8 : public LocalBinaryPatternR2P8 {
            protected:
                const uint8_t uniformLookup[256] = {1, 2, 3, 4, 5, 0, 6, 7, 8, 0, 0, 0, 9, 0, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14, 0, 15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 20, 0, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 27, 0, 28, 29, 30, 31, 0, 32, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 37, 38, 0, 39, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 43, 44, 0, 45, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 47, 48, 49, 0, 50, 0, 0, 0, 51, 52, 53, 0, 54, 55, 56, 57, 58};

                /**
                  * Convert raw LBP value to robust, if any
                  * @param lbp
                  * @return
                  */
                virtual uint8_t robust(uint8_t lbp) {
                    return uniformLookup[lbp];
                }
            };
        }
    }
}