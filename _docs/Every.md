---
title: Every
---

# Every

Sometimes you may need to execute a piece of code at regular intervals. There are a couple
of Timer libraries out there that allows you to do this and a lot more. If you need to start,
stop, pause your timer, go use them, they're really powerful. But if you need something simpler,
you may consider using the `every` construct: it takes a time interval as argument and will
execute the code following code block at regular interval.


### Import

```#include "EloquentTimeUtils.h"```


### How to use

```cpp
int interval = 1000;

void loop() {
    every(1000) {
        Serial.println("Every 1 second");
    }

    every(2 Seconds) {
        Serial.println("Every 2 seconds");
    }

    every(interval) {
        Serial.println("You can have variable intervals");
        interval += 1000;
    }
}
```

### Caveats

`every` is a macro and it has some limitations:

 1. you can't stop or pause it
 2. you can't use several `every` with the same argument
 3. its argument must be the suffix of a valid identifier

Let me clarify 2. and 3.: the macro generates a variable named like `__every__##argument`:
it means that `every(1000)` generates a variable `uint32_t __every__1000`, `every(interval)`
generates `uint32_t __every__interval` and so on, so you can't call `every(10 * 1000)`,
since it would generate `uint32_t __every__10 * 1000`, which would rise a syntax error.

If you can live with this limitations, `every` only needs the space of an `uint32_t` to work.