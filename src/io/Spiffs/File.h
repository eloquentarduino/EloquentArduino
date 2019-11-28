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
            /**
             * Constructor
             * @param filename
             */
            SpiffsFile(String filename) :
                _filename(filename),
                _opened(false) {

            }

            /**
             * Test if file exists
             * @return
             */
            bool exists() {
                return SPIFFS.exists(_filename);
            }

            /**
             * Open file
             * @param mode
             * @return
             */
            void open(const char* mode) {
                _opened = true;
                _file = SPIFFS.open(_filename, mode);
            }

            /**
             * Close file
             */
            void close() {
                if (_opened)
                    _file.close();

                _opened = false;
            }

            /**
             * Dump content to stream.
             * Will close the file at the end
             * @param stream
             */
            void cat(Stream *stream) {
                close();
                open("r");

                while (_file.available())
                    stream->print((char) _file.read());

                close();
            }

            /**
             * Delete file contents
             */
            void wipe() {
                open("w");
                close();
            }

            /**
             * @see parent
             * @param c
             * @return
             */
           SpiffsFile& print(char c) {
               return print<char>(c);
            }

            /**
             * @see parent
             * @param c
             * @return
             */
            SpiffsFile& print(const char *string) {
                return print<const char *>(string);
            }

            /**
             * @see parent
             * @param number
             * @return
             */
           SpiffsFile& print(float number) {
                return print<float>(number);
            }

            /**
             * @see parent
             * @param string
             * @return
             */
           SpiffsFile& print(String string) {
                return print<String>(string);
            }

         protected:
            const String _filename;
            bool _opened;
            File _file;

            /**
             * Actual print
             * @tparam T
             */
            template<typename T>
            SpiffsFile& print(T t) {
                if (_opened) {
                    _file.print(t);
                }

                return *this;
            }
         };
    }
}