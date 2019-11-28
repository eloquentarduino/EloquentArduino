---
title: You may not need Neural Networks - Introducing MicroML
---

In the last weeks Tensorflow Lite for microcontrollers has gained
quite some momentum, thanks to its promise of delivering sophisticated
AI to tiny computers. I'm astonished too, of course: I would have never
tought it could be possible to run [person detection](https://github.com/tensorflow/tensorflow/tree/ac960b6b5a3b8a4cd69d59e63914a971e9bac8e2/tensorflow/lite/experimental/micro/examples/person_detection)
in a 256 Kb microcontroller!

Still, I'm not a big fan of neural networks in general: I never used them for
anything "serious", so I didn't took the time to learn all the ins and outs.
When I had to use them, I just added a bunch of hidden layers randomly and hoped
for the best: sometimes it worked, sometimes not. 
They just don't caught me up, though I know they can do all sort of magic!

The only thing I know for sure is they're not the most efficient algorithm
in the machine learning world: space and time can grow quite fast adding 
more and more layers.
This is why I was surprised to read about the Tensorflow effort to bring
neural networks to microcontrollers: the first thing I thought was "*WHY?*".
There are much more efficient (in both terms of space and time) algorithms
to perform machine learning, so why whould I opt for NN? Following their blog,
it still remains a mystery for me.

Anyway, when I read about NN on microcontrollers for the first time (August 2019),
I listed all the algorithms I knew - not many - searching for alternatives to NN. 
This is the list of what I know (and used during my CS degree):

 - KNN
 - decision tree
 - random forest
 - SVM
 - naive bayes
 
Apart from decision tree, which is probably the simplest and fastest option if
the data is well separable, I selected **SVM** as a good candidate, because
of it's non-linearity, high dimensionality and support vectors encoding 
which seemed to be quite space efficient from my own point of view.

Then I started searching the internet for attempts to bring SVMs to microcontrollers:
I only found the [sklearn-porter](https://github.com/nok/sklearn-porter) project,
that actually does much more than SVM in C. 
So I tried fitting the Iris dataset to a linear SVC in scikit-learn and run the porter;
it was a success: the sketch occupied 4642 bytes (15%) of program space and
860 bytes (41%) of memory of an Arduino Nano (old generation) and
the classifier predicted 20 test samples at 100% accuracy. Problem solved!

Well, not exactly: I tried with another sample dataset (breast cancer) and I hit a wall.
The sketch occupied 9964 bytes (32%) of program space and 7268 bytes (354%) of memory.