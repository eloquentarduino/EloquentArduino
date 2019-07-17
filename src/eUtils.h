#pragma once

#ifndef ELOQUENT_UTILS_NO_TIME_CONSTANTS
    #define Second *1000
    #define Seconds *1000
	#define Millis
#endif

/**
 * Execute code periodically.
 * Stop using `millis`
 * 
 * You can have multiple timers in your loop, the only restriction is the interval be the suffix of a valid identifier.
 * This means (in practice) they must be numeric constants or single variables.
 *
 */
#define every(interval) static uint32_t __every__##interval = millis(); \
	if (millis() - __every__##interval >= interval && (__every__##interval = millis()))


#define within(timeout) for (uint32_t __end = millis() + timeout; __end; __end = 0)
#define check_within if (millis() > __end) break;



/**
 * Don't get stuck in infinite waits.
 * Usage: bool serialAvailable = await(Serial, 5000)
 */
/*#define await(condition, timeout) await_with_interval(condition, timeout, 10)
#define await_with_interval(condition, timeout, interval) \
	([]() { \
		uint32_t start = millis(); \
		while (millis() - start <= timeout) { \
			if (condition) return true; \
			delay(interval); \
		} \
	return false; })()
 */


/**
 * Retry to call function for a given number of times
 * until it return true
 * @param f
 * @param retries
 * @return
 */
bool retry(bool (*f)(), uint8_t retries) {
	for (; retries > 0; retries--)
		if (f())
			return true;

	return false;
}


/**
 * Don't get stuck in infinite waits
 * @param f
 * @param timeout
 * @return
 */
bool await(bool (*f)(), uint32_t timeout) {
	uint32_t start = millis();

	while (millis() - start < timeout) {
		if (f())
			return true;

		delay(10);
	}

	return false;
}