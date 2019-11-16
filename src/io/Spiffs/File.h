#pragma once

#include <Stream.h>
#include <SPIFFS.h>

namespace Eloquent {
    namespace Spiffs {
        /**
         * Abstract SPIFFS file
         */
        class SpiffsFile {
         public:
            SpiffsFile(String filename) :
                _filename(filename) {

            }

            /**
             * Test if file exists
             * @return
             */
            bool exists() {
                return SPIFFS.exists(_filename);
            }

            /**
             *
             * @param mode
             * @return
             */
            void open(const char* mode) {
                _file = SPIFFS.open(_filename, mode);
            }

            /**
             *
             */
            void close() {
                _file.close();
            }

            /**
             * Dump content to stream
             * @param stream
             */
            void cat(Stream *stream) {
                File file = SPIFFS.open(_filename, "r");

                if (file.available())
                    while (file.available())
                        stream->print((char) file.read());

                file.close();
            }

            /**
             * @see parent
             * @param c
             * @return
             */
           SpiffsFile& print(char c) {
                _file.print(c);

                return *this;
            }

            /**
             * @see parent
             * @param number
             * @return
             */
           SpiffsFile& print(float number) {
                _file.print(number);

                return *this;
            }

            /**
             * @see parent
             * @param string
             * @return
             */
           SpiffsFile& print(String string) {
                _file.print(string);

                return *this;
            }

         protected:
            const String _filename;
            File _file;
         };
    }
}