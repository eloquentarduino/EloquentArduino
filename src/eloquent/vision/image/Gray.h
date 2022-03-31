//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "../transform/gray/BaseTransform.h"
#include "../transform/gray/NearestResize.h"
#include "../transform/gray/BilinearResize.h"
#include "../../io/json/JsonEncoder.h"


namespace Eloquent {
    namespace Vision {
        namespace Image {

            /**
             * Manipulate grayscale image matrix
             *
             * @tparam width
             * @tparam height
             */
            template<uint16_t sourceWidth, uint16_t sourceHeight>
            class GrayImage {
            public:
                uint8_t *_buffer;


                /**
                 * Constructor
                 */
                GrayImage() :
                        _width(sourceWidth),
                        _height(sourceHeight) {

                }

                /**
                 * Constructor
                 */
                GrayImage(uint8_t *buffer) :
                        _buffer(buffer),
                        _width(sourceWidth),
                        _height(sourceHeight) {

                }

                /**
                 *
                 * @return
                 */
                uint8_t *getBuffer() {
                    return _buffer;
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
                size_t getLength() {
                    return getWidth() * getHeight();
                }

                void setWidth(uint16_t width) {
                    _width = width;
                }

                void setHeight(uint16_t height) {
                    _height = height;
                }

                /**
                 * Get pixel value at given position
                 *
                 * @param i
                 * @return
                 */
                uint8_t at(uint16_t i) {
                    if (i > getLength())
                        return 0;

                    return _buffer[i];
                }

                /**
                 * Check if buffer is valid
                 * @return
                 */
                bool isOk() {
                    return _buffer != 0;
                }

                /**
                 * Update buffer data
                 *
                 * @param buffer
                 * @param length
                 */
                void write(uint8_t *buffer, size_t length) {
                    _buffer = buffer;
                    _width = sourceWidth;
                    _height = sourceHeight;
                }

                /**
                 * Resize to new dimensions
                 * @param newWidth
                 * @param newHeight
                 */
                template<uint16_t newWidth, uint16_t newHeight>
                void resize() {
                    Transform::NearestResize<sourceWidth, sourceHeight, newWidth, newHeight> resize;

                    transform(resize);
                }

                /**
                 * Resize to new dimensions
                 * @param newWidth
                 * @param newHeight
                 */
                template<uint16_t newWidth, uint16_t newHeight, typename Target>
                void resize(Target &target) {
                    Transform::NearestResize<sourceWidth, sourceHeight, newWidth, newHeight> resize;

                    transform(resize, target);
                }

                /**
                 * Resize to new dimensions using bilinear interpolation
                 * @param newWidth
                 * @param newHeight
                 */
                template<uint16_t newWidth, uint16_t newHeight>
                void resizeBilinear() {
                    Transform::BilinearResize<sourceWidth, sourceHeight, newWidth, newHeight> resize;

                    transform(resize);
                }

                /**
                 * Apply transformation
                 * @param transform
                 */
                void transform(Transform::Transform &transform) {
                    transform.apply(_buffer, &_width, &_height);
                }

                /**
                 * Apply transformation
                 * @param transform
                 */
                template<typename Target>
                void transform(Transform::Transform &transform, Target &target) {
                    uint16_t width = _width;
                    uint16_t height = _height;

                    transform.apply(_buffer, target._buffer, &width, &height);

                    target.setWidth(width);
                    target.setHeight(height);
                }

                /**
                 * Write buffer to stream
                 * @tparam Stream
                 * @param stream
                 */
                template<class Stream>
                void writeRaw(Stream &stream) {
                    stream.write(_buffer, getLength());
                }

                /**
                 * Write buffer to stream
                 * @tparam Stream
                 * @param stream
                 */
                template<typename Stream>
                void writeTo(Stream &stream) {
                    stream.write(_buffer, getWidth(), getHeight(), 1);
                }

                /**
                 * Print as json
                 * @tparam Stream
                 * @param stream
                 * @param string
                 * @param char
                 */
                template<class Stream>
                void printAsJson(Stream &stream) {
                    Eloquent::IO::Json::JsonEncoder<Stream> jsonEncoder(stream);

                    jsonEncoder.openObject();
                    jsonEncoder.encode("width", getWidth());
                    jsonEncoder.then();
                    jsonEncoder.encode("height", getHeight());
                    jsonEncoder.then();
                    jsonEncoder.encode("channels", 1);
                    jsonEncoder.then();
                    jsonEncoder.encode("data", _buffer, getLength());
                    jsonEncoder.closeObject();
                }

            protected:
                uint16_t _width;
                uint16_t _height;
            };


            /**
             * Syntactic sugar
             */
            namespace Gray {
                class QVGA : public GrayImage<320, 240> {

                };
            }
        }
    }
}