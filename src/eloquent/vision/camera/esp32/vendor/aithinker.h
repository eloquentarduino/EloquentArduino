//
// Created by Simone on 04/03/2022.
//

#pragma once


namespace Eloquent {
    namespace Vision {
        namespace Camera {
            /**
             *
             */
            class AiThinkerCamera {
            protected:

                /**
                 *
                 * @param config
                 */
                void setPins(camera_config_t *config) {
                    config.pin_d0 = 5;
                    config.pin_d1 = 18;
                    config.pin_d2 = 19;
                    config.pin_d3 = 21;
                    config.pin_d4 = 36;
                    config.pin_d5 = 39;
                    config.pin_d6 = 34;
                    config.pin_d7 = 35;
                    config.pin_xclk = 0;
                    config.pin_pclk = 22;
                    config.pin_vsync = 25;
                    config.pin_href = 23;
                    config.pin_sscb_sda = 26;
                    config.pin_sscb_scl = 27;
                    config.pin_pwdn = 32;
                    config.pin_reset = -1;
                }
            };
        }
    }
}