//
// Created by Simone on 04/03/2022.
//

#pragma once

#include "./CameraErrors.h"


namespace Eloquent {
    namespace Vision {
        namespace Camera {
            /**
             * Abstract interface for cameras
             */
            class AbstractCamera {
            public:
                /**
                 * Initialize camera
                 * @return
                 */
                virtual bool begin() = 0;

                /**
                 * Capture image and write to given container
                 * @tparam FrameContainer
                 * @param container
                 */
                //template<class FrameContainer>
                //virtual void captureTo(FrameContainer container) = 0;

                /**
                 * Test if camera is ok
                 * @return
                 */
                bool isOk() {
                    return _errorCode == Error::NO_ERROR;
                }

                /**
                 *
                 * @return
                 */
                Error getErrorCode() {
                    return _errorCode;
                }

                /**
                 *
                 * @return
                 */
                String getErrorMessage() {
                    if (_errorMessage.length() > 0)
                        return _errorMessage;

                    switch (_errorCode) {
                        case Error::INITALIZATION_ERROR:
                            return "Initialization error";
                        case Error::CAPTURE_ERROR:
                            return "Capture error";
                        default:
                            return "Unknown error";
                    }
                }

            protected:
                Error _errorCode;
                String _errorMessage;

                /**
                 * Set error code and optional message
                 *
                 * @param code
                 * @param message
                 * @return true if no error, false if error
                 */
                bool setError(Error code, String message = "") {
                    _errorCode = code;
                    _errorMessage = message;

                    return isOk();
                }
            };
        }
    }
}
