//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class PRGn_r {
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
                uint8_t red[64] = {0, 4, 8, 12, 17, 21, 25, 34, 44, 54, 64, 74, 84, 94, 106, 118, 131, 143, 155, 166, 174, 183, 191, 199, 207, 215, 220, 225, 230, 235, 239, 244, 245, 243, 240, 238, 235, 233, 229, 223, 218, 212, 206, 200, 194, 188, 181, 175, 168, 162, 155, 149, 144, 138, 133, 127, 121, 115, 106, 98, 89, 81, 72, 64};
                uint8_t green[64] = {68, 76, 84, 92, 101, 109, 117, 126, 134, 143, 151, 160, 168, 176, 184, 191, 198, 205, 212, 219, 222, 226, 229, 232, 236, 239, 240, 242, 243, 244, 245, 246, 244, 238, 233, 227, 222, 216, 210, 203, 195, 188, 180, 173, 165, 157, 149, 140, 132, 123, 115, 105, 94, 83, 72, 60, 49, 40, 33, 26, 20, 13, 6, 0};
                uint8_t blue[64] = {27, 31, 35, 40, 44, 49, 53, 59, 66, 73, 79, 86, 93, 101, 111, 121, 131, 141, 151, 160, 168, 177, 185, 193, 201, 209, 215, 221, 227, 232, 238, 244, 245, 243, 241, 238, 236, 233, 231, 227, 223, 219, 215, 211, 207, 201, 196, 190, 184, 179, 173, 167, 160, 154, 148, 141, 135, 128, 119, 110, 101, 92, 83, 75};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::PRGn_r prgn_r);