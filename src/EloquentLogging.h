#pragma once

/**
 * A super simple logging library
 * Only prints to Serial
 * Adheres to the severities of PSR-3 Logger Interface @ https://www.php-fig.org/psr/psr-3/
 */

#define LOG_SEVERITY_SILENT 0
#define LOG_SEVERITY_EMERGENCY 1
#define LOG_SEVERITY_ALERT 2
#define LOG_SEVERITY_CRITICAL 3
#define LOG_SEVERITY_ERROR 4
#define LOG_SEVERITY_WARNING 5
#define LOG_SEVERITY_NOTICE 6
#define LOG_SEVERITY_INFO 7
#define LOG_SEVERITY_DEBUG 8

#ifndef LOG_SEVERITY
#define LOG_SEVERITY LOG_SEVERITY_DEBUG
#endif

#define __log(severity, severity_string, msg) if (severity <= LOG_SEVERITY) { Serial.print('['); Serial.print(severity_string); Serial.print("] "); Serial.println(msg); }

#define log_emergency(msg)  __log(LOG_SEVERITY_EMERGENCY, "EMERGENCY", msg);
#define log_alert(msg)      __log(LOG_SEVERITY_ALERT, "ALERT", msg);
#define log_critical(msg)   __log(LOG_SEVERITY_CRITICAL, "CRITICAL", msg);
#define log_error(msg)      __log(LOG_SEVERITY_ERROR, "ERROR", msg);
#define log_warning(msg)    __log(LOG_SEVERITY_WARNING, "WARNING", msg);
#define log_notice(msg)     __log(LOG_SEVERITY_NOTICE, "NOTICE", msg);
#define log_info(msg)       __log(LOG_SEVERITY_INFO, "INFO", msg);
#define log_debug(msg)      __log(LOG_SEVERITY_DEBUG, "DEBUG", msg);

#define log_emergency_if(condition, msg)        if (condition) { log_emergency(msg);    }
#define log_alert_if(condition, msg)            if (condition) { log_alert(msg);        }
#define log_critical_if(condition, msg)         if (condition) { log_critical(msg);     }
#define log_error_if(condition, msg)            if (condition) { log_error(msg);        }
#define log_warning_if(condition, msg)          if (condition) { log_warning(msg);      }
#define log_notice_if(condition, msg)           if (condition) { log_notice(msg);       }
#define log_info_if(condition, msg)             if (condition) { log_info(msg);         }
#define log_debug_if(condition, msg)            if (condition) { log_debug(msg);        }

#define log_emergency_unless(condition, msg)    log_emergency_if(!(condition), msg)
#define log_alert_unless(condition, msg)        log_alert_if(!(condition), msg)
#define log_critical_unless(condition, msg)     log_critical_if(!(condition), msg)
#define log_error_unless(condition, msg)        log_error_if(!(condition), msg)
#define log_warning_unless(condition, msg)      log_warning_if(!(condition), msg)
#define log_notice_unless(condition, msg)       log_notice_if(!(condition), msg)
#define log_info_unless(condition, msg)         log_info_if(!(condition), msg)
#define log_debug_unless(condition, msg)        log_debug_if(!(condition), msg)

#define var_dump(k, v) if (LOG_SEVERITY >= LOG_SEVERITY_DEBUG) { Serial.print("[DUMP] "); Serial.print(k); Serial.print(":\t"); Serial.println(v); }
