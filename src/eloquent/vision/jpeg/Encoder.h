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
             template<typename Stream>
            class Encoder {
            public:

                Encoder(Stream &stream) : _stream(&stream) {

                }

                /**
                 *
                 * @return
                 */
                bool isOk() {
                    return errorMessage.length() == 0;
                }

                /**
                 * Get size of encoded jpeg
                 * @return
                 */
                uint32_t getSize() {
                    return size;
                }

                /**
                 *
                 * @tparam Stream
                 * @param stream
                 * @param buffer
                 * @param width
                 * @param height
                 */
                bool write(uint8_t *buffer, uint16_t width, uint16_t height, uint8_t channels) {
                    JPEGENCODE jpe;
                    Eloquent::Dependencies::BitBank2::JpegEncoder<Stream> jpg(_stream);

                    errorMessage = "";
                    size = 0;

                    if (channels != 1)
                        return error("Only grayscale images are supported");

                    if (jpg.open() != JPEG_SUCCESS)
                        return error("Cannot init encoder");

                    if (jpg.encodeBegin(&jpe, width, height, JPEG_PIXEL_GRAYSCALE, JPEG_SUBSAMPLE_444, JPEG_Q_HIGH) != JPEG_SUCCESS)
                        return error("Cannot begin encoding");

                    int iMCUCount = ((width + jpe.cx-1)/ jpe.cx) * ((height + jpe.cy-1) / jpe.cy);
                    int rc = JPEG_SUCCESS;
                    const uint16_t xBlocks = width / 8;
                    const uint16_t yOffset = width * 8;

                    for (int i=0; i<iMCUCount && rc == JPEG_SUCCESS; i++) {
                        const uint16_t y = i / xBlocks;
                        const uint16_t x = i % xBlocks;

                        rc = jpg.addMCU(&jpe, buffer + y * yOffset + x * 8, width);
                    }

                    size = jpg.close();
                    _stream->close();
                }

            protected:
                Stream *_stream;
                uint32_t size;
                String errorMessage;

                /**
                 *
                 * @param message
                 * @return
                 */
                bool error(String message) {
                    errorMessage = message;

                    return false;
                }
            };
        }
    }
}