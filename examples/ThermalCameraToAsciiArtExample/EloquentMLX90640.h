#pragma once

#include <Wire.h>
#include <MLX90640_API.h>
#include <MLX90640_I2C_Driver.h>

#ifndef TA_SHIFT
//Default shift for MLX90640 in open air
#define TA_SHIFT 8
#endif

namespace Eloquent {
    namespace Sensors {

        enum class MLX90640Status {
            OK,
            NOT_CONNECTED,
            DUMP_ERROR,
            PARAMETER_ERROR,
            FRAME_ERROR
        };

        class MLX90640 {
        public:
            /**
             *
             * @param address
             */
            MLX90640(uint8_t address = 0x33) :
                _address(address),
                _status(MLX90640Status::OK) {

            }

            /**
             *
             * @return
             */
            bool begin() {
                Wire.begin();
                Wire.setClock(400000);

                return isConnected() && loadParams();
            }

            /**
             *
             * @return
             */
            bool read(float result[768]) {
                for (byte x = 0 ; x < 2 ; x++) {
                    uint16_t frame[834];
                    int status = MLX90640_GetFrameData(_address, frame);
                    
                    if (status < 0)
                        return fail(MLX90640Status::FRAME_ERROR);

                    float vdd = MLX90640_GetVdd(frame, &_params);
                    float Ta = MLX90640_GetTa(frame, &_params);
                    float tr = Ta - TA_SHIFT;
                    float emissivity = 0.95;

                    MLX90640_CalculateTo(frame, &_params, emissivity, tr, result);
                }
            }

        protected:
            uint8_t _address;
            paramsMLX90640 _params;
            MLX90640Status _status;

            /**
             * Test if device is connected
             * @return
             */
            bool isConnected() {
                Wire.beginTransmission(_address);

                if (Wire.endTransmission() == 0) {
                    return true;
                }

                return fail(MLX90640Status::NOT_CONNECTED);
            }

            /**
             *
             * @return
             */
            bool loadParams() {
                uint16_t ee[832];
                int status = MLX90640_DumpEE(_address, ee);

                if (status != 0)
                    return fail(MLX90640Status::DUMP_ERROR);

                status = MLX90640_ExtractParameters(ee, &_params);

                if (status != 0)
                    return fail(MLX90640Status::PARAMETER_ERROR);

                return true;
            }

            /**
             * Mark a failure
             * @param status
             * @return
             */
            bool fail(MLX90640Status status) {
                _status = status;

                return false;
            }
        };
    }
}