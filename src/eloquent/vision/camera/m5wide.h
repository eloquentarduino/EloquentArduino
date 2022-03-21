//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "../../macros.h"
#include "./AbstractCameraESP32.h"


namespace Eloquent {
    namespace Vision {
        namespace Camera {
            class M5WideCamera : public AbstractCameraESP32 {
            protected:

                /**
                 *
                 * @param config
                 */
                void setPins(camera_config_t *config) {
                    config->pin_d0 = 32;
                    config->pin_d1 = 35;
                    config->pin_d2 = 34;
                    config->pin_d3 = 5;
                    config->pin_d4 = 39;
                    config->pin_d5 = 18;
                    config->pin_d6 = 36;
                    config->pin_d7 = 19;
                    config->pin_xclk = 27;
                    config->pin_pclk = 21;
                    config->pin_vsync = 25;
                    config->pin_href = 26;
                    config->pin_sscb_sda = 22;
                    config->pin_sscb_scl = 23;
                    config->pin_pwdn = -1;
                    config->pin_reset = 15;
                }
            };

            /**
             * M5 wide camera, grayscale
             */
            class M5WideGrayCamera : public M5WideCamera {
            protected:

                /**
                 *
                 * @param config
                 */
                void configure(camera_config_t *config) override {
                    config->pixel_format = PIXFORMAT_GRAYSCALE;
                }
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Vision::Camera::M5WideGrayCamera grayCamera);