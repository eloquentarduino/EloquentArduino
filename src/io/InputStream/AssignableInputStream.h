#pragma once

#include "InputStream.h"

namespace Eloquent {
    namespace InputStream {

        /**
         * Generate input stream when an assignment is made
         */
        class AssignableInputStream : public InputStream {
        public:
            AssignableInputStream() :
                    _isAssigned(false),
                    _assigned(0) {

            }

            /**
             *
             * @param value
             */
            void operator=(const float value) {
                _assigned = value;
                _isAssigned = true;

                read();
            }

        protected:
            bool _isAssigned;
            float _assigned;

            /**
             * A value is available once it has been assigned
             * @return
             */
            bool available() override {
                if (_isAssigned) {
                    _isAssigned = false;

                    return true;
                }

                return false;
            }

            /**
             * Get assigned value
             * @return
             */
            float _read() override {
                return _assigned;
            }
        };
    }
}