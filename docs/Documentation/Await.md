---
title: Await
---

# Await

Sometimes you may need to wait for a certain condition to become true, but you don't want
to wait forever: it may be awaiting for Serial, for the Wifi to connect to a network, or
the response from a SoftwareSerial peripheral.

Most often, you see example code of this kind:

```cpp
Serial.print("Attempting to connect to WiFi");

while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
}
```

If the connection doesn't succeed, you're stuck in the loop. A proper way for handling
such situations is with a timeout that gets you out of the loop with an error status
so you can handle the failure.

`await` is exactly this: awaits for a condition to become true until a timeout expires,
returning true or false as a response.

### Import

```#include "eTimeUtils.h"```

### How to use

It needs two arguments:

 1. the condition to wait for
 2. the timeout, in milliseconds

```cpp
bool wifiConnected = await(WiFi.status() == WL_CONNECTED, 10000)

// or with the Eloquent utils:
bool wifiConnected = await(WiFi.status() == WL_CONNECTED, 10 Seconds)
```

The code above will await 10 seconds for the wifi to connect: on failure, `wifiConnected`
will be false and you can gently fail.

You can use it for any kind of check, like waiting for `Serial`

```cpp
bool serialAvailable = await(Serial, 5 Seconds)
bool serialHasCharacters = await(Serial.available(), 5 Seconds)
```

The default interval between checks is 10 milliseconds: if you need a custom delay interval
you can use the more verbose `await_with_interval`:

```cpp
// await WiFi for 10 seconds, check if connected every 500 millis
bool wifiConnected = await_with_interval(WiFi.status() == WL_CONNECTED, 10 Seconds, 500 Millis)
```