//
// Created by Simone on 29/03/2022.
//

#pragma once

#include "../../../../macros.h"
#include "../../../image/gray/qvga.h"
#include "../BaseOV767x.h"

using namespace Eloquent::Vision::Cam::OV767x;


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace OV767x {
                namespace Gray {
                    /**
                     * OV767x grayscale camera QVGA resolution
                     */
                    class Qvga : public BaseOV767x<320, 240, 1> {
                    public:
                        Eloquent::Vision::Image::Gray::Qvga image;

                    protected:

                        /**
                         *
                         * @return
                         */
                        bool configure() override {
                            return Camera.begin(QVGA, GRAYSCALE, _fps);
                        }

                        /**
                         *
                         * @param buffer
                         */
                        void setFrameBuffer(uint8_t *buffer) override {
                            this->image.refresh(buffer);
                        }
                    };
                }
            }
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::OV767x::Gray::Qvga camera);