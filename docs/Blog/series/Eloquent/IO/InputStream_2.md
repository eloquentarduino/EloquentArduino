---
title: InputStream . Part2
date: 2019-11-26
namespace: IO
---

# IO::InputStream . Part2

In [Part 1](./InputStream_1.md) I introduced InputStreams and Transformers.
In this second part we'll see some more examples and learn some more in depth.

## Available InputStream

This will be a (hopefully) growing list of the available InputStreams,
with a short description of the use cases of each.

### `AnalogPinInputStream`

Generates values from an analog pin; it's just a wrapper around `analogRead()`. 
Use this when working with analog sensors.

```cpp
AnalogPinInputStream potentiometer(A0);

void loop() {
    Serial.println(potentiometer.read());
    // is equivalent to
    Serial.println(analogRead(A0));
}
```

### `ArrayInputStream`

Transforms an array to a stream. It will emit the values in the array, one by one.
Use this when you have an array you want to process using the transformer
interface.

```cpp
int array[] = {2, 3, 5, 7, 11};
ArrayInputStream stream(array);

void loop() {
    assertTrue(stream.read() == 2);
    assertTrue(stream.read() == 3);
    assertTrue(stream.read() == 5);
    assertTrue(stream.read() == 7);
    assertTrue(stream.read() == 11);
    assertTrue(stream.read() == NaN);
}
```

### `AssignableInputStream` (aka `EchoInputStream`)

This stream emits the values you assign to it. It's a generic stream that 
lets you apply the InputStream interface to whatever variable you have.

```cpp
AssignableInputStream streamX;

void setup() {
    streamX.then(new Abs());
}

void loop() {
    float ax, ay, az;

    M5.MPU6886.getAccelData(ax, ay, az);
    streamX = ax;

    assertTrue(streamX.read() == abs(ax));
}
```

### A note about chaining

You may have noticed that in the examples I used the `new` construct to add the transformers
to the input stream. I suggest to use this pattern because:

 1. it's readable
 2. it forces to use "one-off" transformers
 
The 2^nd point needs some explanation: to do it's magic, the chaining uses
pointers to the transformers to create a sort of linked list, without an actual list.
This means that you can't reuse transformers in multiple places, since it will break
chaining. Also, some transformers have internal state that need to be kept consistent.
If you create a transformer just inside the `then()`, you'll be at safe.

```c
AnalogPinInputStream potentiometer1(A0);
AnalogPinInputStream potentiometer2(A1);
AnalogPinInputStream potentiometer3(A2);
ExponentialSmoothing smoothing(0.5);
Map map(0, 1024, 0, 100);

void setup() {
    // THIS WILL NOT WORK AS EXPECTED
    potentiometer1
        .then(&smoothing)
        .then(&map);

    potentiometer2
            .then(&smoothing)
            .then(&map);

    // NASTY THINGS WILL HAPPEN NOW
    potentiometer3
             .then(&map)
             .then(&smoothing);
}

void loop() {
    Serial.println(potentiomenter1.read());
    Serial.println(potentiomenter2.read());
    Serial.println(potentiomenter3.read());
}
```

-------------------------

In [Part 3](#) we'll look at the available Transformers.