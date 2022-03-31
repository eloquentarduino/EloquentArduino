#pragma once

#define AWAIT2(condition, timeout) AWAIT3(condition, timeout, 10)

/**
 * Await for a condition to become true
 * within the given timeout.
 */
#define AWAIT3(condition, timeout, interval) \
  ([]() { \
    uint32_t start = millis(); \
    while (millis() - start <= timeout) { \
      if (condition) return true; \
      delay(interval); \
    } \
  return false; })()

#define CHOOSE_AWAIT_MACRO(_1, _2, _3, NAME, ...) NAME
#define await(...) CHOOSE_AWAIT_MACRO(__VA_ARGS__, AWAIT3, AWAIT2)(__VA_ARGS__)