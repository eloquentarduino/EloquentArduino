---
title: Pin
date: 2019-25-11
namespace: 'Eloquent::IO'
---

# IO::Pin

`Pin` is an abstract class for pin manipulation. You won't use it directly,
but through its specialized implementations:

 1. DigitalIn
 2. DigitalOut
 3. AnalogIn
 4. AnalogOut
 
These classes will let you stop writing horrible code like `digitalWrite(led, HIGH)`
and do `led.turnOn()` instead, for example.

You may be asking if a whole class to save a few keystrokes is whortwhile. I strongly
believe it is! 
What's the use case, you may ask? Well, one emblematic example is that of the
builtin led on the ESP8266: it is active low, so you write `digitalWrite(BUILTIN_LED, LOW)`
to actually turn it on. Does it look intuitive? Does it look *eloquent*? Not really.
`builtinLed.turnOn()` does, however. All you need to get it working is calling
`builtinLed.activeLow()` in your setup to hide the reversed logic.

Want another example? Toggle. If you need to toggle the current state of a digital
output, you need an helper variable to keep track of the state (and remember to **ALWAYS**
update that variable when you write to the output). With a class, the state is 
tightly bound to the instance, so you have a [single source of truth](https://en.wikipedia.org/wiki/Single_source_of_truth):
`turnOn()`, `turnOff()` and `toggle()` will take care of updating the inner state accordingly.

```c
// BEFORE
#define LED 1

bool ledState = true;

loop() {
    digitalWrite(LED, ledState);
    ledState = !ledState
}


// AFTER
DigitalOut led(1);

void loop() {
    led.toggle();
}
```

Not convinced yet? What if you have an analog input and want to know if its valued
changed by at least X from your latest reading? You would need an helper variable
again. Now imagine if you have 5 analog inputs you want to track: you'll end up
with 10 variables and of course you have again to *ALWAYS* keep both in sync.
`AnalogIn`, conveniently, provides a `delta()` method that gives you the change
from the previous reading and will always be in sync. Awesome!

```c
// BEFORE
#define INPUT1 A1
#define INPUT2 A2

uint16_t current1, prev1;
uint16_t current2, prev2;

void loop() {
    prev1 = current1;
    current1 = analogRead(INPUT1);
    prev2 = current2;
    current2 = analogRead(INPUT2);

    if (abs(current1 - prev1) > THRESHOLD)
        ...


// AFTER
AnalogIn input1(A1), input2(A2);

void loop() {
    input1.read();
    input2.read();

    if (input1.absDelta() > THRESHOLD)
        ...
}
```


Does it feel more *natural*?