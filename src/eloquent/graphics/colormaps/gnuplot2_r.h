//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Gnuplot2_r {
            public:

                /**
                 * Convert single byte to RGB color
                 * @param x
                 * @param r
                 * @param g
                 * @param b
                 */
                void convert(uint8_t x, uint8_t *r, uint8_t *g, uint8_t *b) {
                    *r = red[x << 2];
                    *g = green[x << 2];
                    *b = blue[x << 2];
                }

            protected:
                uint8_t red[64] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 243, 230, 218, 205, 192, 180, 167, 154, 142, 129, 117, 104, 91, 79, 66, 53, 41, 28, 15, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                uint8_t green[64] = {255, 255, 255, 255, 255, 255, 247, 239, 231, 222, 214, 206, 198, 190, 182, 174, 166, 158, 150, 141, 133, 125, 117, 109, 101, 93, 85, 77, 69, 61, 52, 44, 36, 28, 20, 12, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                uint8_t blue[64] = {255, 204, 153, 103, 52, 2, 7, 15, 23, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 113, 121, 129, 137, 145, 153, 161, 169, 177, 185, 193, 202, 210, 218, 226, 234, 242, 250, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 242, 226, 210, 194, 178, 161, 145, 129, 113, 97, 80, 64, 48, 32, 16, 0};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Gnuplot2_r gnuplot2_r);