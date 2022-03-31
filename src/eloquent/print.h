//
// Created by Simone on 08/03/2022.
//

#pragma once

#include <stdarg.h>


namespace eloquent {
    namespace print {

        /**
         *
         * @tparam Stream
         * @param stream
         * @param fmt
         * @param ...
         */
         template<typename Stream>
        void printf(Stream &stream, char *fmt, ...) {
            char buf[128];

            va_list args;
            va_start (args, fmt );
            vsnprintf(buf, 128, fmt, args);
            va_end (args);
            stream.print(buf);
        }

        /**
         *
         * @tparam Stream
         * @tparam bufferSize
         * @param stream
         * @param fmt
         * @param ...
         */
        template<typename Stream, size_t bufferSize>
        void printf(Stream &stream, char *fmt, ...) {
            char buf[bufferSize];

            va_list args;
            va_start (args, fmt );
            vsnprintf(buf, bufferSize, fmt, args);
            va_end (args);
            stream.print(buf);
        }
    }
}
