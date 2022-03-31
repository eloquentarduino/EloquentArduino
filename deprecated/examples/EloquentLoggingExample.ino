#include <EloquentLogging.h>

/**
 * Available severities are, in order:
 *  1. EMERGENCY
 *  2. ALERT
 *  3. CRITICAL
 *  4. ERROR
 *  5. WARNING
 *  6. NOTICE
 *  7. INFO
 *  8. DEBUG
 *
 * All messages with a severity <= LOG_SEVERITY are logged, otherwise discarded.
 * A few utilities exist, such as:
 *  - log_SEVERITY_if(condition, msg): log msg only if condition is true
 *  - log_SEVERITY_unless(condition, msg): log msg only if condition is false
 *  - var_dump(key, value): dump the variable with a descriptive name. LOG_SEVERITY MUST be at least LOG_SEVERITY_DEBUG
 */

#define LOG_SEVERITY LOG_SEVERITY_DEBUG


void setup() {
    Serial.begin(9600);
    delay(1000);

    log_emergency_unless(false, "EMERGENCY");
    log_alert_unless(false, "ALERT");
    log_critical_unless(false, "CRITICAL");
    log_error_unless(false, "ERROR");
    log_warning_unless(false, "WARNING");
    log_notice_unless(false, "NOTICE");
    log_info_unless(false, "INFO");
    log_debug_unless(false, "DEBUG");

    int value = 1;
    var_dump("Value", value);

}

void loop() {

}