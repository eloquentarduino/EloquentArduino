#pragma once


namespace Eloquent {
    namespace IO {
        class Printer {
        public:
            /**
             *
             * @param stream
             */
            Printer(Stream *stream, bool appendNewline = true) :
                _stream(stream),
                _appendNewline(appendNewline) {

            }

            /**
             * all stop condition
             * @param stream
             */
            void all() {
                eol();
            }

            /**
             * Print all arguments
             * @tparam T
             * @tparam Args
             * @param first
             * @param args
             */
            template<typename T, typename... Args>
            void all(T first, Args... args) {
                _stream->print(first);

                // recursion
                all(args...);
            }


            /**
             * csv stop condition
             * @param stream
             */
            void csv() {
                eol();
            }

            /**
             * Print all arguments comma-separated
             * @tparam T
             * @tparam Args
             * @param first
             * @param args
             */
            template<typename T, typename... Args>
            void csv(T first, Args... args) {
                _stream->print(first);
                _stream->print(',');

                // recursion
                csv(args...);
            }

            /**
             * tsv stop condition
             */
            void tsv() {
                eol();
            }

            /**
             * Print all arguments tab-separated
             * @tparam T
             * @tparam Args
             * @param first
             * @param args
             */
            template<typename T, typename... Args>
            void tsv(T first, Args... args) {
                _stream->print(first);
                _stream->print('\t');

                // recursion
                tsv(args...);
            }


            /**
             * Print array
             */
            template<typename T>
            void array(T *array, uint16_t length, char separator=',') {
                for (uint16_t i = 0; i < length; i++) {
                    _stream->print(array[i]);
                    _stream->print(i == length - 1 ? '\n' : separator);
                }
            }

            /**
             * Print variable value
             * @tparam T
             * @param name
             * @param x
             */
            template<typename T>
            void variable(const char *name, T x) {
                all("Value of ", name, ": ", x);
            }

        protected:
            Stream *_stream;
            bool _appendNewline;

            /**
             * Handle end of line
             */
            void eol() {
                if (_appendNewline)
                    _stream->print('\n');
            }
        };
    }
}