//
// Created by Simone on 23/03/2022.
//

#pragma once

#include <FS.h>
#include <SPIFFS.h>


namespace Eloquent {
    namespace FS {
        class SpiffsFile : public File {
        public:


            /**
             * @compatibility
             * @param filename
             * @param mode
             */
            static File open(String filename, const char *mode = "r") {
                return SPIFFS.open(filename, mode);
            }
        };
    }
}