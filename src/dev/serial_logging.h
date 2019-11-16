#pragma once

/**
 * A super simple logging library
 * Only prints to LOG_OUTPUT
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

#ifndef LOG_OUTPUT
#define LOG_OUTPUT Serial
#endif

#ifndef LOG_SEVERITY
#define LOG_SEVERITY LOG_SEVERITY_DEBUG
#endif

#if defined(LOG_DISABLED)
#define __log(severity, severity_string, msg)
#else
#define __log(severity, severity_string, msg) \
    if (severity <= LOG_SEVERITY) { \
        LOG_OUTPUT.print('('); \
        LOG_OUTPUT.print(__FILE__); \
        LOG_OUTPUT.print(':'); \
        LOG_OUTPUT.print(__LINE__); \
        LOG_OUTPUT.print(") "); \
        LOG_OUTPUT.print('['); \
        LOG_OUTPUT.print(severity_string); \
        LOG_OUTPUT.print("] "); \
        LOG_OUTPUT.println(msg); \
    }
#endif

#define log_emergency(msg)  __log(LOG_SEVERITY_EMERGENCY, "EMERGENCY", msg)
#define log_alert(msg)      __log(LOG_SEVERITY_ALERT, "ALERT", msg)
#define log_critical(msg)   __log(LOG_SEVERITY_CRITICAL, "CRITICAL", msg)
#define log_error(msg)      __log(LOG_SEVERITY_ERROR, "ERROR", msg)
#define log_warning(msg)    __log(LOG_SEVERITY_WARNING, "WARNING", msg)
#define log_notice(msg)     __log(LOG_SEVERITY_NOTICE, "NOTICE", msg)
#define log_info(msg)       __log(LOG_SEVERITY_INFO, "INFO", msg)
#define log_debug(msg)      __log(LOG_SEVERITY_DEBUG, "DEBUG", msg)

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


// logging for library is independent from user logging
#ifdef LIBRARY_LOG_ENABLED

#define library_log_emergency	log_emergency
#define library_log_alert	    log_alert
#define library_log_critical	log_critical
#define library_log_error	    log_error
#define library_log_warning	    log_warning
#define library_log_notice	    log_notice
#define library_log_info	    log_info
#define library_log_debug	    log_debug

#define library_log_emergency_if	log_emergency_if
#define library_log_alert_if	    log_alert_if
#define library_log_critical_if	    log_critical_if
#define library_log_error_if	    log_error_if
#define library_log_warning_if	    log_warning_if
#define library_log_notice_if	    log_notice_if
#define library_log_info_if	        log_info_if
#define library_log_debug_if	    log_debug_if

#define library_log_emergency_unless	log_emergency_unless
#define library_log_alert_unless	    log_alert_unless
#define library_log_critical_unless	    log_critical_unless
#define library_log_error_unless	    log_error_unless
#define library_log_warning_unless	    log_warning_unless
#define library_log_notice_unless	    log_notice_unless
#define library_log_info_unless	        log_info_unless
#define library_log_debug_unless	    log_debug_unless

#else

#define library_log_emergency(msg)
#define library_log_alert(msg)
#define library_log_critical(msg)
#define library_log_error(msg)
#define library_log_warning(msg)
#define library_log_notice(msg)
#define library_log_info(msg)
#define library_log_debug(msg)

#define library_log_emergency_if(condition, msg)
#define library_log_alert_if(condition, msg)
#define library_log_critical_if(condition, msg)
#define library_log_error_if(condition, msg)
#define library_log_warning_if(condition, msg)
#define library_log_notice_if(condition, msg)
#define library_log_info_if(condition, msg)
#define library_log_debug_if(condition, msg)

#define library_log_emergency_unless(condition, msg)
#define library_log_alert_unless(condition, msg)
#define library_log_critical_unless(condition, msg)
#define library_log_error_unless(condition, msg)
#define library_log_warning_unless(condition, msg)
#define library_log_notice_unless(condition, msg)
#define library_log_info_unless(condition, msg)
#define library_log_debug_unless(condition, msg)

#endif

#define var_dump(k, v) if (LOG_SEVERITY >= LOG_SEVERITY_DEBUG) { LOG_OUTPUT.print("[DUMP] "); LOG_OUTPUT.print(k); LOG_OUTPUT.print(":\t"); LOG_OUTPUT.println(v); }
#define assert(msg, condition) LOG_OUTPUT.print((condition) ? "OK " : "ERR"); LOG_OUTPUT.print('\t'); LOG_OUTPUT.println(msg);
#define assert_equal(msg, actual, truth) if ((actual) == (truth)) { LOG_OUTPUT.print("OK \t"); LOG_OUTPUT.println(msg); } else { LOG_OUTPUT.print("ERR\t"); LOG_OUTPUT.print(msg); LOG_OUTPUT.print("\tGot "); LOG_OUTPUT.print(actual); LOG_OUTPUT.print(" instead of "); LOG_OUTPUT.println(truth); }
