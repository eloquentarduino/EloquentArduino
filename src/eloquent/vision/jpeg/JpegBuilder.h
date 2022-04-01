//
// Created by Simone on 01/04/2022.
//

#pragma once

#include "./JpegEncoder.h"


namespace Eloquent {
    namespace Vision {
        namespace Jpeg {

            /**
             * Configure jpeg encoding
             */
            class JpegBuilder {
            public:

                /**
                 * Constructor
                 * @param buffer
                 * @param width
                 * @param height
                 * @param depth
                 * @param bytesPerPixel
                 */
                JpegBuilder(uint8_t *buffer, uint16_t width, uint16_t height, uint8_t depth, uint8_t bytesPerPixel) :
                    _buffer(buffer),
                    _width(width),
                    _height(height),
                    _depth(depth),
                    _bytesPerPixel(bytesPerPixel) {

                }

                /**
                 * Set best quality
                 * @return
                 */
                JpegBuilder& bestQuality() {
                    return setQuality(JPEG_Q_BEST);
                }

                /**
                 * Set high quality
                 * @return
                 */
                JpegBuilder& highQuality() {
                    return setQuality(JPEG_Q_HIGH);
                }

                /**
                 * Set low quality
                 * @return
                 */
                JpegBuilder& lowQuality() {
                    return setQuality(JPEG_Q_LOW);
                }

                /**
                 * Set quality
                 * @param quality
                 * @return
                 */
                JpegBuilder& setQuality(int quality) {
                    _quality = quality;

                    return *this;
                }

                /**
                 * Set grayscale
                 * @return
                 */
                JpegBuilder& grayscale() {
                    return setColor(JPEG_PIXEL_GRAYSCALE);
                }

                /**
                 * Set colorspace
                 * @param color
                 * @return
                 */
                JpegBuilder& setColor(int color) {
                    _color = color;

                    return *this;
                }

                /**
                 *
                 * @return
                 */
                bool isOk() {
                    return getSize() > 0 && _errorMessage.length() == 0;
                }

                /**
                 *
                 * @return
                 */
                String getErrorMessage() {
                    return _errorMessage;
                }

                /**
                 * Get size of encoded jpeg
                 * @return
                 */
                size_t getSize() {
                    return _size;
                }

                /**
                 * Get time to encode
                 * @return
                 */
                uint32_t getElapsedTime() {
                    return _elapsedTime;
                }

                /**
                 * Write to container
                 * @tparam Writer
                 * @param writer
                 * @return
                 */
                template<class Writer>
                size_t writeTo(Writer writer) {
                    JpegEncoder<Writer> jpeg(writer);

                    uint32_t startTime = micros();
                    _size = jpeg.write(_buffer, _width, _height, _depth, _bytesPerPixel, _color, _quality);
                    _elapsedTime = micros() - startTime;
                    _errorMessage = jpeg.getErrorMessage();

                    return getSize();
                }

            protected:
                uint8_t *_buffer;
                uint16_t _width;
                uint16_t _height;
                uint8_t _depth;
                uint8_t _bytesPerPixel;
                int _quality;
                int _color;
                size_t _size;
                uint32_t _elapsedTime;
                String _errorMessage;
            };
        }
    }
}