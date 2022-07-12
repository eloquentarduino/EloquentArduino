//
// Created by Simone on 08/07/2022.
//

#pragma once
#include <esp_camera.h>


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            class Esp32CamSensorConfig {
            public:

                /**
                 * Constructor
                 * @param sensor
                 */
                Esp32CamSensorConfig(sensor_t *sensor = NULL) :
                    _sensor(sensor) {

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
                 * @param sensor
                 */
                void setSensor(sensor_t *sensor) {
                    _sensor = sensor;
                }

            protected:
                sensor_t *_sensor;
            };
        }
    }
}