//
// Created by Simone on 29/03/2022.
//

#pragma once

#include "../../../../macros.h"
#include "../../../image/gray/cif.h"
#include "../BaseOV767x.h"

using namespace Eloquent::Vision::Cam::OV767x;


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace OV767x {
                namespace Gray {
                    /**
                     * OV767x grayscale camera CIF resolution
                     */
                    class Cif : public BaseOV767x<352, 240, 1> {
                    public:
                        Eloquent::Vision::Image::Gray::Cif image;

                    protected:

                        /**
                         *
                         * @return
                         */
                        bool configure() override {
                            return Camera.begin(CIF, GRAYSCALE, _fps);
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

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::OV767x::Gray::Cif camera);