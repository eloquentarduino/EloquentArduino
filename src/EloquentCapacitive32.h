#pragma once

#include "EloquentSensor.h"


namespace Eloquent {

    class Capacitive32 : public Sensor {
    public:

        /**
         *
         * @param pin
         */
        Capacitive32(uint8_t pin) {
            _pin = pin;
        }

        /**
         *
         * @return
         */
        const char * getName() {
            return "Touch sensor";
        }

        /**
         *
         * @return
         */
        bool begin() {
            return true;
        }

        /**
         *
         * @return
         */
        float readValue() {
            return touchRead(_pin);
        }

        /**
         *
         * @param sensitiveness
         */
        void setSensitiveness(uint16_t sensitiveness) {
            touchSetCycles(sensitiveness, sensitiveness);
        }

    protected:
        uint8_t _pin;
    };
}