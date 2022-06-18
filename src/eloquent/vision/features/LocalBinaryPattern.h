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
                            const uint8_t p0 = src->at(x - r, y - r);
                            const uint8_t p1 = src->at(x, y - r);
                            const uint8_t p2 = src->at(x + r, y - r);
                            const uint8_t p3 = src->at(x - r, y);
                            const uint8_t p4 = src->at(x + r, y);
                            const uint8_t p5 = src->at(x - r, y + r);
                            const uint8_t p6 = src->at(x, y + r);
                            const uint8_t p7 = src->at(x + r, y + r);

                            const uint8_t lbp =
                                    (p0 > pixel)
                                    | ((p1 > pixel) << 1)
                                    | ((p2 > pixel) << 2)
                                    | ((p3 > pixel) << 3)
                                    | ((p4 > pixel) << 4)
                                    | ((p5 > pixel) << 5)
                                    | ((p6 > pixel) << 6)
                                    | ((p7 > pixel) << 7)

                            dest.set(i, uniformLookup[lbp]);
                            i += 1;
                        }

                        dest.setWidth(width - 2 * r);
                        dest.setHeight(height - 2 * r);
                    }
                }

             protected:
                 const uint8_t uniformLookup[256] = {1, 2, 3, 4, 5, 0, 6, 7, 8, 0, 0, 0, 9, 0, 10, 11, 12, 0, 0, 0, 0, 0, 0, 0, 13, 0, 0, 0, 14, 0, 15, 16, 17, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 19, 0, 0, 0, 20, 0, 21, 22, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 24, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 0, 0, 26, 0, 0, 0, 27, 0, 28, 29, 30, 31, 0, 32, 0, 0, 0, 33, 0, 0, 0, 0, 0, 0, 0, 34, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 35, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 36, 37, 38, 0, 39, 0, 0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 41, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 42, 43, 44, 0, 45, 0, 0, 0, 46, 0, 0, 0, 0, 0, 0, 0, 47, 48, 49, 0, 50, 0, 0, 0, 51, 52, 53, 0, 54, 55, 56, 57, 58};
             };

            /**
             * Local Binary Pattern with R=1 and P=8
             */
            class LocalBinaryPatternR1P8 : public LocalBinaryPatternP8<1> {};

            /**
             * Local Binary Pattern with R=2 and P=8
             */
            class LocalBinaryPatternR1P8 : public LocalBinaryPatternP8<2> {};
        }
    }
}