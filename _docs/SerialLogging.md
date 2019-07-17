# Serial Logging

Serial debug is the most used method to test if our code is behaving as expected. It is not
unusual to intermingle our code with lots of `Serial.print` statements to record what
execution path the code is running or what the value of a variable is.

This works fine for testing purposes, but when you're code is working fine you may need
to remove all those prints to remove clutter. `SerialLogging` defines a few helper methods
to print messages to the console with different levels of severity so you can select
only a subset of your logs to keep "in production" or silent them altogether with a
sigle command. It even provides a construct to debug the value of a variable.

### Import

```#include "EloquentLogging.h"```

### How to use

You have several levels of severity for your debugs, following the PSR-3 Logger Interface
you can find at [https://www.php-fig.org/psr/psr-3/](https://www.php-fig.org/psr/psr-3/):

 1. emergency
 2. alert
 3. critical
 4. error
 5. warning
 6. notice
 7. info
 8. debug

For each severity, you get 3 methods:

 1. `log_$severity(msg)` will always log the given message
 2. `log_$severity_if(condition, message)` will log the message only if condition is true
 3. `log_$severity_unless(condition, message)` will log the message only if condition is false

A few examples:

```cpp
void setup() {
    log_emergency("This emergency message will always be logged");
    log_error_if(!Serial, "This will be logged only if Serial is not available");
    log_info_unless(Serial, "Also this will be logged only if Serial is not available");
}
```

You can than control what messages get actually displayed with the constant `LOG_SEVERITY`,
which defaults to `LOG_SEVERITY_DEBUG` (meaning all messages are displayed):

```cpp
#define LOG_SEVERITY LOG_SEVERITY_ERROR

void setup() {
    log_emergency("This will be displayed");
    log_error("This also will be displayed");
    log_warning("This will not be displayed");
}
```

You have `LOG_SEVERITY_SILENT` to completely silent the logging.

