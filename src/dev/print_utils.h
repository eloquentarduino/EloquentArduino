#pragma once

#include "black_magic.h"

#define serialprint(...) EVAL(MAP(Serial.print, __VA_ARGS__))

//#define _FCSV(f, x) f.print(x); f.print('\t');
//#define fcsv(f, ...) EVAL(MAP(Serial.print, __VA_ARGS__)) f.print('\n');
//#define fcsv(f, ...) EVAL(MAP_WITH_ARG(_FCSV, f, __VA_ARGS__)) f.print('\n');
//#define csv(...) fcsv(Serial, __VA_ARGS__);


/**
 * @private
 * @tparam T
 * @param stream
 * @param v
 */
template<typename T>
void __csv(Stream* stream, T v) { stream->print(v); stream->print('\t'); }

/**
 * @private
 * @tparam T
 * @tparam Args
 * @param stream
 * @param first
 * @param args
 */
template<typename T, typename... Args>
void __csv(Stream* stream, T first, Args... args) { __csv(stream, first); __csv(stream, args...); }


/**
 * CSV to Stream public interface
 * @tparam Args
 * @param stream
 * @param args
 */
template<typename... Args>
void fcsv(Stream* stream, Args... args) { __csv(stream, args...); stream->print('\n'); }

/**
 * CSV to Serial public interface
 * @tparam Args
 * @param args
 */
template<typename... Args>
void csv(Args... args) { fcsv(&Serial, args...); }