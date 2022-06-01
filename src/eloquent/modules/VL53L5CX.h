//
// Created by Simone on 13/04/2022.
//

#pragma once

#include <SparkFun_VL53L5CX_Library.h>
#include "../macros.h"
#include "../math.h"


namespace Eloquent {
    namespace Modules {
        /**
         * Eloquent interface to Vl53l5cx 8x8 Time of Flight sensor
         * @require SparkFun_Vl53l5cx_Library
         */
        class Vl53l5cx {
        public:
            float distances[64];


            /**
             * Constructor
             * @param resolution
             */
            Vl53l5cx(uint8_t resolution = 64) :
                _resolution(resolution),
                _ok(false),
                _ready(false),
                _frequency(10),
                _sleepDistance(0),
                _sleepDebounce(0),
                _sleepDebounceCounter(0),
                _sleepFails(0) {

                if (_resolution != 64 && _resolution != 16)
                    _resolution = 64;

                _config.truncateLowerThan = 0;
                _config.truncateHigherThan = 4000;
                _config.scaleMin = 0;
                _config.scaleMax = 0;
                _config.objectsThreshold = 0;
                _config.objectsCount = 0;
            }

            /**
             *
             * @return
             */
            bool isOk() {
                return _sensor.isConnected();
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
                _sensor.setWireMaxPacketSize(128);
                setFrequency(_resolution == 16 ? 60 : 15);
            }

            /**
             *
             * @param frequency
             */
            void setFrequency(uint8_t frequency) {
                _frequency = frequency;
            }

            /**
             * Truncate readings lower than given threshold
             * @param threshold
             */
            void truncateLowerThan(float threshold) {
                _config.truncateLowerThan = threshold;
            }

            /**
             * Truncate readings higher than given threshold
             * @param threshold
             */
            void truncateHigherThan(float threshold) {
                _config.truncateHigherThan = threshold;
            }

            /**
             * Scale input to given range
             * @param low
             * @param high
             */
            void scaleToRange(float low, float high) {
                _config.scaleMin = low;
                _config.scaleMax = high;
            }

            /**
             * Detect objects when at list minPixels have a value lower than threshold
             * @param threshold
             * @param minPixels
             */
            void detectObjectsWhenNearerThan(float threshold, uint8_t minPixels = 1)
            {
                _config.objectsThreshold = threshold;
                _config.objectsCount = minPixels;
            }

            /**
             * Init module
             * @param frequency
             * @return
             */
            bool begin() {
                if (!_sensor.begin())
                    return false;

                _sensor.setResolution(_resolution);
                _sensor.setRangingFrequency(_frequency);
                _sensor.startRanging();

                return (_ok = _sensor.isConnected());
            }

            /**
             * Test if sensor has new data
             * @return
             */
            bool hasNewData() {
                return _sensor.isDataReady();
            }

            /**
             * Read data from sensor
             * @return always true
             */
            bool read() {
                if (!_sensor.getRangingData(&_data))
                    return false;

                for (uint8_t i = 0; i < _resolution; i++) {
                    float distance = _data.distance_mm[i];

                    distance = eloquent::math::mapConstrain(
                        distance,
                        _config.truncateLowerThan,
                        _config.truncateHigherThan,
                        _config.scaleMin,
                        _config.scaleMax
                    );

                    distances[i] = distance;
                }

                return true;
            }

            /**
             * Test if the given number of pixels is within range
             * @return
             */
            bool hasObjectsNearby() {
                if (!_config.objectsCount || !_config.objectsThreshold)
                    return true;

                uint8_t passes = eloquent::math::arrayCountWhere(distances, _resolution, [this](float distance) {
                    return distance > 0 && distance < this->_config.objectsThreshold;
                });

                return passes >= _config.objectsCount;
            }

            /**
             * Get distance at given index
             * @param i
             * @return
             */
            float at(uint8_t i) {
                return distances[i];
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
             * Get mean value of distances
             * @return
             */
            float mean() {
                return eloquent::math::arrayMean(distances, _resolution);
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
            bool _ready;
            uint8_t _resolution;
            uint8_t _frequency;
            float _sleepDistance;
            uint16_t _sleepDebounce;
            uint16_t _sleepDebounceCounter;
            uint8_t _sleepFails;
            SparkFun_VL53L5CX _sensor;
            VL53L5CX_ResultsData _data;
            struct {
                float truncateLowerThan;
                float truncateHigherThan;
                float scaleMin;
                float scaleMax;
                float objectsThreshold;
                uint8_t objectsCount;
            } _config;
        };
    }
}