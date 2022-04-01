//
// Created by Simone on 24/03/2022.
//

#pragma once

#include "./bitbank2/BitBankJpegEncoder.h"



namespace Eloquent {
    namespace Vision {
        namespace Jpeg {
            /**
             * Jpeg encoding
             */
            template<typename Writer>
            class JpegEncoder {
            public:
                /**
                 * Constructor
                 * @param writer
                 */
                JpegEncoder(Writer &writer) : _writer(&writer) {

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
                 *
                 * @tparam Writer
                 * @param writer
                 * @param buffer
                 * @param width
                 * @param height
                 * @param depth
                 * @param bytesPerPixel
                 * @param color
                 * @param quality
                 * @return jpeg size
                 */
                size_t write(uint8_t *buffer, uint16_t width, uint16_t height, uint8_t depth, uint8_t bytesPerPixel, int color, int quality) {
                    JPEGENCODE jpe;
                    Eloquent::Dependencies::BitBank2::JpegEncoder<Writer> jpg(_writer);

                    _errorMessage = "";
                    _size = 0;

                    if (depth != 1)
                        return error("Only grayscale images are supported");

                    if (jpg.open() != JPEG_SUCCESS)
                        return error("Cannot init encoder");

                    if (jpg.encodeBegin(&jpe, width, height, color, JPEG_SUBSAMPLE_444, quality) != JPEG_SUCCESS)
                        return error("Cannot begin encoding");

                    int mcuCount = ((width + jpe.cx-1) / jpe.cx) * ((height + jpe.cy-1) / jpe.cy);
                    int rc = JPEG_SUCCESS;
                    const uint16_t xBlocks = width / 8;
                    const uint16_t yOffset = width * 8;

                    for (int i=0; i < mcuCount && rc == JPEG_SUCCESS; i++) {
                        const uint16_t y = i / xBlocks;
                        const uint16_t x = i % xBlocks;

                        rc = jpg.addMCU(&jpe, buffer + y * yOffset + x * 8, width);
                    }

                    _size = jpg.close();
                    _writer->close();

                    return getSize();
                }

            protected:
                Writer *_writer;
                size_t _size;
                String _errorMessage;

                /**
                 *
                 * @param message
                 * @return
                 */
                bool error(String message) {
                    _errorMessage = message;

                    return false;
                }
            };
        }
    }
}