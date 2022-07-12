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
                        if (_fb != NULL)
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

                    /**
                     *
                     * @param mirror
                     */
                    bool verticalMirror(bool mirror = true) {
                        return setSensorAttribute([mirror](sensor_t *sensor) {
                            sensor->set_vflip(sensor, mirror);
                        });
                    }

                    /**
                     *
                     * @param mirror
                     */
                    bool horizontalMirror(bool mirror = true) {
                        return setSensorAttribute([mirror](sensor_t *sensor) {
                            sensor->set_hmirror(sensor, mirror);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool setLowBrightness() {
                        return setBrightness(-1);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setLowestBrightness() {
                        return setBrightness(-2);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setHighBrightness() {
                        return setBrightness(1);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setHighestBrightness() {
                        return setBrightness(2);
                    }

                    /**
                     *
                     * @param brightness
                     */
                    bool setBrightness(int8_t brightness) {
                        return setSensorAttribute([brightness](sensor_t *sensor) {
                            sensor->set_brightness(sensor, brightness);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool setLowestSaturation() {
                        return setSaturation(-2);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setLowSaturation() {
                        return setSaturation(-1);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setHighSaturation() {
                        return setSaturation(1);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setHighestSaturation() {
                        return setSaturation(2);
                    }

                    /**
                     *
                     * @param saturation
                     */
                    bool setSaturation(int8_t saturation) {
                        return setSensorAttribute([saturation](sensor_t *sensor) {
                            sensor->set_saturation(sensor, saturation);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableAutomaticWhiteBalance() {
                        return setAutomaticWhiteBalance(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableAutomaticWhiteBalance() {
                        return setAutomaticWhiteBalance(false);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setAutomaticWhiteBalance(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_whitebal(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableGainControl() {
                        return setGainControl(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableGainControl() {
                        return setGainControl(false);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setGainControl(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_gain_ctrl(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableExposureControl() {
                        setExposureControl(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableExposureControl() {
                        return setExposureControl(false);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setExposureControl(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_exposure_ctrl(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableAutomaticWhiteBalanceGain() {
                        return setAutomaticWhiteBalanceGain(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableAutomaticWhiteBalanceGain() {
                        return setAutomaticWhiteBalanceGain(false);
                    }

                    /**
                     *
                     * @return
                     */
                    bool setAutomaticWhiteBalanceGain(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_awb_gain(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableAutomaticGainControl() {
                        return setAutomaticGainControl(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableAutomaticGainControl() {
                        return setAutomaticGainControl(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setAutomaticGainControl(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_gain_ctrl(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @param gain
                     * @return
                     */
                    bool setManualGain(uint8_t gain) {
                        return setSensorAttribute([gain](sensor_t *sensor) {
                            sensor->set_agc_gain(sensor, gain);
                        });
                    }

                    /**
                     *
                     * @param exposure
                     * @return
                     */
                    bool setManualExposure(uint16_t exposure) {
                        return setSensorAttribute([exposure](sensor_t *sensor) {
                            sensor->set_aec_value(sensor, exposure);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableAutomaticExposureControl() {
                        return setAutomaticExposureControl(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableAutomaticExposureControl() {
                        return setAutomaticExposureControl(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setAutomaticExposureControl(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_aec2(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableDCW() {
                        return setDCW(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableDCW() {
                        return setDCW(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setDCW(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_dcw(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableBPC() {
                        return setBPC(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableBPC() {
                        return setBPC(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setBPC(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_bpc(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableWPC() {
                        return setWPC(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableWPC() {
                        return setWPC(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setWPC(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_wpc(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableLensCorrection() {
                        return setLensCorrection(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableLensCorrection() {
                        return setLensCorrection(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setLensCorrection(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_lenc(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @return
                     */
                    bool enableRawGamma() {
                        return setRawGamma(true);
                    }

                    /**
                     *
                     * @return
                     */
                    bool disableRawGamma() {
                        return setRawGamma(false);
                    }

                    /**
                     *
                     * @param enable
                     * @return
                     */
                    bool setRawGamma(bool enable) {
                        return setSensorAttribute([enable](sensor_t *sensor) {
                            sensor->set_raw_gma(sensor, enable);
                        });
                    }

                    /**
                     *
                     * @tparam Setter
                     * @param setter
                     * @return
                     */
                    template<typename Setter>
                    bool setSensorAttribute(Setter setter) {
                        if (_sensor != NULL) {
                            setter(_sensor);
                            return true;
                        }

                        return false;
                    }


                    /**
                     *
                     */
                    void flashOn() {
                        pinMode(12, OUTPUT);
                        digitalWrite(12, HIGH);
                    }

                    /**
                     * Disable all automatic controls
                     */
                    void disableAutomaticControl() {
                        disableAutomaticExposureControl();
                        disableAutomaticGainControl();
                        disableAutomaticWhiteBalance();
                        disableAutomaticWhiteBalanceGain();
                        disableBPC();
                        // @todo this line breaks the capture
                        //disableDCW();
                        disableExposureControl();
                        disableGainControl();
                        disableLensCorrection();
                        disableRawGamma();
                        disableWPC();
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
                     * Configure sensor
                     */
                    virtual void configSensor() {

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
                        _sensor->set_framesize(_sensor, getFrameSize());
                        configSensor();

                        return true;
                    }

                    /**
                     *
                     */
                    bool concreteCapture() override {
                        free();

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