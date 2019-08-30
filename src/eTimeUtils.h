#pragma once

#include "_e.h"


#ifndef ELOQUENT_UTILS_NO_TIME_CONSTANTS
    #define Second *1000
    #define Seconds *1000
    #define Millis
#endif


/**
 * Await for a condition to become true within a timeout
 */
#define await(...) GET_MACRO(__VA_ARGS__, await_with_capturing, await_without_capturing)(__VA_ARGS__)
#define await_without_capturing(condition, timeout) await_with_capturing(, condition, timeout)
#define await_with_capturing(capturing, condition, timeout) ([capturing]() {        \
    uint32_t ending = millis() + (timeout);       \
                                                \
    while (millis() < ending) {                 \
        if (condition)                          \
            return true;                        \
        else delay(10);                         \
    }                                           \
                                                \
    return false;                               \
})()