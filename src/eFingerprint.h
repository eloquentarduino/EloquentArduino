#pragma once

#include <Adafruit_Fingerprint.h>
#include "eUtils.h"

namespace Eloquent {

    /**
     * A wrapper around https://github.com/adafruit/Adafruit-Fingerprint-Sensor-Library
     */
    class Fingerprint {
    public:
        Fingerprint(HardwareSerial* serial) :
                _serial(serial),
                _finger(serial) {

        }

        /**
         *
         * @param baud
         */
        void begin(uint32_t baud = 57600) {
            _finger.begin(baud);
        }
        /**
         * Test if sensor is available
         * @return
         */
        bool available() {
            return _finger.verifyPassword();
        }

        /**
         *
         * @return
         */
        uint8_t count() {
            _finger.getTemplateCount();

            return _finger.templateCount;
        }

        /**
         * Read serial char
         * @return
         */
        uint8_t read() {
            return _serial->read();
        }

        /**
         *
         * @return
         */
        bool fingerAvailable() {
            return getImage();
        }

        /**
         * Get image
         * @return
         */
        bool getImage() {
            return _finger.getImage() == FINGERPRINT_OK;
        }

        /**
         *
         * @return
         */
        bool convert(uint8_t i) {
            return _finger.image2Tz(i) == FINGERPRINT_OK;
        }

        /**
         *
         * @param id
         * @return
         */
        bool getModel(uint8_t id) {
            return _finger.loadModel(id) == FINGERPRINT_OK && _finger.getModel() == FINGERPRINT_OK;
        }

        /**
         * Get fingerprint checksum
         * @param id
         * @param take
         * @param maxNumber
         * @return
         */
        uint16_t getModelChecksum(uint8_t id) {
            int i = 0;
            int checksum[4];

            if (!id || !getModel(id))
                return 0;

            // set a timeoute
            within(5 Seconds) {
                while (i < 534) {
                    if (_serial->available() && i++) {
                        uint8_t c = read();

                        // last 2 bytes of the 2 packets (267 bytes each) are the checksum
                        if (i == 265) checksum[0] = c;
                        else if (i == 266) checksum[1] = c;
                        else if (i == 265 + 267) checksum[2] = c;
                        else if (i == 266 + 267) checksum[3] = c;
                    }

                    check_within;
                }
            }

            return checksum[0] + 256 * checksum[1];
        }


        /**
         *
         * @param i
         * @param max
         * @return
         */
        uint32_t getModelChecksum2(uint8_t id, uint16_t take = 256, uint16_t maxNumber = UINT16_MAX) {
            int i = 0;
            int32_t checksum = 0;
            uint8_t bytesReceived[534]; // 2 data packets

            memset(bytesReceived, 0xff, 534);

            if (!getModel(id))
                return 0;

            within(5 Seconds) {
                while (i < 534) {
                    if (_serial->available()) {
                        bytesReceived[i++] = _serial->read();
                    }

                    check_within;
                }
            }

            // something is missing
            if (i != 534)
                return 0;

            uint8_t fingerTemplate[512]; // the real template
            memset(fingerTemplate, 0xff, 512);

            // filtering only the data packets
            int uindx = 9, index = 0;
            while (index < 534) {
                while (index < uindx) ++index;
                uindx += 256;
                while (index < uindx) {
                    fingerTemplate[index++] = bytesReceived[index];
                }
                uindx += 2;
                while (index < uindx) ++index;
                uindx = index + 9;
            }

            for (int i = 0; i < 512; i++)
                checksum = (checksum + (int32_t) fingerTemplate[i]) % 20;

            return checksum;
        }

        /**
         * Test if there's a finger
         * @param timeout
         * @return
         */
        bool awaitFinger(uint32_t timeout = 300) {
            for (uint32_t until = millis() + timeout; millis() < until; delay(10)) {
                if (getImage())
                    return true;
            }

            return false;
        }

        /**
         *
         */
        void awaitNoFinger() {
            while (_finger.getImage() != FINGERPRINT_NOFINGER)
                delay(10);
        }

        /**
         *
         * @return
         */
        uint8_t match(uint16_t minConfidence = 0) {
            getImage();

            if (!convert(1) || _finger.fingerFastSearch() != FINGERPRINT_OK)
                return 0;

            return _finger.confidence > minConfidence ? _finger.fingerID : 0;
        }

        /**
         * Create and store new model
         * @param id
         * @return
         */
        bool newModel(uint8_t id) {
            int response = _finger.createModel();

            if (response != FINGERPRINT_OK)
                return false;

            response = _finger.storeModel(id);

            return response == FINGERPRINT_OK;
        }

        /**
         * Make all the steps necessary to create a new model
         * @param id
         * @return
         */
        bool newModelProcedure(uint8_t id) {
            Serial.println("Put your finger on...");

            if (!awaitFinger(5000)) {
                Serial.println("No finger detected");
                return false;
            }

            if (!convert(1)) {
                Serial.println("Cannot convert");
                return false;
            }

            Serial.println("Remove finger...");
            delay(1000);
            awaitNoFinger();
            delay(1000);
            Serial.println("Put your finger on again...");

            if (!awaitFinger(5000)) {
                Serial.println("No finger detected");
                return false;
            }

            if (!convert(2)) {
                Serial.println("Cannot convert");
                return false;
            }

            Serial.println("Saving...");

            return newModel(id);
        }

    protected:
        Stream* _serial;
        Adafruit_Fingerprint _finger;
    };
}