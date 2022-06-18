//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Spectral_r {
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
                uint8_t red[64] = {94, 87, 80, 73, 66, 59, 52, 55, 64, 72, 80, 88, 97, 106, 117, 128, 139, 150, 161, 171, 181, 190, 200, 209, 218, 228, 233, 237, 241, 245, 249, 253, 254, 254, 254, 254, 254, 254, 253, 253, 253, 253, 253, 253, 253, 251, 250, 248, 247, 246, 244, 241, 236, 231, 226, 221, 216, 210, 201, 192, 184, 175, 166, 158};
                uint8_t green[64] = {79, 88, 97, 106, 115, 124, 133, 142, 151, 160, 170, 179, 188, 195, 200, 204, 208, 212, 217, 221, 225, 229, 232, 236, 240, 244, 246, 247, 249, 251, 252, 254, 252, 247, 242, 237, 232, 227, 222, 214, 206, 198, 190, 182, 174, 164, 154, 144, 133, 123, 113, 104, 97, 89, 82, 74, 67, 59, 49, 39, 30, 20, 10, 1};
                uint8_t blue[64] = {162, 166, 170, 174, 179, 183, 187, 186, 182, 178, 174, 171, 167, 164, 164, 164, 164, 164, 164, 163, 161, 160, 158, 156, 154, 152, 156, 163, 169, 175, 181, 187, 186, 178, 170, 162, 153, 145, 137, 130, 124, 117, 110, 104, 97, 92, 87, 83, 78, 73, 68, 68, 70, 71, 73, 75, 77, 78, 76, 74, 72, 70, 68, 66};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Spectral_r spectral_r);