//
// Created by Simone on 05/07/2022.
//

#pragma once

#include <esp_camera.h>
#include "../../macros.h"
#include "./errors.h"
#include "./decoders/gray.h"
#include "./decoders/rgb565.h"
#include "./esp32_sensor_config.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            /**
             * Esp32 cam interface
             */
            class Esp32Cam {
            public:
                /**
                 * Image data buffer
                 */
                uint8_t *buffer;
                /**
                 * Sensor configurator
                 */
                 Esp32CamSensorConfig sensorConfig;


                /**
                 *
                 */
                Esp32Cam() :
                    sensorConfig(NULL),
                    _error(Error::OK),
                    _jpegQuality(20) {

                }

                /**
                 * Set QQVGA resolution
                 */
                void qqvga() {
                    _framesize = FRAMESIZE_QQVGA;
                }

                /**
                 * Set QVGA resolution
                 */
                void qvga() {
                    _framesize = FRAMESIZE_QVGA;
                }

                /**
                 * Set VGA resolution
                 */
                void vga() {
                    _framesize = FRAMESIZE_VGA;
                }

                /**
                 * Set grayscale pixel format
                 */
                void grayscale() {
                    _pixformat = PIXFORMAT_GRAYSCALE;
                }

                /**
                 * Set RGB888 pixel format
                 */
                void rgb888() {
                    _pixformat = PIXFORMAT_RGB888;
                }

                /**
                 * Set RGB565 pixel format
                 */
                void rgb565() {
                    _pixformat = PIXFORMAT_RGB565;
                }

                /**
                 * Set YUV422 pixel format
                 */
                void yuv422() {
                    _pixformat = PIXFORMAT_YUV422;
                }

                /**
                 * Set jpeg pixel format
                 * @param quality
                 */
                void jpeg(uint8_t quality = 10) {
                    _pixformat = PIXFORMAT_JPEG;
                    _jpegQuality = quality;
                }

                /**
                 * Set jpeg pixel format (low quality)
                 */
                void jpegLowQuality() {
                    jpeg(30);
                }

                /**
                 * Set jpeg pixel format (high quality)
                 */
                void jpegHighQuality() {
                    jpeg(10);
                }

                /**
                 * Set jpeg pixel format (best quality)
                 */
                void jpegBestQuality() {
                    jpeg(0);
                }

                /**
                 *
                 * @return
                 */
                bool begin() {
                    _config.ledc_channel = LEDC_CHANNEL_0;
                    _config.ledc_timer = LEDC_TIMER_0;
                    _config.fb_count = 1;
                    _config.pixel_format = _pixformat;
                    _config.frame_size = _framesize;

                    if (!_config.xclk_freq_hz)
                        _config.xclk_freq_hz = 20000000;

                    setPins();

                    if (esp_camera_init(&_config) != ESP_OK) {
                        return setError(Error::INIT_ERROR);
                    }

                    _sensor = esp_camera_sensor_get();
                    _sensor->set_framesize(_sensor, _framesize);
                    sensorConfig.setSensor(_sensor);

                    return true;
                }

                /**
                 * Capture new frame
                 */
                bool capture() {
                    free();

                    _fb = esp_camera_fb_get();

                    if (_fb == NULL || _fb->len == 0) {
                        return setError(Error::CAPTURE_ERROR);
                    }

                    buffer = _fb->buf;

                    return true;
                }

                /**
                 * Release frame memory
                 */
                void free() {
                    if (_fb != NULL)
                        esp_camera_fb_return(_fb);
                }

                /**
                 * Get width of captured image
                 * @return
                 */
                uint16_t getWidth() {
                    switch (_framesize) {
                        case FRAMESIZE_QQVGA:
                            return 160;
                        case FRAMESIZE_QVGA:
                            return 320;
                        case FRAMESIZE_VGA:
                            return 640;
                        default:
                            return 0;
                    }
                }

                /**
                 * Get height of captured image
                 * @return
                 */
                uint16_t getHeight() {
                    switch (_framesize) {
                        case FRAMESIZE_QQVGA:
                            return 120;
                        case FRAMESIZE_QVGA:
                            return 240;
                        case FRAMESIZE_VGA:
                            return 480;
                        default:
                            return 0;
                    }
                }

                /**
                 * Get number of channels
                 * @return
                 */
                uint8_t getDepth() {
                    switch (_pixformat) {
                        case PIXFORMAT_GRAYSCALE:
                            return 1;
                        case PIXFORMAT_RGB565:
                        case PIXFORMAT_RGB888:
                        case PIXFORMAT_YUV422:
                        case PIXFORMAT_JPEG:
                            return 3;
                        default:
                            return 0;
                    }
                }

                /**
                 * Get number of bytes for each pixl
                 * @return
                 */
                uint8_t getBytesPerPixel() {
                    switch (_pixformat) {
                        case PIXFORMAT_GRAYSCALE:
                            return 1;
                        case PIXFORMAT_RGB565:
                            return 2;
                        case PIXFORMAT_RGB888:
                            return 3;
                        case PIXFORMAT_YUV422:
                            return 4;
                        default:
                            return 0;
                    }
                }

                /**
                 * Get current error message
                 * @return
                 */
                String getErrorMessage() {
                    switch (_error) {
                        case Error::OK:
                            return "";
                        case Error::INIT_ERROR:
                            return "Init error";
                        case Error::CAPTURE_ERROR:
                            return "Capture error";
                        default:
                            return "Unknown error";
                    }
                }

                /**
                 * Print to printer
                 * @tparam Printer
                 * @param printer
                 * @param separator
                 */
                template<class Printer>
                void printTo(Printer& printer, char separator = ',') {
                    if (_fb == NULL || _fb->len == 0)
                        return;

                    printer.print(_fb->buf[0]);

                    for (size_t i = 1; i < _fb->len; i++) {
                        printer.print(separator);
                        printer.print(_fb->buf[i]);
                    }
                }

                /**
                 * Print to printer
                 * @tparam Printer
                 * @param printer
                 * @param width
                 * @param height
                 * @param separator
                 */
                template<class Printer>
                void printResizedTo(Printer& printer, uint16_t width, uint16_t height, char separator = ',') {
                    if (_fb == NULL || _fb->len == 0)
                        return;

                    const uint8_t bpp = getBytesPerPixel();
                    const float dy = getHeight() / height;
                    const float dx = getWidth() / width;

                    for (uint16_t y = 0; y < height; y++) {
                        const size_t rowOffset = dy * y * getWidth() * bpp;

                        for (uint16_t x = 0; x < width; x++) {
                            const size_t offset = rowOffset + dx * x * bpp;

                            for (uint8_t z = 0; z < bpp; z++) {
                                printer.print(_fb->buf[offset + z]);

                                if (y != height - 1 || x != width - 1 || z != bpp - 1)
                                    printer.print(separator);
                            }
                        }
                    }

                    printer.print('\n');
                }

            protected:
                Error _error;
                framesize_t _framesize;
                pixformat_t _pixformat;
                uint8_t _jpegQuality;
                camera_config_t _config;
                sensor_t *_sensor;
                camera_fb_t *_fb;

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
                 * Set camera error
                 * @param error
                 * @return
                 */
                bool setError(Error error) {
                    return (_error = error) == Error::OK;
                }
            };
        }
    }
}

ELOQUENT_SINGLETON(Eloquent::Vision::Cam::Esp32Cam camera);