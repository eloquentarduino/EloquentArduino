//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./BaseTransform.h"

namespace Eloquent {
    namespace Vision {
        namespace Transform {
            namespace Gray {
                /**
                 * Apply transform to image buffer
                 */
                class BaseTransform {
                public:

                    /**
                     * Apply transform
                     * @param src
                     * @param width
                     * @param height
                     */
                    virtual void apply(uint8_t *src, uint16_t *width, uint16_t *height) = 0;

                    /**
                     * Apply transform
                     * @param src
                     * @param width
                     * @param height
                     */
                    virtual void apply(uint8_t *src, uint8_t *dest, uint16_t *width, uint16_t *height) = 0;
                };
            }
        }
    }
}