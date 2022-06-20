//
// Created by Simone on 30/03/2022.
//

#pragma once

#include "../../io/json/JsonEncoder.h"


namespace Eloquent {
    namespace Vision {
        namespace Image {
            /**
             * Base image interface
             * @tparam width 
             * @tparam height 
             * @tparam depth 
             * @tparam bytesPerPixel 
             */
            template<uint16_t width, uint16_t height, uint8_t depth, uint8_t bytesPerPixel>
            class BaseImage {
            public:
                /**
                 * Raw data
                 */
                uint8_t *buffer;
                
                /**
                 * Constructor
                 */
                BaseImage(uint8_t *buf = NULL) :
                    _width(width),
                    _height(height),
                    _depth(depth),
                    _bytesPerPixel(bytesPerPixel),
                    _copyOnWrite(false),
                    buffer(buf) {
                    
                }
                
                /**
                 *
                 * @return
                 */
                uint16_t getWidth() {
                    return _width;
                }

                /**
                 *
                 * @return
                 */
                uint16_t getHeight() {
                    return _height;
                }

                /**
                 *
                 * @return
                 */
                uint8_t getDepth() {
                    return _depth;
                }

                /**
                 *
                 * @return
                 */
                uint8_t getBytesPerPixel() {
                    return _bytesPerPixel;
                }

                /**
                 *
                 * @return
                 */
                uint16_t getLength() {
                    return getWidth() * getHeight() * getBytesPerPixel();
                }

                /**
                 * Update width
                 * @param newWidth
                 */
                void setWidth(uint16_t newWidth) {
                    _width = newWidth;
                }

                /**
                 * Update height
                 * @param newHeight
                 */
                void setHeight(uint16_t newHeight) {
                    _height = newHeight;
                }

                /**
                 * Update depth
                 * @param newDepth
                 */
                void setDepth(uint8_t newDepth) {
                    _depth = newDepth;
                }

                /**
                 * Set bytes per pixel
                 * @param newBytesPerPixel
                 */
                void setBytesPerPixel(uint8_t newBytesPerPixel) {
                    _bytesPerPixel = newBytesPerPixel;
                }

                /**
                 * Get pixel at (x, y)
                 * @param x
                 * @param y
                 */
                uint8_t at(uint16_t x, uint16_t y) {
                    return at(x, y, 0);
                }

                /**
                 * Get pixel at (x, y, z)
                 * @param x
                 * @param y
                 * @param z
                 */
                uint8_t at(uint16_t x, uint16_t y, uint8_t z) {
                    return at(y * getWidth() * getBytesPerPixel() + x * getBytesPerPixel() + z);
                }

                /**
                 * Get pixel value at given index
                 * @param i
                 * @return
                 */
                uint8_t at(uint16_t i) {
                    if (i > getLength())
                        return 0;

                    return buffer[i];
                }

                /**
                 * Set pixel at (x, y)
                 * @param x
                 * @param y
                 * @param value
                 */
                uint8_t set(uint16_t x, uint16_t y, uint8_t value) {
                    return at(x, y, 0, value);
                }

                /**
                 * Set pixel at (x, y, z)
                 * @param x
                 * @param y
                 * @param z
                 */
                uint8_t set(uint16_t x, uint16_t y, uint8_t z, uint8_t value) {
                    return set(y * getWidth() * getBytesPerPixel() + x * getBytesPerPixel() + z, value);
                }

                /**
                 * Set pixel value at given index
                 * @param i
                 * @param value
                 * @return
                 */
                uint8_t set(uint16_t i, uint8_t value) {
                    if (i > getLength())
                        return 0;

                    return (buffer[i] = value);
                }

                /**
                 * Set new buffer and restore to original size
                 *
                 * @param buffer
                 */
                void refresh(uint8_t *buffer) {
                    this->buffer = buffer;
                    this->restoreToOriginalSize();
                }

                /**
                 * Restore sizes to their original values
                 */
                void restoreToOriginalSize() {
                    setWidth(width);
                    setHeight(height);
                    setDepth(depth);
                    setBytesPerPixel(bytesPerPixel);
                }

                /**
                 * If true, will copy the buffer when writing the image
                 * @param copy
                 */
                void copyOnWrite(bool copy) {
                    _copyOnWrite = copy;
                }

                /**
                 * Write raw data to image container
                 * @param buffer
                 * @param length how many bytes to write
                 * @return
                 */
                size_t write(uint8_t *buffer, size_t length = 0) {
                    if (length == 0)
                        length = getLength();

                    if (_copyOnWrite && this->buffer != NULL)
                        memcpy(this->buffer, buffer, length);
                    else
                        this->buffer = buffer;

                    return length;
                }

                /**
                 *
                 * @tparam Writer
                 * @param writer
                 * @return
                 */
                template<typename Writer>
                size_t writeTo(Writer writer) {
                    return writer.write(buffer, getLength());
                }
                
                /**
                 * Print as json
                 * @tparam Printer
                 * @param printer
                 * @param string
                 * @param char
                 */
                template<class Printer>
                void printAsJsonTo(Printer &printer) {
                    Eloquent::IO::Json::JsonEncoder<Printer> jsonEncoder(printer);

                    jsonEncoder.openObject();
                    jsonEncoder.encode("width", getWidth());
                    jsonEncoder.then();
                    jsonEncoder.encode("height", getHeight());
                    jsonEncoder.then();
                    jsonEncoder.encode("depth", getDepth());
                    jsonEncoder.then();
                    jsonEncoder.encode("bpp", getBytesPerPixel());
                    jsonEncoder.then();
                    jsonEncoder.encode("length", getLength());
                    jsonEncoder.then();
                    jsonEncoder.encode("data", buffer, getLength());
                    jsonEncoder.closeObject();
                }

                /**
                 * Save as jpeg
                 * @tparam Writer
                 * @param writer
                 */
//                template<class Writer>
//                void writeAsJpegTo(Writer writer) {
//                    Eloquent::Vision::Jpeg::Encoder<Writer> jpeg(writer);
//
//                    jpeg.write(buffer, getLength());
//                }

            protected:
                uint16_t _width;
                uint16_t _height;
                uint8_t _depth;
                uint8_t _bytesPerPixel;
                bool _copyOnWrite;
            };
        }
    }
}
