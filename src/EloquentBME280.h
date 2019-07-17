#pragma once

#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include "EloquentSensor.h"
#include "EloquentReadsMultipleNumericValues.h"
#include "eSerialLog.h"

namespace Eloquent {

    namespace BME280_Readings {
        enum {
            TEMPERATURE,
            HUMIDITY,
            PRESSURE
        };
    }

    typedef struct {
        uint8_t address;
        uint8_t cs;
        uint8_t miso;
        uint8_t mosi;
        uint8_t sck;
    } BME280Config;

    class BME280 : public Sensor, public ReadsMultipleNumericValues {

    public:
        /**
         * Default constructor
         */
        BME280() {

        }

        /**
         * Constructor with configs
         * @param config
         */
        BME280(BME280Config config) :
            _config(config) {

        }

        /**
         *
         * @return
         */
        const char * getName() {
            return "BME280";
        }

        /**
         *
         * @return
         */
        bool begin() {
            // I2C address given
            if (_config.address) {
                return _bme.begin(_config.address);
            }
            // SPI (full)
            else if (_config.cs && _config.miso && _config.mosi && _config.sck) {
                _bme = Adafruit_BME280(_config.cs, _config.mosi, _config.miso, _config.sck);
            }
            // SPI (CS only)
            else if (_config.cs) {
                _bme = Adafruit_BME280(_config.cs);
            }

            // default to I2C with default address
            return _bme.begin();
        }

        /**
         *
         * @return
         */
        uint8_t numReadings() {
            return 3;
        }

        /**
         *
         * @return
         */
        float readValue() {
            return ReadsMultipleNumericValues::readValue();
        }

        /**
         *
         * @param index
         * @return
         */
        float readValueAt(uint8_t index) {
            switch (index) {
                case BME280_Readings::TEMPERATURE:
                    return _bme.readTemperature();
                case BME280_Readings::HUMIDITY:
                    return _bme.readHumidity();
                case BME280_Readings::PRESSURE:
                    return _bme.readPressure();
                default:
                    log_error("Invalid index");
                    var_dump("index", index);
                    return 0;
            }
        }

        /**
         *
         * @return
         */
        float readTemperature() {
            return readValueAt(BME280_Readings::TEMPERATURE);
        }

        /**
         *
         * @return
         */
        float readHumidity() {
            return readValueAt(BME280_Readings::HUMIDITY);
        }

        /**
         *
         * @return
         */
        float readPressure() {
            return readValueAt(BME280_Readings::PRESSURE);
        }


    protected:
        Adafruit_BME280 _bme;
        BME280Config _config;
    };
}