//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class YlOrBr_r {
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
                uint8_t red[64] = {102, 108, 114, 121, 127, 134, 140, 147, 153, 160, 166, 173, 179, 186, 192, 199, 205, 209, 213, 217, 221, 225, 229, 233, 236, 239, 241, 243, 246, 248, 250, 252, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 254, 255, 255, 255, 255, 255, 255, 255, 255};
                uint8_t green[64] = {37, 38, 40, 42, 44, 46, 48, 50, 52, 55, 58, 61, 64, 67, 70, 73, 77, 81, 86, 90, 95, 100, 104, 109, 113, 119, 124, 129, 134, 139, 145, 150, 155, 161, 166, 172, 177, 183, 188, 193, 198, 202, 206, 210, 214, 218, 222, 226, 228, 231, 233, 236, 239, 241, 244, 246, 247, 248, 249, 250, 251, 252, 253, 255};
                uint8_t blue[64] = {5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 4, 7, 9, 11, 14, 16, 18, 21, 23, 26, 29, 31, 34, 37, 39, 43, 48, 53, 57, 62, 67, 72, 77, 84, 92, 101, 109, 117, 126, 134, 142, 149, 154, 160, 165, 170, 176, 181, 187, 192, 197, 202, 208, 213, 218, 223, 229};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::YlOrBr_r ylorbr_r);