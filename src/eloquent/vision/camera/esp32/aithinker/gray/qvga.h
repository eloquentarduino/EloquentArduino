//
// Created by Simone on 31/03/2022.
//

#pragma once

#include "../../../../../macros.h"
#include "../../../../image/gray/qvga.h"
#include "../../pins/aithinker.h"
#include "../../BaseEsp32Camera.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace Esp32 {
                /**
                 * M5 wide
                 * Grayscale
                 * QVGA
                 */
                class Camera : public BaseEsp32Camera {
                public:
                    Eloquent::Vision::Image::Gray::Qvga image;

                    /**
                     *
                     * @return
                     */
                    framesize_t getFrameSize() {
                        return FRAMESIZE_QVGA;
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