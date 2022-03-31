#pragma once

#include <Stream.h>

namespace Eloquent {
    namespace ImageProcessing {

        /**
         *
         * @tparam width
         * @tparam height
         */
        template<size_t width, size_t height>
        class AsciiArt {
        public:
            AsciiArt(const uint8_t *data) {
                _data = data;
            }

            /**
             * Get pixel at given coordinates
             * @param x
             * @param y
             * @return
             */
            uint8_t at(size_t x, size_t y) {
                return _data[y * width + x];
            }

            /**
             * Print as ASCII art picture
             * @param stream
             */
            void print(Stream *stream, uint8_t frameSize = 0) {
                const char glyphs[] = " .,:;xyYX";
                const uint8_t glyphsCount = 9;

                printAsciiArtHorizontalFrame(stream, frameSize);

                for (size_t y = 0; y < height; y++) {
                    // vertical frame
                    for (uint8_t k = 0; k < frameSize; k++)
                        Serial.print('|');

                    for (size_t x = 0; x < width; x++) {
                        const uint8_t glyph = floor(((uint16_t) at(x, y)) * glyphsCount / 256);

                        stream->print(glyphs[glyph]);
                    }

                    // vertical frame
                    for (uint8_t k = 0; k < frameSize; k++)
                        Serial.print('|');

                    stream->print('\n');
                    stream->flush();
                }

                printAsciiArtHorizontalFrame(stream, frameSize);
            }

        protected:
            const uint8_t *_data;

            /**
             *
             * @param stream
             * @param frameSize
             */
            void printAsciiArtHorizontalFrame(Stream *stream, uint8_t frameSize) {
                for (uint8_t i = 0; i < frameSize; i++) {
                    for (size_t j = 0; j < width + 2 * frameSize; j++)
                        stream->print('-');
                    stream->print('\n');
                    stream->flush();
                }
            }
        };
    }
}