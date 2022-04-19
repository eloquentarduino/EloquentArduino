//
// Created by Simone on 13/04/2022.
//

#pragma once

#include <SparkFun_VL53L5CX_Library.h>
#include "../macros.h"


namespace Eloquent {
    namespace Modules {
        /**
         * Eloquent interface to VL53L5CX 8x8 Time of Flight sensor
         * @require SparkFun_VL53L5CX_Library
         */
        class VL53L5CX {
        public:

            /**
             * Constructor
             * @param resolution
             */
            VL53L5CX(uint8_t resolution = 64) :
                _resolution(resolution),
                _ok(false),
                _maxDistance(0),
                _rangeMin(0),
                _rangeMax(0) {

                if (_resolution != 64 && _resolution != 16)
                    _resolution = 64;
            }

            /**
             *
             * @return
             */
            bool isOk() {
                return _ok;
            }

            /**
             * Test for new data available
             * @return
             */
            bool available() {
                if (!isOk())
                    begin();

                return isOk() && _sensor.isDataReady();
            }

            /**
             * Configure settings for high speed communication
             * @param frequency
             */
            void highFreq() {
                Wire.setClock(400000);
                _sensor.setWireMaxPacketSize(128);
            }

            /**
             * Set max distance
             * Distances above this will be truncated
             * @param maxDistance
             */
            void truncateAt(float maxDistance) {
                _maxDistance = maxDistance;
            }

            /**
             * Scale input to given range
             * @param low
             * @param high
             */
            void scale(float low, float high) {
                _rangeMin = low;
                _rangeMax = high;
            }

            /**
             * Init module
             * @param frequency
             * @return
             */
            bool begin(uint8_t frequency = 10) {
                if (!_sensor.begin())
                    return false;

                _sensor.setResolution(_resolution);
                _sensor.setRangingFrequency(frequency);
                _sensor.startRanging();

                return (_ok = true);
            }

            /**
             * Read data
             */
            bool read() {
                if (!isOk())
                    begin();

                if (!isOk())
                    return false;

                if (!available())
                    return false;

                _sensor.getRangingData(&_data);

                return true;
            }

            /**
             * Get distance at given index
             * @param i
             * @return
             */
            float at(uint8_t i) {
                if (!isOk())
                    return 0;

                float d = _data.distance_mm[i];

                if (_maxDistance > 0 && d > _maxDistance)
                    d = _maxDistance;

                if (_maxDistance > 0 && _rangeMin != _rangeMax)
                    d = (d / _maxDistance) * (_rangeMax - _rangeMin) + _rangeMin;

                return d;
            }

            /**
             * Get distance at given coordinates
             * @param x
             * @param y
             * @return
             */
            float at(uint8_t x, uint8_t y) {
                const uint8_t width = sqrt(_resolution);

                return at(y * width + x);
            }

            /**
             * Print values to printer as single row
             * @tparam Printer
             * @param printer
             * @param delimiter
             */
            template<class Printer>
            void printTo(Printer &printer, char delimiter = ',', char end = '\n') {
                printer.print(at(0));

                for (uint8_t i = 1; i < _resolution; i++) {
                    printer.print(delimiter);
                    printer.print(at(i));
                }

                printer.print(end);
            }

            /**
             * Print values to printer as matrix
             * @tparam Printer
             * @param printer
             * @param delimiter
             * @param newline
             * @param end
             */
            template<class Printer>
            void printAsMatrixTo(Printer &printer, char delimiter = ',', char newline = '\n', char end = '\n') {
                uint8_t width = sqrt(_resolution);

                for (uint8_t y = 0; y < width; y++) {
                    printer.print(at(y, 0));

                    for (uint8_t x = 1; x < width; x++) {
                        printer.print(delimiter);
                        printer.print(at(x, y));
                    }

                    printer.print(y == width - 1 ? end : newline);
                }
            }

        protected:
            bool _ok;
            uint8_t _resolution;
            float _maxDistance;
            float _rangeMin;
            float _rangeMax;
            SparkFun_VL53L5CX _sensor;
            VL53L5CX_ResultsData _data;
        };
    }
}

ELOQUENT_SINGLETON(Eloquent::Modules::VL53L5CX tof8x8(64));
ELOQUENT_SINGLETON(Eloquent::Modules::VL53L5CX tof4x4(16));