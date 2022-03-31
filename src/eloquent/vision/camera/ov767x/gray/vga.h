//
// Created by Simone on 29/03/2022.
//

#pragma once

#include "../../../../macros.h"
#include "../../../image/gray/vga.h"
#include "../BaseOV767x.h"

using namespace Eloquent::Vision::Cam::OV767x;


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace OV767x {
                namespace Gray {
                    /**
                     * OV767x grayscale camera VGA resolution
                     */
                    class Vga : public BaseOV767x<640, 480, 1> {
                    public:
                        Eloquent::Vision::Image::Gray::Vga image;

                    protected:

                        /**
                         *
                         * @return
                         */
                        bool configure() override {
                            return Camera.begin(VGA, GRAYSCALE, _fps);
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

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::OV767x::Gray::Vga camera);