//
// Created by Simone on 23/03/2022.
//

#pragma once

#include <FS.h>
#include <SPIFFS.h>
#include "../macros.h"


namespace Eloquent {
    namespace FS {
        /**
         * File wrapper
         */
        class SpiffsFile {
        public:

            /**
             * Constructor
             * @param filename
             * @param mode
             */
            SpiffsFile(String filename, const char *mode) :
                _filename(filename),
                _mode(mode),
                _opened(false) {
                _isReadable = String(mode).indexOf("r") >= 0 || String(mode).indexOf("+") >= 0;
                _isWritable = String(mode).indexOf("w") >= 0;
            }

            /**
             * Open file
             * @return
             */
            bool open() {
                if (_opened)
                    return true;

                close();
                _file = SPIFFS.open(_filename, _mode);

                if (_file) {
                    return (_opened = true);
                }

                return false;
            }

            /**
             *
             */
            void close() {
                _file.close();
                _opened = false;
            }

            /**
             * Get file size
             * NOTE: will close the file first!
             * @return
             */
            size_t size() {
                close();
                File file = SPIFFS.open(_filename, "r");
                size_t s = file.size();

                file.close();

                return s;
            }

            /**
             *
             * @tparam T
             * @param data
             * @return
             */
            template<typename T>
            size_t write(T data) {
                if (open() && _isWritable) {
                    return _file.write(data);
                }

                return 0;
            }

            /**
             * Write raw data of given length
             * @tparam T
             * @param data
             * @param length
             * @return
             */
            template<typename T>
            size_t write(T data, size_t length) {
                if (open() && _isWritable) {
                    return _file.write(data, length);
                }

                return 0;
            }

        protected:
            String _filename;
            const char *_mode;
            File _file;
            bool _opened;
            bool _isReadable;
            bool _isWritable;
        };

        /**
         * Spiffs filesystem abstraction
         */
        class SpiffsFilesystem {
        public:

            /**
             * Init SPIFFS
             * @param format
             */
            void begin(bool format = false) {
                SPIFFS.begin(format);
            }

            /**
             *
             * @param filename
             * @return
             */
            SpiffsFile writeBinary(String filename) {
                return SpiffsFile(filename, "wb");
            }
        };
    }
}

ELOQUENT_SINGLETON(Eloquent::FS::SpiffsFilesystem filesystem);