# SVM

Machine learning on microcontrollers is a hot topic these days.
Adafruit [https://blog.adafruit.com/2019/06/24/tiny-machine-learning-on-the-edge-with-tensorflow-lite-running-on-samd51-arduino-tensorflow-tinyml-tensorflow/](seems to be the first who ported TensorFlow Lite to his SAMD51 boards).
But TensorFlow (and deep learning) are not the whole machine learning world, so I
explored the possibility to port other algorithms to resource-constrained hardware.

One that seems fit to this purpose was SVM (Support Vector Machines): they're quite
simple to use and work pretty well for lots of classification problems. Of course
you will need to train a model on your PC: then you can run that model on the Arduino
to do the classification.

The whole project is to get a sklearn SVM classifier and "export" it to plain C.
Of course the porting should strive to keep the program space and memory usage to
the minimum, well below the Arduino boards limits, so the user can still write its
own code to actually do something useful.

Using the Arduino UNO board as a reference, I got 6372 bytes (19%) of program space and 264 bytes (12%)
of memory for a toy sketch that classifies three samples of the IRIS dataset.
This means the model has a tiny footprint and it's embeddable in almost any project.