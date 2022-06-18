//
// Created by Simone on 18/05/2022.
//

#pragma once
#include "../../macros.h"


namespace Eloquent {
    namespace Graphics {
        namespace Colormaps {
            class Tab10_r {
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
                uint8_t red[64] = {23, 23, 23, 23, 23, 23, 23, 188, 188, 188, 188, 188, 188, 127, 127, 127, 127, 127, 127, 227, 227, 227, 227, 227, 227, 227, 140, 140, 140, 140, 140, 140, 148, 148, 148, 148, 148, 148, 214, 214, 214, 214, 214, 214, 214, 44, 44, 44, 44, 44, 44, 255, 255, 255, 255, 255, 255, 31, 31, 31, 31, 31, 31, 31};
                uint8_t green[64] = {190, 190, 190, 190, 190, 190, 190, 189, 189, 189, 189, 189, 189, 127, 127, 127, 127, 127, 127, 119, 119, 119, 119, 119, 119, 119, 86, 86, 86, 86, 86, 86, 103, 103, 103, 103, 103, 103, 39, 39, 39, 39, 39, 39, 39, 160, 160, 160, 160, 160, 160, 127, 127, 127, 127, 127, 127, 119, 119, 119, 119, 119, 119, 119};
                uint8_t blue[64] = {207, 207, 207, 207, 207, 207, 207, 34, 34, 34, 34, 34, 34, 127, 127, 127, 127, 127, 127, 194, 194, 194, 194, 194, 194, 194, 75, 75, 75, 75, 75, 75, 189, 189, 189, 189, 189, 189, 40, 40, 40, 40, 40, 40, 40, 44, 44, 44, 44, 44, 44, 14, 14, 14, 14, 14, 14, 180, 180, 180, 180, 180, 180, 180};
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Graphics::Colormaps::Tab10_r tab10_r);