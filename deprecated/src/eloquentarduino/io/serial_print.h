#ifndef ELOQUENTARDUINO_SERIAL_PRINT
#define ELOQUENTARDUINO_SERIAL_PRINT 1

#if defined(Stream_h)

#include "print.h"


namespace eloquent {
    namespace io {

        /**
         * Print all arguments to Serial
         * @tparam Args
         * @param args
         */
        template<typename... Args>
        void print_all(Args... args) {
            fprint_all(&Serial, args...);
        }


        /**
         * Print CSV-style line to serial
         * @tparam Args
         * @param args
         */
        template<typename... Args>
        void print_csv(Args... args) {
            fprint_csv(&Serial, args...);
        }


        /**
         * Print array to Serial
         */
        template<typename T>
        void print_array(T *array, uint16_t length, char separator=',') {
            fprint_array(&Serial, array, length, separator);
        }

    }
}

#endif
#endif