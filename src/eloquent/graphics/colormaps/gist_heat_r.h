//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Gist_heat_r {
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
                uint8_t red[64] = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 248, 242, 236, 230, 224, 218, 212, 206, 200, 194, 188, 182, 176, 170, 163, 157, 151, 145, 139, 133, 127, 121, 115, 109, 103, 97, 91, 85, 78, 72, 66, 60, 54, 48, 42, 36, 30, 24, 18, 12, 6, 0};
                uint8_t green[64] = {255, 246, 238, 230, 222, 214, 206, 198, 190, 182, 174, 165, 157, 149, 141, 133, 125, 117, 109, 101, 93, 85, 76, 68, 60, 52, 44, 36, 28, 20, 12, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                uint8_t blue[64] = {255, 238, 222, 206, 190, 174, 157, 141, 125, 109, 93, 76, 60, 44, 28, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Gist_heat_r gist_heat_r);