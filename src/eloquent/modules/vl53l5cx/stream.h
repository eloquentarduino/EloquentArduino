//
// Created by Simone on 13/04/2022.
//

#pragma once

#include "../vl53l5cx.h"


namespace Eloquent {
    namespace Modules {
        /**
         * Capture a stream of VL53L5CX frames
         * @tparam resolution
         * @tparam frames
         */
        template<uint8_t resolution, uint8_t frames>
        class VL53L5CXStream : public VL53L5CX {
        public:
            float features[resolution * frames];

            /**
             *
             */
            VL53L5CXStream() :
                VL53L5CX(resolution),
                _counter(0),
                _throttle(1) {
                memset(features, 0, getLength() * sizeof(float));
            }

            /**
             *
             * @return
             */
            uint16_t getLength() {
                return resolution * frames;
            }

            /**
             * Emit "queue" event once every n readings
             * @param throttle
             */
            void throttle(size_t throttle) {
                _throttle = throttle;
            }

            /**
             *
             * @param i
             * @return
             */
            float at(size_t i) {
                return features[i];
            }

            /**
             *
             * @param x
             * @param y
             * @param z
             * @return
             */
            float at(uint8_t x, uint8_t y, size_t z) {
                uint8_t width = sqrt(resolution);

                return at(z * resolution + y * width + x);
            }

            /**
             * Add frame to queue
             * @return
             */
            bool queue() {
                if (!read())
                    return false;

                shift();
                _counter += 1;

                for (uint16_t i = 0, j = resolution * (frames - 1); i < resolution; i++, j++) {
                    features[j] = VL53L5CX::at(i);
                }

                if (_counter < frames)
                    return false;

                if ((_counter % _throttle) != 1)
                    return false;

                return true;
            }

            /**
             * Print values to printer as single row
             * @tparam Printer
             * @param printer
             * @param delimiter
             * @param end
             */
            template<class Printer>
            void printTo(Printer &printer, char delimiter = ',', char end = '\n') {
                printer.print(at(0));

                for (uint16_t i = 1; i < resolution * frames; i++) {
                    printer.print(delimiter);
                    printer.print(at(i));
                }

                printer.print(end);
            }


        protected:
            size_t _counter;
            size_t _throttle;


            /**
             * Shift data to the left by one frame
             */
            void shift() {
                //memcpy(features, features + resolution, resolution * (frames - 1));

                for (uint16_t i = 0; i < getLength(); i++)
                    features[i] = features[i + resolution];
            }
        };
    }
}