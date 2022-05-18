//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Gist_heat {
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
                uint8_t red[64] = {0, 6, 12, 18, 24, 30, 36, 42, 48, 54, 60, 66, 72, 78, 85, 91, 97, 103, 109, 115, 121, 127, 133, 139, 145, 151, 157, 163, 170, 176, 182, 188, 194, 200, 206, 212, 218, 224, 230, 236, 242, 248, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
                uint8_t green[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 12, 20, 28, 36, 44, 52, 60, 68, 76, 84, 93, 101, 109, 117, 125, 133, 141, 149, 157, 165, 174, 182, 190, 198, 206, 214, 222, 230, 238, 246, 255};
                uint8_t blue[64] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 28, 44, 60, 76, 93, 109, 125, 141, 157, 174, 190, 206, 222, 238, 255};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Gist_heat gist_heat);