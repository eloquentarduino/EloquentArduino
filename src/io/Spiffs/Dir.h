#pragma once

#include <SPIFFS.h>

namespace Eloquent {
    namespace Spiffs {
        /**
         * Abstract SPIFFS directory
         */
        class Dir {
        public:
            Dir(String dirname) :
                    _dirname(dirname) {

            }

            /**
             * Run function for each file in directory
             */
            void walk(void (*handler)(File)) {
                File dir = SPIFFS.open(_dirname);
                File file;

                while (file = dir.openNextFile()) {
                    handler(file);
                    file.close();
                }

                dir.close();
            }

        protected:
            String _dirname;
        };
    }
}