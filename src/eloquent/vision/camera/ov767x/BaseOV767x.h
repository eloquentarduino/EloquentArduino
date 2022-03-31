//
// Created by Simone on 29/03/2022.
//

#pragma once

#include <Arduino_OV767X.h>
#include "../BaseCamera.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace OV767x {
                /**
                 *
                 * @tparam width
                 * @tparam height
                 * @tparam depth
                 */
                template<uint16_t width, uint16_t height, uint8_t bytesPerPixel>
                class BaseOV767x : public BaseCamera {
                public:
                    uint8_t pixels[width * height * bytesPerPixel];

                    /**
                     * Constructor
                     */
                    BaseOV767x() :
                        _fps(1) {
                        //memset(pixels, 0, width * height * bytesPerPixel);
                    }

                    /**
                     * Set camera FPS
                     * You MUST call this BEFORE begin()
                     * @param fps
                     */
                    void setFps(uint8_t fps) {
                        _fps = fps;
                    }

                    /**
                     *
                     */
                    void setHighFreq() {
                        setFps(5);
                    }

                    /**
                     *
                     */
                    void setLowFreq() {
                        setFps(1);
                    }

                protected:
                    uint8_t _fps;

                    /**
                     * Update image
                     *
                     * @param buffer
                     */
                    virtual void setFrameBuffer(uint8_t *buffer) = 0;

                    /**
                     *
                     * @param buffer
                     */
                    bool concreteCapture() override {
                        Camera.readFrame(pixels);
                        setFrameBuffer(pixels);

                        return true;
                    }
                };
            }
        }
    }
}