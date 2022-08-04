//
// Created by Simone on 20/07/2022.
//

#pragma once


#include <camera.h>
#include <himax.h>
#include "../../macros.h"


HM01B0 himax;
FrameBuffer buffer(320, 240, 2);


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            class PortentaCamera : public Camera {
            public:

                /**
                 *
                 */
                PortentaCamera() :
                    Camera(himax),
                    isBegin(false) {
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
                    Camera::begin(CAMERA_R320x240, CAMERA_GRAYSCALE, 30);

                    return true;
                }

                /**
                 * Capture frame
                 *
                 * @return
                 */
                bool capture() {
                    return grabFrame(buffer, 50) == 0;
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
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::PortentaCamera camera);