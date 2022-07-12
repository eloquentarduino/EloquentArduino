//
// Created by Simone on 24/06/2022.
//

#pragma once

#include "../pins/m5wide.h"
#include "../BaseEsp32Camera.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace Esp32 {
                class M5WideCamera : public BaseEsp32Camera {
                protected:
                    /**
                     *
                     */
                    void configureSensor() {
                        //vflip();
                        //hmirror();
                    }
                };
            }
        }
    }
}
