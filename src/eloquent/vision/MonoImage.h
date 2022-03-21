//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./transform/Transform.h"
#include "./transform/NearestResize.h"
#include "../io/json/JsonEncoder.h"


namespace Eloquent {
    namespace Vision {
        /**
         * Manipulate image matrices
         *
         * @tparam width
         * @tparam height
         */
        template<uint16_t sourceWidth, uint16_t sourceHeight>
        class MonoImage {
        public:

            /**
             * Constructor
             */
            MonoImage() :
                _width(sourceWidth),
                _height(sourceHeight) {

            }

            /**
             *
             * @return
             */
            uint8_t* getBuffer() {
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
            }

            /**
             * Resize to new dimensions
             * @param newWidth
             * @param newHeight
             */
            void resizeTo(uint16_t newWidth, uint16_t newHeight) {
                Transform::NearestResize<sourceWidth, sourceHeight> resize(newWidth, newHeight);

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
             * Write buffer to stream
             * @tparam Stream
             * @param stream
             */
            template<class Stream>
            void writeTo(Stream &stream) {
                stream.write(_buffer, getLength());
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
            uint8_t *_buffer;
        };

        /**
         * Syntactic sugar
         */
        class MonoImageQVGA : public MonoImage<320, 240> {

        };
    }
}