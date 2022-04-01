//
// Created by Simone on 30/03/2022.
//

#pragma once

#include "../BaseImage.h"
#include "../../transform/gray/NearestResize.h"
#include "../../jpeg/JpegBuilder.h"


using namespace Eloquent::Vision::Image;
using namespace Eloquent::Vision::Transform::Gray;
using Eloquent::Vision::Jpeg::JpegBuilder;


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
                     * @param buffer
                     */
                    Custom(uint8_t *buffer = NULL) : BaseImage<width, height, 1, 1>(buffer) {

                    }

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
                     * Resize to QVGA
                     * @return
                     */
                    Custom<width, height>& qvga() {
                        resize<320, 240>();

                        return *this;
                    }

                    /**
                     * Resize to QQVGA
                     * @return
                     */
                    Custom<width, height>& qqvga() {
                        resize<160, 120>();

                        return *this;
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
                     * Resize to new dimensions into a new container
                     * @tparam newWidth
                     * @tparam newHeight
                     * @tparam Image
                     * @param target
                     */
                    template<uint16_t newWidth, uint16_t newHeight, class Image>
                    void resizeTo(Image &target) {
                        NearestResize<width, height, newWidth, newHeight> resize;

                        resize.apply(this, &target);
                    }

                    /**
                     *
                     * @return
                     */
                    JpegBuilder& jpeg() {
                        return JpegBuilder(this->buffer, this->getWidth(), this->getHeight(), 1, 1).grayscale();
                    }

                protected:

                };


                /**
                 * Grayscale image at custom resolution with inner buffer memory
                 * @tparam width
                 * @tparam height
                 */
                template<uint16_t width, uint16_t height>
                class CustomWithBuffer : public Custom<width, height> {
                public:

                    /**
                     * Constructor
                     */
                    CustomWithBuffer() : Custom<width, height>(_stack) {}

                protected:
                    uint8_t _stack[width * height];
                };
            }
        }
    }
}