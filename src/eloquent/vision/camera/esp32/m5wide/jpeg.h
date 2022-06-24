//
// Created by Simone on 24/06/2022.
//

#pragma once

#include "../../../../macros.h"
#include "./m5wide.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            namespace Esp32 {
                /**
                 * M5 wide
                 * Grayscale
                 * QQVGA
                 */
                class BaseJpegCamera : public M5WideCamera {
                public:

                    /**
                     *
                     * @return
                     */
                    virtual framesize_t getFrameSize() = 0;

                    /**
                     *
                     * @return
                     */
                    pixformat_t getPixFormat() {
                        return PIXFORMAT_JPEG;
                    }

                    /**
                     *
                     * @param buffer
                     */
                    void setFrameBuffer(uint8_t *buffer) {
                        // do nothing
                    }

                    /**
                     * Set jpeg quality
                     * @param quality
                     */
                    void setQuality(uint8_t quality) {
                        _quality = quality;
                    }

                protected:
                    uint8_t _quality = 30;

                    /**
                     *
                     */
                    void setConfig() {
                        setHighFreq();
                        _config.jpeg_quality = _quality;
                    }
                };

                /**
                 * QQVGA jpeg camera
                 */
                class QqvgaJpegCamera : public BaseJpegCamera {
                public:
                    framesize_t getFrameSize() {
                        return FRAMESIZE_QQVGA;
                    }
                };

                /**
                 * QVGA jpeg camera
                 */
                class QvgaJpegCamera : public BaseJpegCamera {
                public:
                    framesize_t getFrameSize() {
                        return FRAMESIZE_QVGA;
                    }
                };

                /**
                 * VGA jpeg camera
                 */
                class VgaJpegCamera : public BaseJpegCamera {
                public:
                    framesize_t getFrameSize() {
                        return FRAMESIZE_VGA;
                    }
                };
            }
        }
    }
}

