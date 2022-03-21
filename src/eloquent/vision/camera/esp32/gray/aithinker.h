//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "../../AbstractCameraESP32.h"
#include "../vendor/AiThinker.h"


namespace Eloquent {
    namespace Vision {
        namespace Camera {

            /**
             *
             */
            class Camera : public AbstractCameraESP32, AiThinkerCamera {
            protected:
                /**
                 *
                 * @param config
                 */
                void configure(camera_config_t *config) override {
                    setPins(config);
                    config->pixel_format = PIXFORMAT_GRAYSCALE;
                    //config.jpeg_quality = _jpeqQuality;
                }
            };
        }
    }
}