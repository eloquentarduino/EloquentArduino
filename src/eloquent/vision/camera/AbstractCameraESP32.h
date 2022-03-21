//
// Created by Simone on 04/03/2022.
//

#pragma once

#include <esp_camera.h>
#include "./CameraErrors.h"
#include "./AbstractCamera.h"


namespace Eloquent {
    namespace Vision {
        namespace Camera {
            /**
             * Abstract camera interface for ESP32-based cameras
             */
            class AbstractCameraESP32 : public AbstractCamera {
            public:

                /**
                 * Init camera
                 * @return true on succes, false on error
                 */
                bool begin() {
                    camera_config_t config;

                    config.ledc_channel = LEDC_CHANNEL_0;
                    config.ledc_timer = LEDC_TIMER_0;
                    config.xclk_freq_hz = _freq;
                    config.frame_size = _size;
                    config.fb_count = 1;

                    setPins(&config);
                    configure(&config);

                    if (esp_camera_init(&config) != ESP_OK) {
                        setError(Error::INITALIZATION_ERROR);
                        return false;
                    }

                    sensor_t *sensor = esp_camera_sensor_get();
                    //sensor->set_framesize(sensor, _size);

                    return true;
                }

                /**
                 * Capture image and write to given container
                 * @tparam FrameContainer
                 * @param container
                 * @return true is image was captured, false otherwise
                 */
                template<class FrameContainer>
                bool captureTo(FrameContainer &container) {
                    if (!isOk())
                        return false;

                    _frame = esp_camera_fb_get();

                    if (_frame->len == 0) {
                        return setError(Error::CAPTURE_ERROR);
                    }

                    container.write(_frame->buf, _frame->len);

                    if (_autoRelease)
                        free();

                    return true;
                }

                /**
                 * Release frame
                 */
                void free() {
                    esp_camera_fb_return(_frame);
                }

                /**
                 *
                 */
                void setHighFreq() {
                    _freq = 20000000;
                }

                /**
                 *
                 */
                void setLowFreq() {
                    _freq = 10000000;
                }

                /**
                 * Disable automatic memory mamangement
                 */
                void manageMemoryManually() {
                    _autoRelease = false;
                }

            protected:
                uint32_t _freq = 10000000;
                framesize_t _size = FRAMESIZE_QVGA;
                camera_fb_t *_frame;
                bool _autoRelease = false;

                /**
                 * Camera-specific configuration
                 * @param config
                 */
                virtual void configure(camera_config_t *config) {

                }

                /**
                 * Configure camera pins
                 * @param config
                 */
                virtual void setPins(camera_config_t *config) = 0;
            };
        }
    }
}
