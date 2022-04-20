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
             * @param openImmediately
             */
            SpiffsFile(String filename, char *mode, bool openImmediately = false) :
                _filename(filename),
                _mode(mode),
                _opened(false) {

                setMode(mode);

                if (openImmediately)
                    open();
            }

            /**
             * Open file
             * @return
             */
            bool open(const char *mode = "") {
                if (_opened)
                    close();

                setMode(mode);
                _file = SPIFFS.open(_filename, _mode);

                if (_file) {
                    return (_opened = true);
                }

                return false;
            }

            /**
             * Alias for open()
             * @param mode
             * @return
             */
            bool reopenAs(const char *mode) {
                close();

                return open(mode);
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

                close();

                return s;
            }

            /**
             * Test if more data is available
             * @return
             */
            bool available() {
                return _file.available();
            }

            /**
             *
             * @return
             */
            uint8_t read() {
                if (_isReadable)
                    return _file.read();

                return 0;
            }

            /**
             *
             * @tparam T
             * @param data
             * @return
             */
            template<typename T>
            size_t write(T data) {
                if (!_isWritable)
                    return 0;

                if (!_opened && !open())
                    return 0;

                return _file.write(data);
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
                if (!_isWritable)
                    return 0;

                if (!_opened && !open())
                    return 0;

                return _file.write(data, length);
            }

        protected:
            String _filename;
            char *_mode;
            File _file;
            bool _opened;
            bool _isReadable;
            bool _isWritable;

            /**
             *
             * @param mode
             */
            void setMode(const char *mode) {
                if (strlen(mode) > 0)
                    _mode = (char *) mode;

                _isReadable = String(_mode).indexOf("r") >= 0 || String(_mode).indexOf("+") >= 0;
                _isWritable = String(_mode).indexOf("w") >= 0;
            }
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
             * @param openImmediately
             * @return
             */
            SpiffsFile readBinary(String filename, bool openImmediately = true) {
                return SpiffsFile(filename, "rb", openImmediately);
            }

            /**
             *
             * @param filename
             * @return
             */
            SpiffsFile writeBinary(String filename) {
                return SpiffsFile(filename, "wb");
            }

            /**
             * List files to output stream
             * @tparam Printer
             * @param printer
             */
            template<class Printer>
            void listTo(Printer &printer) {
                File root = SPIFFS.open("/");
                File file = root.openNextFile();

                printer.print("List of files\n");

                while(file) {
                    float size = file.size();
                    String unit = "bytes";

                    if (size >= 1024 * 1024 * 1024) {
                        size /= 1024 * 1024 * 1024;
                        unit = "Gb";
                    }
                    else if (size >= 1024 * 1024) {
                        size /= 1024 * 1024;
                        unit = "Mb";
                    }
                    else if (size >= 1024) {
                        size /= 1024;
                        unit = "Kb";
                    }

                    printer.print(file.name());
                    printer.print(": ");
                    printer.print(size);
                    printer.print(" ");
                    printer.print(unit);
                    printer.print("\n");

                    file = root.openNextFile();
                }
            }
        };
    }
}

ELOQUENT_SINGLETON(Eloquent::FS::SpiffsFilesystem filesystem);