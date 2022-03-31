#pragma once


namespace Eloquent {
    namespace Vision {
        namespace IO {
            namespace Writers {

                /**
                 * Write jpeg image to disk
                 */
                template<uint16_t width, uint16_t height>
                class JpegWriter {
                public:

                    /**
                     * Write grayscale image
                     * @tparam TFile File class
                     * @param file
                     * @param image
                     * @return jpeg size
                     */
                    template<class TFile>
                    size_t writeGrayscale(TFile &file, uint8_t *image, uint8_t quality = 30) {
                        return write(file, image, PIXFORMAT_GRAYSCALE, quality);
                    }

                    /**
                     * Write RGB565 image
                     * @tparam TFile File class
                     * @param file
                     * @param image
                     * @return jpeg size
                     */
                    template<class TFile>
                    size_t writeRGB565(TFile &file, uint8_t *image, uint8_t quality = 30) {
                        return write(file, image, PIXFORMAT_RGB565, quality);
                    }

                    /**
                     * Write JPEG image to file
                     * @tparam TFile
                     * @param file
                     * @param image
                     * @param pixformat
                     * @param quality
                     * @return jpeg size
                     */
                    template<class TFile>
                    size_t write(TFile &file, uint8_t *image, pixformat_t pixformat, uint8_t quality = 30) {
                        uint8_t *jpeg;
                        size_t len;

                        if (fmt2jpg(image, width * height, width, height, pixformat, quality, &jpeg, &len)) {
                            file.write(jpeg, len);

                            return len;
                        }

                        return 0;
                    }

                };
            }
        }
    }
}