//
// Created by Simone on 31/03/2022.
//

#pragma once

#include "../../../../../macros.h"
#include "../../../../image/gray/hd.h"
#include "../../pins/m5.h"
#include "../../BaseEsp32Camera.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace Esp32 {
                /**
                 * M5 wide
                 * Grayscale
                 * HD
                 */
                class Camera : public BaseEsp32Camera {
                public:
                    Eloquent::Vision::Image::Gray::Hd image;

                    /**
                     *
                     * @return
                     */
                    framesize_t getFrameSize() {
                        return FRAMESIZE_HD;
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