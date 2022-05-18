//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Nipy_spectral_r {
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
                uint8_t red[64] = {204, 204, 204, 204, 208, 213, 219, 228, 239, 250, 255, 255, 255, 255, 255, 255, 253, 248, 242, 236, 220, 203, 187, 130, 71, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 19, 62, 105, 134, 128, 123, 113, 75, 37, 0};
                uint8_t green[64] = {204, 139, 74, 9, 0, 0, 0, 0, 0, 0, 26, 75, 123, 159, 175, 191, 206, 217, 228, 238, 243, 249, 254, 255, 255, 255, 246, 235, 224, 213, 203, 192, 181, 170, 160, 154, 160, 165, 170, 170, 170, 169, 164, 158, 153, 143, 132, 121, 90, 52, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                uint8_t blue[64] = {204, 139, 74, 9, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 58, 101, 138, 148, 159, 170, 187, 203, 219, 221, 221, 221, 221, 221, 221, 211, 195, 178, 167, 162, 156, 151, 145, 140, 129, 86, 43, 0};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Nipy_spectral_r nipy_spectral_r);