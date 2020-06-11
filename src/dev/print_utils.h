#pragma once

#if defined(Stream_h)

//#include "black_magic.h"

//#define serialprint(...) EVAL(MAP(Serial.print, __VA_ARGS__))

//#define _FCSV(f, x) f.print(x); f.print('\t');
//#define fcsv(f, ...) EVAL(MAP(Serial.print, __VA_ARGS__)) f.print('\n');
//#define fcsv(f, ...) EVAL(MAP_WITH_ARG(_FCSV, f, __VA_ARGS__)) f.print('\n');
//#define csv(...) fcsv(Serial, __VA_ARGS__);


/**
 * Stop condition
 * @param stream
 */
void fprint_all(Stream* stream) {}

/**
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
 * @tparam Args
 * @param args
 */
template<typename... Args>
void print_all(Args... args) {
    fprint_all(&Serial, args...);
}


/**
 * Stop condition
 * @param stream
 */
void fcsv(Stream* stream) {
    stream->print('\n');
}

/**
 *
 * @tparam T
 * @tparam Args
 * @param stream
 * @param first
 * @param args
 */
template<typename T, typename... Args>
void fcsv(Stream* stream, T first, Args... args) {
    stream->print(first);
    stream->print('\t');
    fcsv(stream, args...);
}

/**
 *
 * @tparam Args
 * @param args
 */
template<typename... Args>
void csv(Args... args) { fcsv(&Serial, args...); }


/**
 *
 */
template<typename T>
void fprint_array(Stream *stream, T *array, uint16_t length, char separator=',') {
    for (uint16_t i = 0; i < length; i++) {
        stream->print(array[i]);
        stream->print(i == length - 1 ? '\n' : separator);
    }
}


/**
 *
 */
template<typename T>
void print_array(T *array, uint16_t length, char separator=',') {
    fprint_array(&Serial, array, length, separator);
}



#endif