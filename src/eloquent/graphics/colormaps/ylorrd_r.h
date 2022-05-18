//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class YlOrRd_r {
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
                uint8_t red[64] = {128, 135, 143, 151, 158, 166, 174, 182, 189, 194, 199, 204, 208, 213, 218, 223, 227, 230, 234, 237, 240, 243, 246, 250, 252, 252, 252, 252, 252, 252, 252, 252, 253, 253, 253, 253, 253, 253, 253, 253, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255};
                uint8_t green[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 7, 10, 13, 16, 20, 23, 27, 34, 40, 47, 54, 60, 67, 73, 81, 89, 97, 105, 113, 121, 129, 137, 143, 148, 152, 157, 162, 166, 171, 176, 181, 186, 191, 195, 200, 205, 210, 215, 218, 221, 223, 226, 229, 231, 234, 236, 239, 241, 243, 245, 248, 250, 252, 255};
                uint8_t blue[64] = {38, 38, 38, 38, 38, 38, 38, 38, 37, 36, 35, 34, 32, 31, 30, 28, 28, 30, 32, 33, 35, 37, 39, 40, 42, 45, 47, 49, 52, 54, 56, 58, 61, 63, 65, 67, 69, 71, 73, 75, 79, 84, 90, 95, 100, 105, 111, 116, 122, 127, 132, 138, 143, 148, 154, 159, 164, 170, 176, 181, 187, 192, 198, 204};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::YlOrRd_r ylorrd_r);