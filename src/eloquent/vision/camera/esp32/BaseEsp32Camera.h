//
// Created by Simone on 31/03/2022.
//

#pragma once

#include <esp_camera.h>
#include "../BaseCamera.h"

using namespace Eloquent::Vision::Cam;


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace Esp32 {
                /**
                 * Base class for Esp32-based cameras
                 */
                class BaseEsp32Camera : public BaseCamera {
                public:

                    /**
                     * Release frame
                     */
                    void free() override {
                        esp_camera_fb_return(_fb);
                    }

                    /**
                     *
                     */
                    void setHighFreq() {
                        _config.xclk_freq_hz = 20000000;
                    }

                    /**
                     *
                     */
                    void setLowFreq() {
                        _config.xclk_freq_hz = 10000000;
                    }

                protected:
                    camera_config_t _config;
                    sensor_t *_sensor;
                    camera_fb_t *_fb;

                    /**
                     * Get camera resolution
                     *
                     */
                    virtual framesize_t getFrameSize() = 0;

                    /**
                     * Get camera pixel format
                     *
                     */
                    virtual pixformat_t getPixFormat() = 0;

                    /**
                     * Update image buffer
                     *
                     * @param buffer
                     */
                    virtual void setFrameBuffer(uint8_t *buffer) = 0;

                    /**
                     * Set camera-specific configurations
                     *
                     * @param config
                     */
                    virtual void setConfig() {

                    }

                    /**
                     * Set camera-specific pins
                     *
                     * @param config
                     */
                    void setPins() {
                        _config.pin_d0 = Y2_GPIO_NUM;
                        _config.pin_d1 = Y3_GPIO_NUM;
                        _config.pin_d2 = Y4_GPIO_NUM;
                        _config.pin_d3 = Y5_GPIO_NUM;
                        _config.pin_d4 = Y6_GPIO_NUM;
                        _config.pin_d5 = Y7_GPIO_NUM;
                        _config.pin_d6 = Y8_GPIO_NUM;
                        _config.pin_d7 = Y9_GPIO_NUM;
                        _config.pin_xclk = XCLK_GPIO_NUM;
                        _config.pin_pclk = PCLK_GPIO_NUM;
                        _config.pin_vsync = VSYNC_GPIO_NUM;
                        _config.pin_href = HREF_GPIO_NUM;
                        _config.pin_sscb_sda = SIOD_GPIO_NUM;
                        _config.pin_sscb_scl = SIOC_GPIO_NUM;
                        _config.pin_pwdn = PWDN_GPIO_NUM;
                        _config.pin_reset = RESET_GPIO_NUM;
                    }

                    /**
                     * 
                     * @return 
                     */
                    bool configure() override {
                        _config.ledc_channel = LEDC_CHANNEL_0;
                        _config.ledc_timer = LEDC_TIMER_0;
                        _config.fb_count = 1;
                        _config.pixel_format = getPixFormat();
                        _config.frame_size = getFrameSize();

                        if (!_config.xclk_freq_hz)
                            setLowFreq();

                        // let concrete classes add their own customization
                        setPins();
                        setConfig();

                        if (esp_camera_init(&_config) != ESP_OK) {
                            setError(Error::INIT_ERROR);
                            return false;
                        }

                        _sensor = esp_camera_sensor_get();

                        return true;
                    }

                    /**
                     *
                     */
                    bool concreteCapture() override {
                        this->_fb = esp_camera_fb_get();

                        if (this->_fb == NULL || this->_fb->len == 0) {
                            return setError(Error::CAPTURE_ERROR);
                        }

                        this->_bufferLength = this->_fb->len;
                        setFrameBuffer(this->_fb->buf);

                        return true;
                    }
                };
            }
        }
    }
}