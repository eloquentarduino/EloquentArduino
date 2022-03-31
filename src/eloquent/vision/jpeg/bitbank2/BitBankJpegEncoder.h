#pragma once

#include "./definitions.h"
#include "./jpeg.inl"


/**
 *
 */
namespace Eloquent {
    namespace Dependencies {
        namespace BitBank2 {
            template<typename Stream>
            class JpegEncoder {
            public:
                JpegEncoder(Stream *stream) :
                _stream(stream) {

                }

                int open() {
                    memset(&_jpeg, 0, sizeof(JPEGIMAGE));
                    _jpeg.pHighWater = &_jpeg.ucFileBuf[JPEG_FILE_BUF_SIZE - 512];

                    return JPEG_SUCCESS;
                }

                int close() {
                    JPEGEncodeEnd(_stream, &_jpeg);
                }

                int encodeBegin(JPEGENCODE *pEncode, int iWidth, int iHeight, uint8_t ucPixelType, uint8_t ucSubSample, uint8_t ucQFactor) {
                    return JPEGEncodeBegin(&_jpeg, pEncode, iWidth, iHeight, ucPixelType, ucSubSample, ucQFactor);
                }

                int addMCU(JPEGENCODE *pEncode, uint8_t *pPixels, int iPitch) {
                    return JPEGAddMCU<Stream>(_stream, &_jpeg, pEncode, pPixels, iPitch);
                }

                int getLastError() {
                    return _jpeg.iError;
                }

            protected:
                Stream *_stream;
                JPEGIMAGE _jpeg;
            };
        }
    }
}
