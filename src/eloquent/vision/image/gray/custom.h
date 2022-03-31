//
// Created by Simone on 30/03/2022.
//

#pragma once

#include "../BaseImage.h"
#include "../../transform/gray/NearestResize.h"

using namespace Eloquent::Vision::Image;
using namespace Eloquent::Vision::Transform::Gray;


namespace Eloquent {
    namespace Vision {
        namespace Image {
            namespace Gray {
                /**
                 * Grayscale image at custom resolution
                 * @tparam width
                 * @tparam height
                 */
                template<uint16_t width, uint16_t height>
                class Custom : public BaseImage<width, height, 1, 1> {
                public:

                    /**
                     *
                     * @param x
                     * @param y
                     * @param v
                     */
                    void set(uint16_t x, uint16_t y, uint8_t v) {
                        set(x, y, 1, v);
                    }

                    /**
                     * Set pixel value
                     * @param x
                     * @param y
                     * @param z
                     * @param v
                     */
                    void set(uint16_t x, uint16_t y, uint8_t z, uint8_t v) {
                        set(y * this->getWidth() + x, v);
                    }

                    /**
                     *
                     * @param x
                     * @param v
                     */
                    void set(uint16_t i, uint8_t v) {
                        if (i < this->getLength())
                            this->buffer[i] = v;
                    }

                    /**
                     * Resize to new dimensions
                     * @param newWidth
                     * @param newHeight
                     */
                    template<uint16_t newWidth, uint16_t newHeight>
                    void resize() {
                        NearestResize<width, height, newWidth, newHeight> resize;

                        resize.apply(this);
                    }

                    /**
                     * Apply transformation
                     * @param transform
                     */
                    void transform(BaseTransform &transform) {
                        transform.apply(this);
                        //transform.apply(this->buffer, &this->_width, &this->_height);
                    }

                protected:

                };
            }
        }
    }
}