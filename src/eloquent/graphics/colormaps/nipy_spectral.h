//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Nipy_spectral {
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
                uint8_t red[64] = {0, 37, 75, 113, 123, 128, 134, 105, 62, 19, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 71, 130, 187, 203, 220, 236, 242, 248, 253, 255, 255, 255, 255, 255, 255, 250, 239, 228, 219, 213, 208, 204, 204, 204, 204};
                uint8_t green[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 52, 90, 121, 132, 143, 153, 158, 164, 169, 170, 170, 170, 165, 160, 154, 160, 170, 181, 192, 203, 213, 224, 235, 246, 255, 255, 255, 254, 249, 243, 238, 228, 217, 206, 191, 175, 159, 123, 75, 26, 0, 0, 0, 0, 0, 0, 9, 74, 139, 204};
                uint8_t blue[64] = {0, 43, 86, 129, 140, 145, 151, 156, 162, 167, 178, 195, 211, 221, 221, 221, 221, 221, 221, 219, 203, 187, 170, 159, 148, 138, 101, 58, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 74, 139, 204};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Nipy_spectral nipy_spectral);