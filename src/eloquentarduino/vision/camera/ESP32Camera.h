#pragma once

#include <esp_camera.h>
#include "pins.h"

namespace Eloquent {
    namespace Vision {
        namespace Camera {

            /**
             * Eloquent API to take frames from an ESP32-compatible camera
             */
            class ESP32Camera {
            public:
                /**
                 *
                 */
                ESP32Camera(pixformat_t pixelFormat) :
                    _pixelFormat(pixelFormat) {

                }

                uint8_t getDepth() {
                    return _pixelFormat == PIXFORMAT_GRAYSCALE ? 1 : 3;
                }

                /**
                 *
                 * @param frameSize
                 * @param pixelFormat
                 * @param jpegQuality
                 * @return
                 */
                bool begin(framesize_t frameSize, uint8_t jpegQuality = 30,
                           uint32_t freq = 20000000) {
                    camera_config_t config;

                    config.ledc_channel = LEDC_CHANNEL_0;
                    config.ledc_timer = LEDC_TIMER_0;
                    config.pin_d0 = Y2_GPIO_NUM;
                    config.pin_d1 = Y3_GPIO_NUM;
                    config.pin_d2 = Y4_GPIO_NUM;
                    config.pin_d3 = Y5_GPIO_NUM;
                    config.pin_d4 = Y6_GPIO_NUM;
                    config.pin_d5 = Y7_GPIO_NUM;
                    config.pin_d6 = Y8_GPIO_NUM;
                    config.pin_d7 = Y9_GPIO_NUM;
                    config.pin_xclk = XCLK_GPIO_NUM;
                    config.pin_pclk = PCLK_GPIO_NUM;
                    config.pin_vsync = VSYNC_GPIO_NUM;
                    config.pin_href = HREF_GPIO_NUM;
                    config.pin_sscb_sda = SIOD_GPIO_NUM;
                    config.pin_sscb_scl = SIOC_GPIO_NUM;
                    config.pin_pwdn = PWDN_GPIO_NUM;
                    config.pin_reset = RESET_GPIO_NUM;
                    config.xclk_freq_hz = freq;
                    config.pixel_format = _pixelFormat;
                    config.frame_size = frameSize;
                    config.jpeg_quality = jpegQuality;
                    config.fb_count = 1;

                    bool ok = esp_camera_init(&config) == ESP_OK;

                    sensor_t *sensor = esp_camera_sensor_get();
                    sensor->set_framesize(sensor, frameSize);

                    return ok;
                }

                /**
                 *
                 * @return
                 */
                camera_fb_t *capture() {
                    return (_frame = esp_camera_fb_get());
                }

            protected:
                pixformat_t _pixelFormat;
                camera_fb_t *_frame;
            };
        }
    }
}