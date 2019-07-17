---
home: true
---

Eloquent Arduino is an attempt to bring sanity and most of all clarity in Arduino projects' code. 
Arduino sells itself as a platform well suited for beginners, and it is for sure.
Lots of non-tech people are able to bring their ideas to life thanks to this awesome platform.
Nevertheless, I often stumble on random bits of code over the internet that make me think about the
quality of the projects people are producing.

Even the Arduino official site is misleading in this sense, in my opinion, since it promotes a code style 
really straighforward, but suited for toy projects, with little logics and low complexity level.
When things start to get seriuous (and it soon happens as your project grows),
 it is quite inevitable that you'll come into trouble, since you will be mixing lots of variables, 
 flags and states, thus producing the (in)famous spaghetti code.
Here's an example of what I'm talking about, copy-pasted from the Arduino official site (with comments removed):

```cpp
void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (ledState == LOW) {
      ledState = HIGH;
    } else {
      ledState = LOW;
    }

    digitalWrite(ledPin, ledState);
  }
}
```

Can you tell what this code does with a minimum mental effort? I don't think so 
(it actually blinks a LED in a non-blocking fashion). And this is the problem: most Arduino code is not **eloquent**.
By eloquent I mean code that speaks by itself, without the need for comments. What about the following:

```cpp
void loop() {
    every(interval * SECONDS) {
        led.toggle();
    }
}
```

Hopefully, it does the exact same thing as above, yet it is far more readable and understandable.
Can you see my point now? Wouldn't it be much easier and reliable to code with the help of a 
set of such eloquent constructs / interfaces? I strongly believe it is, and this is why I'm writing this library. 
Asynchronous programming, pin state managements, animations are bits of code that pop up over and over again 
in most of the projects, yet every time we start from zero and write the same boilerplate code over and over again.
 Boilerplate code is not only tedious, but error-prone, since it heavily relies on a fixed structure that 
 could be not that easy to adapt to your specific case. And lengthy! Longer code means more chances to break 
 something and more code to debug, which can waste lots of your valuable time.