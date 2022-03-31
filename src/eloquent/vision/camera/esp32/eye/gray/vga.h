//
// Created by Simone on 31/03/2022.
//

#pragma once

#include "../../../../../macros.h"
#include "../../../../image/gray/vga.h"
#include "../../pins/eye.h"
#include "../../BaseEsp32Camera.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace Esp32 {
                /**
                 * M5 wide
                 * Grayscale
                 * VGA
                 */
                class Camera : public BaseEsp32Camera {
                public:
                    Eloquent::Vision::Image::Gray::Vga image;

                    /**
                     *
                     * @return
                     */
                    framesize_t getFrameSize() {
                        return FRAMESIZE_VGA;
                    }

                    /**
                     *
                     * @return
                     */
                    pixformat_t getPixFormat() {
                        return PIXFORMAT_GRAYSCALE;
                    }

                    /**
                     *
                     * @param buffer
                     */
                    void setFrameBuffer(uint8_t *buffer) {
                        image.refresh(buffer);
                    }

                };
            }
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::Esp32::Camera camera);