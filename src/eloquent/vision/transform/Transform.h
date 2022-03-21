//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./Transform.h"

namespace Eloquent {
    namespace Vision {
        namespace Transform {
            /**
             * Apply transform to image buffer
             */
            class Transform {
            public:
                /**
                 * Apply transform
                 * @param buffer
                 * @param width
                 * @param height
                 */
                virtual void apply(uint8_t *buffer, uint16_t *width, uint16_t *height);
            };
        }
    }
}