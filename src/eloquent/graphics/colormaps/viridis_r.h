//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Viridis_r {
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
                uint8_t red[64] = {253, 243, 233, 223, 212, 202, 191, 181, 170, 159, 149, 139, 129, 119, 109, 100, 89, 81, 73, 66, 59, 53, 47, 42, 38, 35, 32, 31, 30, 30, 31, 31, 33, 34, 36, 37, 39, 40, 42, 43, 45, 46, 48, 50, 52, 54, 56, 58, 60, 62, 64, 66, 67, 69, 70, 71, 71, 72, 72, 71, 71, 70, 69, 68};
                uint8_t green[64] = {231, 229, 228, 227, 225, 224, 223, 221, 219, 217, 215, 213, 211, 208, 206, 203, 199, 196, 193, 190, 186, 183, 179, 176, 172, 168, 165, 161, 157, 153, 150, 146, 141, 137, 134, 130, 126, 122, 119, 115, 111, 107, 103, 99, 95, 91, 87, 83, 77, 73, 68, 64, 59, 54, 49, 44, 39, 34, 29, 24, 18, 12, 6, 1};
                uint8_t blue[64] = {36, 30, 25, 24, 26, 30, 36, 43, 50, 56, 63, 70, 76, 82, 88, 93, 100, 104, 109, 113, 117, 120, 123, 126, 129, 131, 133, 135, 136, 138, 139, 140, 140, 141, 141, 142, 142, 142, 142, 142, 142, 142, 141, 141, 141, 140, 140, 139, 138, 137, 135, 133, 131, 129, 126, 123, 119, 115, 111, 106, 101, 95, 90, 84};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Viridis_r viridis_r);