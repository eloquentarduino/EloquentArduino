//
// Created by Simone on 20/07/2022.
//

#pragma once


#include <camera.h>
#include <himax.h>
#include "../../macros.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            class PortentaCamera {
            public:

                /**
                 *
                 */
                PortentaCamera() :
                    isBegin(false),
                    cam(himax) {
                    grayscale();
                    setFPS(30);
                    setTimeout(100);
                }

                /**
                 * Set grayscale mode
                 * Call before begin()
                 *
                 */
                void grayscale() {
                    mode = CAMERA_GRAYSCALE;
                }

                /**
                 * Set RGB565 mode
                 * Call before begin()
                 *
                 */
                void rgb565() {
                    mode = CAMERA_RGB565;
                }

                /**
                 * Set FPS
                 *
                 * @param fps
                 */
                void setFPS(uint8_t fps) {
                    this->fps = fps;
                }

                /**
                 * Set capture timeout, in milliseconds
                 *
                 * @param timeout
                 */
                void setTimeout(uint16_t timeout) {
                    this->timeout = timeout;
                }

                /**
                 * Init camera
                 *
                 * @return
                 */
                bool begin() {
                    cam.debug(Serial);
                    cam.begin(CAMERA_R320x240, mode, fps);

                    return true;
                }

                /**
                 * Capture frame
                 *
                 * @return
                 */
                bool capture() {
                    if (!isBegin)
                        isBegin = begin();

                    if (!isBegin)
                        return false;

                    return cam.grabFrame(buffer, 50) == 0;
                }

                /**
                 * Release buffer
                 *
                 */
                void free() {
                    // do nothing
                }

            protected:
                bool isBegin;
                int mode;
                uint8_t fps;
                uint16_t timeout;
                HM01B0 himax;
                Camera cam;
                FrameBuffer buffer;
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::PortentaCamera camera);