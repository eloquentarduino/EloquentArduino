#pragma once

#ifndef ELOQUENT_TIMEUTILS_NO_CONSTANTS
    #define Second 1000
    #define Seconds 1000
#endif

/**
 * Execute code periodically.
 * Stop using `millis`
 * 
 * You can have multiple timers in your loop, the only restriction is the interval be the suffix of a valid identifier.
 * This means (in practice) they must be numeric constants or single variables.
 *
 */
#define every(interval) static unsigned long __every__##interval = millis(); \
	if (millis() - __every__##interval >= interval && (__every__##interval = millis()))


/**
 * Don't get stuck in infinite waits.
 * Usage: bool serialAvailable = await(Serial, 5000)
 */
#define await(condition, timeout) \
	([]() { \
		uint32_t start = millis(); while (millis() - start <= timeout) { \
			if (condition) return true; \
			delay(1); \
		} \
	return false; })()
