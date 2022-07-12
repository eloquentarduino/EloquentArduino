//
// Created by Simone on 08/03/2022.
//

#pragma once

#include <stdarg.h>


namespace eloquent {
    namespace print {

        /**
         *
         * @tparam Printer
         * @param stream
         * @param fmt
         * @param ...
         */
         template<class Printer>
        void printf(Printer &printer, char *fmt, ...) {
            char buf[256];

            va_list args;
            va_start (args, fmt );
            vsnprintf(buf, 256, fmt, args);
            va_end (args);
            printer.print(buf);
        }

        /**
         * Stop condition for print_all
         * @tparam Printer
         * @param printer
         */
        template<class Printer>
        void print_all(Printer& printer) {

        }

        /**
         * Print all arguments
         * @tparam Printer
         * @tparam T
         * @tparam Args
         * @param stream
         * @param first
         * @param args
         */
        template<class Printer, typename T, typename... Args>
        void print_all(Printer& printer, T first, Args... args) {
            printer.print(first);
            print_all(printer, args...);
        }
    }
}
