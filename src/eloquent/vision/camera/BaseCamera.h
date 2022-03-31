//
// Created by Simone on 29/03/2022.
//

#pragma once

#include "./Errors.h"


namespace Eloquent {
    namespace Vision {
        namespace Cam {
            /**
             * Abstract camera definition
             */
            class BaseCamera {
            public:

                /**
                 *
                 * @param force
                 * @return
                 */
                bool begin(bool force = false) {
                    if (_beginOk && !force)
                        return true;

                    if (!configure()) {
                        _beginOk = false;
                        setError(Error::INIT_ERROR);
                    }

                    _beginOk = true;

                    return isOk();
                }

                /**
                 * Test if everything is ok
                 * @return
                 */
                bool isOk() {
                    return _error == Error::OK;
                }

                /**
                 * Get error code
                 * @return
                 */
                Eloquent::Vision::Cam::Error getErrorCode() {
                    return _error;
                }

                /**
                 *
                 * @return
                 */
                String getErrorMessage() {
                    if (_error == Eloquent::Vision::Cam::Error::OK)
                        return "OK";

                    if (_error == Eloquent::Vision::Cam::Error::INIT_ERROR)
                        return "Init error";

                    if (_error == Eloquent::Vision::Cam::Error::CAPTURE_ERROR)
                        return "Capture error";

                    return "Generic error";
                }

                /**
                 *
                 * @return
                 */
                bool capture() {
                    if (!this->isOk())
                        return false;

                    if (!this->_beginOk)
                        this->begin();

                    if (!this->isOk())
                        return false;

                    return concreteCapture();
                }


            protected:
                bool _beginOk = false;
                Error _error = Error::OK;
                uint16_t _bufferLength;


                /**
                 * Capture frame to buffer
                 * @return
                 */
                virtual bool concreteCapture() = 0;

                /**
                 * Configure camera
                 * @return
                 */
                virtual bool configure() = 0;

                /**
                 *
                 * @param error
                 * @return
                 */
                bool setError(Error error) {
                    _error = error;

                    return isOk();
                }
            };
        }
    }
}