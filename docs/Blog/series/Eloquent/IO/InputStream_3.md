---
title: InputStream . Part3
date: 2019-11-27
namespace: 'Eloquent::IO'
---

# IO::InputStream . Part3

In this post we'll list the available transformers.

::: warning
Some transformers will need more than one input to generate an output.
You should always check if the stream returned a valid value with `isNan()`!

```cpp
if (!stream.isNan()) {
    // do stuff
}
```
:::

### AtLeast

Truncates the values whose absolute value is less than a threshold to 0.

```cpp
int array = {-5, -4, -2, 2, 4, 5};
ArrayInputStream stream(array);

void setup() {
    stream.then(new AtLeast(3));
}

void loop() {
    assertTrue(stram.read() == -5);
    assertTrue(stram.read() == -4);
    assertTrue(stram.read() == 0);
    assertTrue(stram.read() == 0);
    assertTrue(stram.read() == 4);
    assertTrue(stram.read() == 5);
}
```

### Average

Takes the average of the last chunk of N samples.

::: warning
This is a discrete transformer: it will not output a value for each input value
:::

```cpp
int array = {1, 2, 3, 4, 5, 6, 10, 14, 12};
ArrayInputStream stream(array);

void setup() {
    stream.then(new Average(3)); // take the average of every 3 values
}

void loop() {
    assertTrue(stram.read() == NaN); // we need 3 values, just 1 here
    assertTrue(stram.read() == NaN); // we need 3 values, just 2 here
    assertTrue(stram.read() == 2);   // now we can average the 3 values
    assertTrue(stram.read() == NaN);
    assertTrue(stram.read() == NaN);
    assertTrue(stram.read() == 5);
    assertTrue(stram.read() == NaN);
    assertTrue(stram.read() == NaN);
    assertTrue(stram.read() == 12);
}
```

### Constrain

Applies `constrain(x, min, max)` to the input values.

```cpp
int array = {1, 2, 3, 4, 5, 6, 7};
ArrayInputStream stream(array);

void setup() {
    stream.then(new Constrain(3, 5));
}

void loop() {
    assertTrue(stram.read() == 3);
    assertTrue(stram.read() == 3);
    assertTrue(stram.read() == 3);
    assertTrue(stram.read() == 4);
    assertTrue(stram.read() == 5);
    assertTrue(stram.read() == 5);
    assertTrue(stram.read() == 5);
}
```

### Derivative

Outputs the difference between the current value and the previous.

```cpp
int array = {1, 2, 4, 7, 11};
ArrayInputStream stream(array);

void setup() {
    stream.then(new Derivative());
}

void loop() {
    assertTrue(stram.read() == Nan); // first value is NaN, because no previous value
    assertTrue(stram.read() == 1); // = 2 - 1
    assertTrue(stram.read() == 2); // = 4 - 2
    assertTrue(stram.read() == 3); // = 7 - 4
    assertTrue(stram.read() == 4); // = 11 - 7
}
```

### ExponentialSmoothing

Applies exponential smoothing to the values. The formula is `f(x[i]) = a*x[i] + (1-a)*x[i-1]`

### Map

Applies `map(x, fromLow, fromHigh, toLow, toHigh)` to the input values.

```cpp
int array = {1, 2, 3, 4, 5};
ArrayInputStream stream(array);

void setup() {
    stream.then(new Map(1, 10, 1, 100));
}

void loop() {
    assertTrue(stram.read() == 10);
    assertTrue(stram.read() == 20);
    assertTrue(stram.read() == 30);
    assertTrue(stram.read() == 40);
    assertTrue(stram.read() == 50);
}
```

### Round

Applies `round(x)` to the input values

```cpp
float array = {1.1, 9.9};
ArrayInputStream stream(array);

void setup() {
    // available ROUND, FLOOR, CEIL
    stream.then(new Round(RoundStrategy::ROUND));
}

void loop() {
    assertTrue(stram.read() == 1);
    assertTrue(stram.read() == 10);
}
```
