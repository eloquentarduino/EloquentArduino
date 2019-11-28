---
title: Introducing MicroML
---

# Introducing MicroML

MicroML is an attempt to bring Machine Learning algorithms to microcontrollers.
It originated when I first saw a blog about Tensorflow Lite for microcontrollers
and thought it was a waste of resources (if they even fitted on the hardware)
to run Neural Networks on such constrained devices when more efficient
alternatives were available.<br>
Quoting from the Tensoflow blog: `The core runtime fits in 16 KB on an Arm Cortex M3`
(that's just the runtime, without any actual operator!).
What about my beloved Arduino Nano (old generation) and its 2 Kb of RAM?
**Should I give up on ML? No way!**

I opted for [Support Vector Machines](https://en.wikipedia.org/wiki/Support-vector_machine)
as a good candidate algorithm, since support vectors should lead to a space efficient
implementation (since RAM is often the most limiting factor).
The basic idea is that you train a classifier in Python with [scikit-learn](https://scikit-learn.org/)
and generate C code from it.<br>
[sklearn-porter](https://github.com/nok/sklearn-porter) is an existing project
that can output C code, though it's not optimized for microcontrollers, so you'll
hit a wall on memory because it needs to declare all the support vectors in memory
(to have an idea, the [breast cancer dataset](https://scikit-learn.org/stable/modules/generated/sklearn.datasets.load_breast_cancer.html)
produces a 57x30 matrix of doubles, totalling 6840 bytes just for the support vectors).

So my effort was to find an implementation that needed the least amount possible of
memory, sacrificing the program space in my case, since you will hardly ever
fill that much space.
After a whole 20 minutes of thinking, the result is a Python library that takes 
a SVM classifier and produces C code you can copy-paste in your project to run ML 
on microcontrollers. The C code is clearly readable, so you can even see what's going on:
no black magic.

In a next series of articles I'll take the demo projects on the Tensorflow blog
and clone them using MicroML instead, comparing the hardware requirements
of the two. Stay tuned!