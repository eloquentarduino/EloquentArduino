#ifndef ELOQUENTARDUINO_PRINT
#define ELOQUENTARDUINO_PRINT 1

#if defined(Stream_h)

namespace eloquent {
    namespace io {

        /**
         * fprint_all stop condition
         * @param stream
         */
        void fprint_all(Stream* stream) {
            stream->print('\n');
        }

        /**
         * Print all arguments
         * @tparam T
         * @tparam Args
         * @param stream
         * @param first
         * @param args
         */
        template<typename T, typename... Args>
        void fprint_all(Stream* stream, T first, Args... args) {
            stream->print(first);
            fprint_all(stream, args...);
        }


        /**
         * print_csv stop condition
         * @param stream
         */
        void fprint_csv(Stream* stream) {
            stream->print('\n');
        }

        /**
         * Print all arguments comma-separated
         * @tparam T
         * @tparam Args
         * @param stream
         * @param first
         * @param args
         */
        template<typename T, typename... Args>
        void fprint_csv(Stream* stream, T first, Args... args) {
            stream->print(first);
            stream->print('\t');
            fprint_csv(stream, args...);
        }


        /**
         * Print array
         */
        template<typename T>
        void fprint_array(Stream *stream, T *array, uint16_t length, char separator=',') {
            for (uint16_t i = 0; i < length; i++) {
                stream->print(array[i]);
                stream->print(i == length - 1 ? '\n' : separator);
            }
        }

    }
}

#endif
#endif